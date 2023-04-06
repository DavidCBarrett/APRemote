
#include <SPIFFS.h>
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

#include "main.h"
#include "SeaTalk.h"
#include "ApRemote_GSLC_Externs.h"

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");
DNSServer dns;

// Callback: receiving any WebSocket message
void onWebSocketEvent(AsyncWebSocket       *server,     //
                      AsyncWebSocketClient *client,     //
                      AwsEventType          type,       // the signature of this function is defined
                      void                 *arg,        // by the `AwsEventHandler` interface
                      uint8_t              *payload,    //
                      size_t                length) {   //

  // Figure out the type of WebSocket event
  switch(type) {
 
    // Client has disconnected
    case WS_EVT_DISCONNECT: {
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
      } break;
 
    // New client has connected
    case WS_EVT_CONNECT: {
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    }  break;
 
    // Handle text messages from client
    case WS_EVT_DATA: {
      // Print out raw message
      Serial.printf("[%u] Received text: %s\r\n", client->id(), payload);
      newCmd = payload[0] - '0';
      xQueueSend(queue, &newCmd, portMAX_DELAY);
      } break;
 
    // For everything else: do nothing
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void getData(AsyncWebServerRequest *request) {

  uint16_t iwts;
  
  String APdata, L1, L2, L3, L4, sRSA, sAWA, sXTE, sWTS, sALM, xteUnit;
  String sBTW, sDTW, sLeft, sRight;
 
  L1 = "led_off";
  L2 = "led_off";
  L3 = "led_off";
  L4 = "led_off";

  switch(dir){
    case 1 :
      sLeft = "<";
      sRight = "&nbsp;";
    break;
    case 0 :
      sLeft ="&nbsp;";
      sRight = "&nbsp;";
    break;
    case -1 :
      sLeft ="&nbsp;";
      sRight = ">";
    break;
  }

  if(xteValid){
    xteUnit = " Nm";
    if(abs(xte) < 160){
      xteUnit = " Ft";
      sXTE = ">>" + String(xte * 6, 0) + xteUnit;
      if(xte < 0){
        sXTE = String(abs(xte * 6), 0) + xteUnit + "<<";
      }
     } else {
      
      sXTE = ">>" + String(xte / 1000, 2) + xteUnit;
      if(xte < 0){
        sXTE = String(abs(xte / 1000), 2) + xteUnit + "<<";
      }
    }
  }
  else{
    sXTE = String("---");
  }
  if(btwValid){
    sDTW = String(dtw);
    sBTW = String(btw);
    
  }
  else {
    sBTW = "---";
    sDTW = "---";
  }

  sAWA = "S";
  if (awa > 180){
    awa = 360 - awa;
    sAWA = "P";
  }
  sAWA = String(awa) + sAWA;

  if(apMode == 2){
    sWTS = "S";
    iwts = wts;
    if (wts > 180){
      iwts = 360 - wts;
      sWTS = "P";
    }
    sWTS = String(iwts) + sWTS;
  }

  sRSA = "S";
  if (rsa < 0){
    rsa = abs(rsa);
    sRSA = "P";
  }  
  sRSA = sRSA + String((int)rsa);

  switch(apAlarm) {
    case 0 :
      sALM = " ";
    break;
    case 1 :
      sALM = "OFF COURSE";
    break;
    case 2 :
      sALM = "WIND SHIFT";
    break;
    case 3 :
      sALM = "NO DATA";
    break;
  }

#ifdef DEBUG
  Serial.print(apMode);
#endif
  
  APdata = "{\"hdg\":" + String(hdg);
  APdata += ",\"cts\":" + String(cts);
  if (apMode < 2) { 
    APdata += ",\"hdgInfo\":\"&nbsp;\"";
  }
  if (apMode == 2) {
    APdata += ",\"hdgInfo\":\"" + sWTS + "\"";
  }
  if (apMode == 3) { 
    APdata += ",\"hdgInfo\":\"" + sXTE + "\""; 
  } 
  APdata += ",\"rsa\":\"" + sRSA + "\"";
  APdata += ",\"sog\":" + String(sog);
  APdata += ",\"cog\":" + String(cog);
  APdata += ",\"awa\":\"" + sAWA + "\"";
  APdata += ",\"xte\":\"" + sXTE + "\"";
  APdata += ",\"aws\":" + String(aws);
  APdata += ",\"vlw\":" + String(vlw);
  APdata += ",\"dpt\":" + String(dpt);
  APdata += ",\"stw\":" + String(stw);
  APdata += ",\"dtw\":\"" + sDTW + "\"";
  APdata += ",\"btw\":\"" + sBTW + "\"";
  APdata += ",\"left\":\"" + sLeft + "\"";
  APdata += ",\"right\":\"" + sRight + "\"";
 
  switch(apMode){
    case 0 : 
      L1 = "led_on";   
    break;
    case 1 :
      L2 = "led_on";
    break;
    case 2 : 
      L3 = "led_on";   
    break;
    case 3 :
      L4 = "led_on";
    break;
  }

  APdata += ",\"led0\":\"" + L1 + "\"";
  APdata += ",\"led1\":\"" + L2 + "\"";
  APdata += ",\"led2\":\"" + L3 + "\"";
  APdata += ",\"led3\":\"" + L4 + "\"";
  APdata += ",\"alm\":\"" + sALM + "\"";
  APdata += "}";
 
  // Send Autopilot data string to update the users view. 
  // see the requestData function in index.htlm
  request->send(200, "text/plain", APdata); 

}  

void onWifiEvent(WiFiEvent_t event) {
 switch (event) {
		case WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED:
			Serial.println("Connected or reconnected to WiFi");
			break;
		case WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("WiFi Disconnected. Reason: ");
//      status("WiFI Disconnected");
     // Serial.println(info.wifi_sta_disconnected.reason)
			Serial.println("Enabling WiFi autoconnect");
			WiFi.setAutoReconnect(true);
			break;
		default: break;
  }
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}


//gets called when WiFiManager enters configuration mode
void configModeCallback (AsyncWiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  
  ApGslc_Update();
}

void ApWiFi_Init() {

     if(!SPIFFS.begin(true)){
     Serial.println("SPIFFS Setup Error");
     return;
   }

  //WiFiManager
  AsyncWiFiManager wifiManager(&server,&dns);

// Set WiFi to station mode and disconnect from an AP if it was previously connected
//   WiFi.begin();
//   delay(500);
//   WiFi.disconnect();
//   delay(100);

  // handler for WiFi eventns (connects and disconnect events).
  // dcb WiFi.onEvent(onWifiEvent);

  //reset settings - uncomment for testing
  //wifiManager.resetSettings();

  wifiManager.setConfigPortalTimeout(2);  // WiFi config portal time out set to 2 secs
  wifiManager.setTryConnectDuringConfigPortal(false);
  wifiManager.setDebugOutput(true);

  // set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
//dcb  wifiManager.setAPCallback(configModeCallback);

  // fetches ssid and pass and tries to connect
  // if it does not connect it starts an access point with the specified name
  // "AutoPilot Remote" and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("AutoPilot Remote")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    //ESP.restart();
    //delay(1000);
  }

  // if you get here you have connected to the WiFi
  Serial.println("Connected to WiFI.");
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"Connected to WiFI.");

 // Send web page to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    mySerial.enableRx(false);
    IPAddress Ip = request->client()->remoteIP();
    Serial.println("[" + Ip.toString() + "], requested " + request->url());
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // serve up all other files requested by the broswer in the Filesystem (css, js, ...)
  server.serveStatic("/", SPIFFS, "/");

    
  // Receive an HTTP GET request every second to update display details
  server.on("/getData", HTTP_GET, getData);
   
  server.onNotFound(notFound);

  webSocket.onEvent(onWebSocketEvent);    // Assign  WebSocket callback
  server.addHandler(&webSocket);
  server.begin();

}

void APWiFi_Tick() {
    
  webSocket.cleanupClients();

}