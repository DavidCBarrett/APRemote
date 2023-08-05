#include "SeaTalk.h"
#include "ApEsp32Pins.h"
#include "main.h"

// tasks to continually read SeaTalk bus, format send data to Web Client
void readST( void *pvParameters );

// The queue sitting between the read seatalk task and the html webserver (called by client to get ST data for display)
QueueHandle_t queue;

// Seatalk param declarations
float rsa, stw, sog, xte, aws, dpt, dtw, vlw;    // rudder angle, speed through water, speed over ground, cross track error
                                                 // apparent wind speed, depth, dist to waypt, trip distance
uint16_t hdg, cts, cog, awa, btw; // heading, course to steer, course over ground, apparent wind angle, bearing to waypt
uint8_t apMode;                                 // autopilot mode 0=Standby, 1=Auto, 2=Wind, 3=Track
bool xteValid = false, btwValid = false;       // cross track error valid
int wts;             // wind angle to steer
int dir;              // direction to steer
uint8_t apAlarm;
uint8_t newCmd;

SoftwareSerial mySerial;

// Function Prototypes ...
void sendCMD(int cmd);
void CheckBus(void);
void send2ST(uint8_t cmd[]);

//
//  Core 0 task handles reading data off the seatalk bus
//  Read data of the Seatalk pick out autopilot command and display info
//  for web page.
//  looking for HDG CTS SOG Rudder angle and AP Mode
 //

