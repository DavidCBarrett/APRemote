/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-wi-fi-manager-asyncwebserver/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

Main Changes - make this simple wifi manager non-blocking and integrated into main application's loop & code. 
The main app should happily work with:
  a. the ESP32 as the access point - in APMode (i.e. when there is no station about cause you're on the boat), 
  b. or if the user has configured an SSID & Pwd that connect, the main app works in station mode  - in STAMode 

To do the above, moving WiFi Manager to be based on a statemachine. See here https://www.codeproject.com/Articles/1087619/State-Machine-Design-in-Cplusplus-2 
States are:
  ST_APMODE                         in this state, nothing to do but service any wifi objects
  ST_CONNECTINGTOSTA                in this state, try and connect to STA with supplied ssid & pwd, if succeed, fail, or timeout then transition.
  ST_STAMODE                        in this state, nothing to do but service any wifi objects

initial state: 
  is ST_CONNECTINGTOSTA             after power on.

state transitions:
  ST_CONNECTINGTOSTA -> ST_STAMODE  due to succesfull connection to the speciifed station.
  ST_CONNECTINGTOSTA -> ST_APMODE   due to failing to connect to specified station, maybe a timeout, or max retries
  ST_APMODE  -> ST_CONNECTINGTOSTA  due to "OnUserConnectRequest" (typically after they have configured a stations ssid & pwd)
  ST_STAMODE -> ST_CONNECTINGTOSTA  due to Wifi randomly disconnects (e.g. signal drop out) This starts ESP32 to Station reconnection attempt(s).
  ST_STAMODE -> ST_APMODE           due to "OnUserDisconnectRequest"

External events:
  OnUserConnectRequest          Move from AP to STA mode, and try and connect with saved ssid and pwd
  OnUserDisconnectRequest       disconnect from any station, enter APMode.

Using Timoutout libaray from https://github.com/tfeldmann/Arduino-Timeout

*********/
#include "DCBWiFiManager.h"

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

#include "ApRemote_GSLC_Externs.h"

DCBWiFiManager::DCBWiFiManager(AsyncWebServer* server, const char* APSSID) : StateMachine(ST_MAX_STATES) {

  _apssid = APSSID;
  _server = server;
  
  if (SPIFFS.begin(true)) {
    // Load values saved in SPIFFS
    _ssid   = readFile(SPIFFS, ssidPath);
    _pass   = readFile(SPIFFS, passPath);
    ip      = readFile(SPIFFS, ipPath);
    gateway = readFile(SPIFFS, gatewayPath);

    Serial.printf("From SPIFFS - SSID:%s, PWD: %s, IP: %s, Gateway: %s\n ", _ssid, _pass, ip.c_str(), gateway.c_str());
  }
  else {
    Serial.println("DCBWiFiManager::DCBWiFiManager An error has occurred while mounting SPIFFS");
  }
}

//
// external events taken by this state machine
//

void DCBWiFiManager::OnUserConnectRequest() {
   // given the OnUserConnectRequest event, transition to a new state based upon 
   // the current state of the state machine - real work is done in the ST_XXX functions
    BEGIN_TRANSITION_MAP                            // - Current State -
        TRANSITION_MAP_ENTRY (ST_CONNECTINGTOSTA)   // ST_BOOTUP
        TRANSITION_MAP_ENTRY (ST_CONNECTINGTOSTA)   // ST_APMODE
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_CONNECTINGTOSTA
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_STAMODE
    END_TRANSITION_MAP(NULL)
}

void DCBWiFiManager::OnUserDisconnectRequest() {
   // given the OnUserConnectRequest event, transition to a new state based upon 
   // the current state of the state machine - real work is done in the ST_XXX functions
    BEGIN_TRANSITION_MAP                            // - Current State -
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_BOOTUP
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)        // ST_APMODE
        TRANSITION_MAP_ENTRY (ST_APMODE)            // ST_CONNECTINGTOSTA
        TRANSITION_MAP_ENTRY (ST_APMODE)            // ST_STAMODE
    END_TRANSITION_MAP(NULL)
}

void DCBWiFiManager::poll() {
   // hopefully this will just poll the current state, calling the relevant STATE_DEFINE function below.
    BEGIN_TRANSITION_MAP                            // - Current State -
        TRANSITION_MAP_ENTRY (ST_BOOTUP)            // ST_BOOTUP
        TRANSITION_MAP_ENTRY (ST_APMODE)            // ST_APMODE
        TRANSITION_MAP_ENTRY (ST_CONNECTINGTOSTA)   // ST_CONNECTINGTOSTA
        TRANSITION_MAP_ENTRY (ST_STAMODE)           // ST_STAMODE
    END_TRANSITION_MAP(NULL)
}

STATE_DEFINE(DCBWiFiManager,     Bootup,                  NoEventData) {
  // Nothing to do.
}

