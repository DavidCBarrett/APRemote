
#include <SPIFFS.h>
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
//#include <ESPAsyncWiFiManager.h>
#include <WiFiManager.h>

#include "main.h"
#include "SeaTalk.h"
#include "ApRemote_GSLC_Externs.h"

#define APSSID "AutoPilot Remote"

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");
DNSServer dns;
AsyncWiFiManager wifiManager(&server,&dns);

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
        gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "WebSocket client #%u disconnected\n", client->id());
      } break;
 
    // New client has connected
    case WS_EVT_CONNECT: {
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
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
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiStatus,  "Connected");
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiSSID,    "%s", WiFi.SSID());
//      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiIp,      "%s", WiFi.localIP().toString());
      break;
		case WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.print("WiFi Disconnected. Reason: ");
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiStatus, "Disconnected");
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
  Serial.printf("Entered config mode, AP=%s\n", WiFi.softAPIP());
  gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "Entered config mode, AP=%s\n", WiFi.softAPIP().toString());

  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  
  ApGslc_Update();
}

void ApWiFi_Connect() {
  wifiManager.setConfigPortalTimeout(4);  // WiFi config portal time out set to 4 secs
  wifiManager.setTryConnectDuringConfigPortal(false);

  // set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  // fetches ssid and pass and tries to connect
  // if it does not connect it starts an access point with the specified name
  // as per the "#define APSSID ..."" and goes into a blocking loop awaiting configuration
  if (wifiManager.autoConnect(APSSID)) {
    
    // if you get here you have connected to WiFi
    Serial.println("Connected to WiFI.");
    
    gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus,  (char*)"\nConnected to WiFI.");
    gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, 
      "Connected to WiFI.\n SSID %s with pwd: %s", WiFi.SSID(), "TBC");
    gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiIp,      "%s", WiFi.localIP().toString());


    // function to send web page to client defined here (using some c++ magic i don't yet understand...)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      mySerial.enableRx(false);
      IPAddress Ip = request->client()->remoteIP();
      Serial.println("[" + Ip.toString() + "], requested " + request->url());
    
      Serial.printf("[%s], requested %s", Ip.toString(), request->url());
      gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "[%s], requested %s", Ip.toString(), request->url());

      request->send(SPIFFS, "/index.html", "text/html");
    });

    // define how to serve up all other files requested by the client broswer (from the Filesystem (css, js, ...))
    server.serveStatic("/", SPIFFS, "/");

    // ling the getData request to the get data function handling HTTP GET request (received every second to update client display details)
    server.on("/getData", HTTP_GET, getData);
    
    server.onNotFound(notFound);

    webSocket.onEvent(onWebSocketEvent);    // Assign  WebSocket callback
    server.addHandler(&webSocket);
    server.begin();
  }
  else {
    // Failed to connect to WiFi
    Serial.println("failed to connect and hit timeout");
    gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, 
      "Failed to connect to WiFI.\n SSID %s PWD: %s", WiFi.SSID(), "TBC");
  }

}

void ApWiFi_Init() {

  if(!SPIFFS.begin(true)){
     Serial.println("SPIFFS Setup Error");
     return;
   }

  gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "WiFi Diag\n");

  gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiStatus, "Disconnected");

  wifiManager.setDebugOutput(true);

  wifiManager.setconfigportal
// Set WiFi to station mode and disconnect from an AP if it was previously connected
//   WiFi.begin();
//   delay(500);
//   WiFi.disconnect();
//   delay(100);

  // handler for WiFi eventns (connect and disconnect events).
  WiFi.onEvent(onWifiEvent);

  //reset settings - uncomment for testing
  //wifiManager.resetSettings();

  ApWiFi_Connect();
}

void APWiFi_Tick() {
    
  webSocket.cleanupClients();

}

void APWiFi_ConfigPortal() {

  WiFi.disconnect();
  delay(100);

  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nEntering WiFi AP Mode");  
  gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "Entering WiFi AP Mode\n");

  wifiManager.setConfigPortalTimeout(60);               // WiFi config portal time out set to 60 secs
  wifiManager.setTryConnectDuringConfigPortal(false);
  wifiManager.startConfigPortal(APSSID);

  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nExiting WiFi AP Mode");
  gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "Exiting WiFi AP Mode\n");

   ApWiFi_Connect();
}