void readST(void *pvParameters) 
{
  (void) pvParameters;

  bool bCmd = false;      // set true if command has been rxd, its bytes are being read, and processed.
  uint8_t bufCount = 0;   // counter for no of bytes in the command received so far
  uint8_t cmdCount;       // number of bytes expected in the command
  int i;
  uint16_t b;
  uint8_t stBuff[MAX_BUF_SIZE];
  uint32_t mS;
  char b1[15];
  uint8_t u;
  uint16_t aveAWA[5] = {0,0,0,0,0};
  uint8_t iCount = 0;
  uint8_t old_apMode = 0;
  uint8_t cmd;
  uint16_t ui16;
  uint16_t lastAWA;

  char szOut[100];

  Serial.printf("readST Task Stack High Water Mark = %d\n", uxTaskGetStackHighWaterMark(NULL));

  // buffer capacity = 20 bytes, with ISR capacity of 20*11 bits worth of timing data
  mySerial.begin(4800, SWSERIAL_8S1, RX_IN, TX_OUT, false, 80, 880);
  
  while(true){

    // "yield" for 1ms, enables to RTOS / watchdog to get a look in.
     vTaskDelay( pdMS_TO_TICKS( 1 ) );

    if(xQueueReceive(queue, &cmd, 0)){
      sendCMD(cmd);
    }

    if (!mySerial.available())
      continue;

    b = mySerial.read();
    if ((mySerial.readParity())){  // if parity set then this byte is a command byte

      if (bCmd && (cmdCount > 0)){
        if((stBuff[0] == 0x86) && (cmd >= 0)){
          // last sent command was AP request, we caused the clash so resend last autopilot command...
          Serial.println("Re-sending AP Command");
          sendCMD(cmd);
        }
        else {
          // another unit caused the clash ... just report it 
          Serial.printf("Collision found: cmd %X received while reading cmd: %X. Only bufCount: %u, read out of expected cmdCount:%u\r\n ", b, stBuff[0], bufCount, cmdCount);
          Serial.printf("  stBuff so far: ");
          for(i = 0; i < bufCount; i++){
            Serial.printf(" %X", stBuff[i]);
          }
          Serial.printf("\r\n");
        }
      }

      // reset counters for reading this command
      bCmd = true;
      bufCount = 0;
      cmdCount = 0;
      stBuff[bufCount++] = b;
    }
    else {
      if(!bCmd)
        continue;
      
      stBuff[bufCount++] = b;
 
      if(bufCount == 2){
        // this byte gives the number of bytes in cmd
        cmdCount = (b & 0x000F) + 3;    // cmd + byte count + mandatory 1st field
      }
      
      if((cmdCount == bufCount) && (cmdCount > 2)){
        // received all the chars for command so start processing it
        
        // print the command.
        for(i = 0; i < cmdCount; i++){
          Serial.print(stBuff[i], HEX);
          Serial.print(" ");
        }
        Serial.print("\n\r");

        // interprett & action the command in the rx buffer
        switch (stBuff[0]) {

          case 0x86 :
            // autopilot command sentance
            Serial.print("Rxd  AP Command :");
            for(i = 0; i < 4; i++){
              Serial.print(stBuff[i], HEX);
              Serial.print(" ");  
            }
            Serial.print("\n\r");

            //
            //  if apmode is wind and last command is direction change then adjust wts value
            //
             if (apMode == 2){
                switch(stBuff[2]){
                  case 0x05 :  // -1
                    i = 1;
                  break;
                  case 0x06 :  // -10
                    i = 10;
                  break;
                  case 0x21 :  // -Tack
                    i = 90;
                  break;
                  case 0x07 :  // +1
                    i = -1;
                  break;
                  case 0x08 :  // +10
                    i = -10;
                  break;
                  case 0x22 :  // +Tack
                    i = -90;
                  break;
                  default :
                    i = 0;
                  break;
                }
                wts += i;
                if(wts > 360){
                  wts -= 360;
                }
                if(wts < 0) {
                  wts += 360;
                }
             }
            cmd = -1;
          break;
          case 0x84 :
            
            // *
            // * got AP info so process out info we need
            // *  0  1  2  3  4  5  6  7  8
            // * 84 U6 VW XY 0Z 0M RR SS TT
            // * 
            // * RR Rudder andle pos steer STB - steer PRT
            // * 
            // * Compass heading
            // * U & 0x3 * 90 + VW & 03f *2 + 2 if U & 0xc0 > 8 
            // *                            + 1      "      = 8
            // *                            
            // * CTS = V & 0xc0 * 90 + XY / 2
            // * 
            // * MODE: Z & 0x2 = 0 Standby
            // *       Z & 0x2 = 2 Auto
            // *       Z & 0x4 = 4 Vane Mode
            // *       Z & 0x8 = 8 Track Mode
            // *
#ifdef DEBUG            
            for(i = 0; i < cmdCount; i++){
              Serial.print(stBuff[i], HEX);
              Serial.print(" ");
            }
            Serial.print("\n\r");
#endif
            u = stBuff[4] & 0x0f; 
            if((u & 0x02) == 0){
              apMode = 0;
            } else {
              if((u & 0x04) == 4){
                apMode = 2;   // steer to wind
                if(apMode != old_apMode){
                  wts = lastAWA;    // set wind angle to steer
                }
              } else {
                if((u & 0x08) == 8){
                  apMode = 3;
                }
                else {
                  apMode = 1;
                }
             } 
            }
            old_apMode = apMode;
            dir = 0;
            if(apMode > 0){
              if((stBuff[1] & 0x80) == 0x80){
                dir = 1;           
              }
              else {
                dir = -1;
              }
            }
            
            if (stBuff[6] > 127) {
              // negative
              rsa = 0.0 - (float)(256 - stBuff[6]);
            }
            else {
              rsa = (float) stBuff[6];
            }

            
            u = stBuff[1] >> 4;
            hdg = ((u & 0x03) * 90) + (stBuff[2] & 0x3f) * 2;
            if((u & 0x4) == 0x4){
              hdg++;
            }
            if((hdg < 0) || (hdg > 360)){
              hdg = 0;
            }

            u = stBuff[2] >> 6;
            cts = u * 90 + (stBuff[3] / 2);

            apAlarm = 0;
            if((stBuff[5] &  0x04) == 0x04){
              apAlarm = 1;
            }
            if((stBuff[5] & 0x08) == 0x08){
              apAlarm = 2;
            }
            if((stBuff[7] & 0x08) == 0x08){
              apAlarm = 3;
            }

#ifdef DEBUG
            dtostrf(rsa, 0, 1, b1);
            sprintf(szOut, "Rudder angle = %s\r\nHeading=%d\r\nAP CTS = %d\r\nMode = %d", b1, hdg, cts, apMode);
            Serial.println(szOut);
#endif
          break;
         
          case 0x20 : // Speed through water
            // 
            //  0  1  2  3
            // 20 01 XX XX
            // 
            // stw = (xx[3] * 256 + xx[2]) / 10 K
            //
             stw = (stBuff[3] * 256 + stBuff[2]) / 10.0;

          break;
          case 0 :  // depth
            //
            //   0  1  2  3  4
            //  00 02 YZ XX XX   Depth  = XXXX / 10 in feet
            //          
            dpt = (stBuff[4] * 256 + stBuff[3]) * 0.3077 / 10.0;
        
          break;
          case 0x25 :   // trip
            
            //  0   1   2   3   4   5  6
            // 25  Z4  XX  YY  UU  VV AW  Total & Trip Log
            //      total= (XX+YY*256+Z* 4096)/ 10 [max=104857.5] nautical miles
            //      trip = (UU+VV*256+W*65536)/100 [max=10485.75] nautical miles
            
            vlw = (stBuff[4] + stBuff[5] * 256 + (stBuff[6] & 0x0f) * 65536) / 100.0;
          break;

          case 0x11 : // Apparent Wind Speed
            
            //  0  1  2  3
            // 11 01 xx 0y     xx & 0x7F + yy & 0x0F/ 10 
            
            aws = (float)(stBuff[2] & 0x7F) + (stBuff[3] &  0x0F) / 2.0;
          break;

          case 0x10 : // ApparentWind Angle - appears always to come before 11 - AWS
            
            //  0  1  2  3
            // 10 01 xx yy     xx * 256 + yy
            
            lastAWA = (stBuff[2] * 256 + stBuff[3]) / 2;
            aveAWA[iCount] = lastAWA;
            iCount++;   // increase count up to 9 then restart at
            iCount %= 5;
            awa = 0;
            for(i = 0; i < 5; i++){
              awa += aveAWA[i];
            }
            awa /= 5;
            if(awa > 360){
              awa = 0;
            }
          break;
            
          case 0x53 : // Course over the ground
            
            //  COG
            //   0  1  2
            //  53 U0 VW
            
            u = stBuff[1] >> 4;
            cog = ((u & 0x03) * 90) + (stBuff[2] & 0x3f) * 2 + (u & 0x0c) / 8; 
          break;
          case 0x52 : // speed over ground
            
            //  SOG
            //   0  1  2  3
            //  52 00 xx xx
            //   SOG = XX[3] * 256 + xx[2] / 10
            
            sog = (stBuff[3] * 256 + stBuff[2]) / 10.0;
          break;
          case 0x85 : 
            //   0   1   2   3  4  5  6  7  8
            //  85  X6  XX  VU ZW ZZ YF 00 yf   Navigation to waypoint information
            //     Cross Track Error: XXX/100 nautical miles
            //      Example: X-track error 2.61nm => 261 dec => 0x105 => X6XX=5_10
            //     Bearing to destination: (U & 0x3) * 90° + WV / 2°
            //      Example: GPS course 230°=180+50=2*90 + 0x64/2 => VUZW=42_6
            //      U&8: U&8 = 8 -> Bearing is true, U&8 = 0 -> Bearing is magnetic
            //     Distance to destination: Distance 0-9.99nm: ZZZ/100nm, Y & 1 = 1
            //                              Distance >=10.0nm: ZZZ/10 nm, Y & 1 = 0
            //     Direction to steer: if Y & 4 = 4 Steer right to correct error
            //                         if Y & 4 = 0 Steer left  to correct error
            //     Example: Distance = 5.13nm, steer left: 5.13*100 = 513 = 0x201 => ZW ZZ YF=1_ 20 1_
            //              Distance = 51.3nm, steer left: 51.3*10  = 513 = 0x201 => ZW ZZ YF=1_ 20 0_
            //     F contains four flags which indicate the available data fields:
            //              Bit 0 (F & 1): XTE present
            //              Bit 1 (F & 2): Bearing to destination present
            //              Bit 2 (F & 4): Range to destination present
            //              Bit 3 (F & 8): XTE >= 0.3nm
            //          These bits are used to allow a correct translation from for instance an RMB sentence which
            //          contains only an XTE value, all other fields are empty. Since SeaTalk has no special value
            //          for a data field to indicate a "not present" state, these flags are used to indicate the
            //          presence of a value.
            //      In case of a waypoint change, sentence 85, indicating the new bearing and distance,
            //      should be transmitted prior to sentence 82 (which indicates the waypoint change).
            //  85 a6 bc ZW ZZ YF 00 yf
            // 
            //           XTE = (bc * 256 + a)/ 100
            
             xteValid = ((stBuff[6] & 0x01) == 1);
            btw = (stBuff[3] & 0x03) * 90 + ((stBuff[4] & 0x0f) * 16 + (stBuff[3] >> 4)) / 2;

            ui16 =(stBuff[5] * 16) + (stBuff[4] >> 4);
            
            if( (stBuff[6] & 0x10) == 0x10 ){
              dtw = ui16 /100.0;
            }
            else {
              dtw = ui16 / 10.0;
            }
             
            if((stBuff[6] & 0x02) == 0x02){
              btwValid = true;
             }
            else {
                btwValid = false;
            }
          break;
          case 0xAC :
               
                  // XTE
                  // AC K2 XX YY CS
                  // K & 1 = 1 steer left
                  //       = 0 steer right
                  // K & 2 = 2 XTE valid
                  // xte = YYXX / 1000
                         
 //           xteValid = ((stBuff[1] & 0x20) == 0x20);
            if( xteValid ){
              xte = (stBuff[3] * 256 + stBuff[2]);
              if((stBuff[1] & 0x10) == 0){
               xte = 0.0 - xte;
             }
            }
          break;
          default : // all the rest
            // reset command buffer
            for(i = 0; i < cmdCount; i++){
              stBuff[i] = 0;
            }
          break;
        }
        // we've read all chars in this command so reset pointers - ready to start again
        bufCount= 0;
        bCmd = false;
        cmdCount = 0;

       }
     }
   }
}