ENTRY_DEFINE(DCBWiFiManager,     EntryAPMode,             NoEventData) {
  // Setup AP Mode.
  Serial.println("EntryAPMode");
  
  // Ensure disconnected from any WiFi Stations, and set up ApMode.
  WiFi.disconnect();
  WiFi.mode(WIFI_MODE_AP);
  
  // Start WiFi in AP mode for clients to connect to.
  Serial.println("Setting AP (Access Point)");
  WiFi.softAP(_apssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); 

  // Web Server Root URL
  _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/wifimanager.html", "text/html");
  });
  
  _server->serveStatic("/", SPIFFS, "/");
  
  _server->on("/", HTTP_POST, [this](AsyncWebServerRequest *request) {
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        // HTTP POST ssid value
        if (p->name() == PARAM_INPUT_1) {
          _ssid = p->value().c_str();
          Serial.print("SSID set to: ");
          Serial.println(_ssid);
          // Write file to save value
          writeFile(SPIFFS, ssidPath, _ssid.c_str());
        }
        // HTTP POST _pass value
        if (p->name() == PARAM_INPUT_2) {
          _pass = p->value().c_str();
          Serial.print("Password set to: ");
          Serial.println(_pass);
          // Write file to save value
          writeFile(SPIFFS, passPath, _pass.c_str());
        }
        // HTTP POST ip value
        if (p->name() == PARAM_INPUT_3) {
          ip = p->value().c_str();
          Serial.print("IP Address set to: ");
          Serial.println(ip);
          // Write file to save value
          writeFile(SPIFFS, ipPath, ip.c_str());
        }
        // HTTP POST gateway value
        if (p->name() == PARAM_INPUT_4) {
          gateway = p->value().c_str();
          Serial.print("Gateway set to: ");
          Serial.println(gateway);
          // Write file to save value
          writeFile(SPIFFS, gatewayPath, gateway.c_str());
        }
        //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
    delay(3000);
    ESP.restart();
  });
  _server->begin();

  gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiStatus,  "AP Mode");
  gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiSSID,    "%s", _apssid.c_str());
  gslc_ElemSetTxtPrintf(&m_gui, m_pElemTextWifiIp,      "%s", WiFi.softAPIP().toString());
}

STATE_DEFINE(DCBWiFiManager,     APMode,                  NoEventData) {}

GUARD_DEFINE(DCBWiFiManager,     GuardConnectingToSTA,   NoEventData) {
 
  IPAddress localIP, localGateway;
  IPAddress subnet(255, 255, 0, 0);
 
  // if no SSID or IP provided, don't proceed
  if(_ssid=="" || ip==""){
      Serial.println("GuardConnectingToSTA::Undefined SSID or IP address.");
      return FALSE; // note use of upper BOOL, TRUE and FALSE in GUARD functions.
  }

  // Move to station mode, & configure, only proceed to ST_CONNECTINGTOSTA if this succeeds.
  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());

  // if configuring WiFi fails, don't proceed.
  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("GuardConnectingToSTA::STA Failed to configure");
    return FALSE;
  }

  // STA preparations successful, proceed
  return TRUE;
}

ENTRY_DEFINE(DCBWiFiManager,     EntryConnectingToSTA,    NoEventData) {
  // Attempt connecion with provided info.
  Serial.println("EntryConnectingToSTA::Connecting to WiFi...");
  WiFi.begin(_ssid.c_str(), _pass.c_str());

  // start the connection timer.
  WifiConnectTimeout.start(connectionlTimeout_ms);
}

STATE_DEFINE(DCBWiFiManager,     ConnectingToSTA,         NoEventData) {
  // check for connection success, or timeout.
  if(WiFi.status() == WL_CONNECTED) {

    Serial.printf("ConnectingToSTA::Connected to STA @ %s\n", WiFi.localIP().toString());
    // notify client we connected to wifi, calling their conneted function
    if (_wificonnectedcallback != NULL)
    {
      _wificonnectedcallback();
    }

    // Start the web_server
    _server->begin();

    //Connecition Success - move to ST_STAMODE
    InternalEvent(ST_STAMODE);
  }
  else {
    // check for connection timeout
    if (WifiConnectTimeout.time_over()) {
      Serial.printf("ConnectingToSTA::Connection to %s timeout.\n", _ssid);

      //Connecition Timed out - move to ST_STAMODE
      InternalEvent(ST_APMODE);
    }

    // we haven't connected or timed out yet... just wait...
  }
}

STATE_DEFINE(DCBWiFiManager,     STAMode,                 NoEventData) {}


void DCBWiFiManager::resetSettings(){

  // Reset settings by deleting the connection files
  if(SPIFFS.exists(ssidPath)) SPIFFS.remove(ssidPath);
  if(SPIFFS.exists(passPath)) SPIFFS.remove(passPath);
  if(SPIFFS.exists(ipPath)) SPIFFS.remove(ipPath);
  if(SPIFFS.exists(gatewayPath)) SPIFFS.remove(gatewayPath);
}


// Read File from SPIFFS
String DCBWiFiManager::readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to SPIFFS
void DCBWiFiManager::writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}
