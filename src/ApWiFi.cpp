
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "main.h"
#include "SeaTalk.h"
#include "ApRemote_GSLC_Externs.h"
#include "DCBWiFiManager.h"
#include "EnumsToStrings.h"

#define APSSID "AutoPilot Remote"

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");
//DNSServer dns;

DCBWiFiManager wm(&server, APSSID);

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
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiIp,      "%s", WiFi.localIP().toString());
      break;

		case WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi Disconnected.");
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiStatus, "Disconnected");
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiSSID,    " ");
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiIp,      " ");
			wm.OnUserDisconnectRequest();
			break;
      
		default: 
      Serial.printf("Event ID = %s\n", WiFiEvent_tToString(event));
      gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextboxWiFiDiag, "Event ID = %s\n", WiFiEvent_tToString(event));
      break;
  }
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void WiFiConnectedCallback() {
    // if you get here you have connected to WiFi
    gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus,  (char*)"\nConnected to WiFI.");
    gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, 
      "Connected to WiFI.\n SSID %s\n with pwd: %s\n", WiFi.SSID(), wm.getConfiguredSTAPassword());
}

void ApWiFi_Setup() {

  gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, "WiFi Diag\n");
  gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiStatus, "Disconnected");

  // Setup the Webserver, ready for connections...
  // Lambda function route to send web page to client defined in request->send below
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    mySerial.enableRx(false);
    Serial.printf("[%s], requested %s", request->client()->remoteIP().toString(), request->url());
    gslc_ElemXTextboxPrintf(&m_gui, m_pElemTextboxWiFiDiag, 
      "[%s], requested %s", request->client()->remoteIP().toString(), request->url());

    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Define how to serve up all other files requested by the client broswer (from the Filesystem (css, js, ...))
  server.serveStatic("/", SPIFFS, "/");

  // Handling the getData request using the getData function handling HTTP GET request (received every second to update client display details)
  server.on("/getData", HTTP_GET, getData);
  
  server.onNotFound(notFound);

  // Assign  WebSocket callback
  webSocket.onEvent(onWebSocketEvent);                    
  server.addHandler(&webSocket);
 
  // handler for WiFi events (connect and disconnect events).
  WiFi.onEvent(onWifiEvent);                              

  wm.setWiFiConnectedCallback(WiFiConnectedCallback);
 
  // give WiFiManager a kick to start the state machine...
  wm.OnUserConnectRequest();
}

void APWiFi_Loop() {
    
  webSocket.cleanupClients();

  wm.poll();  // poll / process the statemachine.
}