void sendCMD(int cmd){

uint8_t stCmd [10][4] = {
                0x86, 0x21, 0x02, 0xfd,            // standby
                0x86, 0x21, 0x05, 0xfa,            // -1
                0x86, 0x21, 0x01, 0xfe,            // auto
                0x86, 0x21, 0x07, 0xf8,            // +1
                0x86, 0x21, 0x06, 0xf9,            // -10
                0x86, 0x21, 0x23, 0xdc,            // wind
                0x86, 0x21, 0x08, 0xf7,            // +10
                0x86, 0x21, 0x21, 0xde,            // tack (-1 + -10)
                0x86, 0x21, 0x03, 0xfc,            // track
                0x86, 0x21, 0x22, 0xdd};           // tack (+1 + +10)
                
  switch(cmd){
    case 0 :
      txtDiagLog.printf("Standby\n");
      Serial.println("Standby ");
    break;
    case 1 :
      Serial.println("-1 ");
    break;
    case 2 : 
      txtDiagLog.printf("Auto\n");
      Serial.println("Auto ");
    break;
    case 3 :
      Serial.println("+1 ");
    break;
    case 4 :
      Serial.println("-10 ");
    break;
    case 5 :
      txtDiagLog.printf("Wind\n");
      Serial.println("Wind ");
    break;
    case 6 :
      Serial.println("+10 ");
    break;
    case 7 :
      Serial.println("Tack port ");
    break;
    case 8 :
      txtDiagLog.printf("Track\n");
      Serial.println("Track ");
    break;
    case 9 :
      Serial.println("Tack Stbd ");
    break;
    default :
      Serial.println("Cmd out of range in seatack.cpp sendCMD()");
      return;
    break;
  }
  //DCB disabled due to corruption in debug display - it it this call?? 
  send2ST(stCmd[cmd]);
}

void send2ST(uint8_t cmd[]){
  CheckBus();
  digitalWrite(TX_LED, LOW );
  for( int i = 0; i < 4; i++){
    (i == 0) ? mySerial.write(cmd[i], SWSERIAL_PARITY_MARK) : mySerial.write(cmd[i], SWSERIAL_PARITY_SPACE);
  }
  delay(100);
  digitalWrite(TX_LED, HIGH);
}

// wait line idle for 7 x 256 micro secs (1.8mS) 
void CheckBus ( void ){

  for(int cX = 0; cX < 255; cX++ ){
    // Reset the wait time if the RX line is active. For DCB's (Raynarine's) Seatalk electronics, 
    // the RX line is active low, so reset the wait count if the RX_MON is low.
    if(digitalRead(RX_MON) == 0 ){
      cX = 0;                         
    }    
    delayMicroseconds(7);   
  }
}

void Seatalk_Init() {

  queue = xQueueCreate(10, sizeof(uint8_t));

  if(queue != NULL){
    Serial.println("Queue created");
  }
  
  // Now set up tasks to run independently.
  // ESP32 core 0 is used for WiFI, and i've had problems with ST data recieved. 
  // trying this task on core 1 (application core)
  xTaskCreatePinnedToCore(
    readST
    ,  "read SeaTalk"   // A name just for humans
    ,  2048 // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  configMAX_PRIORITIES-10 // Priority, with 3 (config MAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);

  Serial.println("Seatalk Init done");
}
