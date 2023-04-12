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

*********/

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include "ApRemote_GSLC_Externs.h"

#include "DCBWiFiManager.h"

// AsyncWebServer to use ...
AsyncWebServer* _server;

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";

String _apssid;

//Variables to save values from HTML form
String _ssid;
String _pass;
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long configPortalPreviousMillis  = 0;
unsigned long configPortalTimeoutMillis   = 120;        // seconds to run Wifi manager's AP config portal 
unsigned long configPortalStartTimeMillis = millis();
bool          portalRunning               = false;
bool          startAP                     = false;      // start AP and webserver if true, else start only webserver

DCBWiFiManager::DCBWiFiManager(AsyncWebServer* server, const char* APSSID) : StateMachine(ST_MAX_STATES) {

if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");

_apssid = APSSID;
  _server = server;
  
  // Load values saved in SPIFFS
  _ssid = readFile(SPIFFS, ssidPath);
  _pass = readFile(SPIFFS, passPath);
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(_ssid);
  Serial.println(_pass);
  Serial.println(ip);
  Serial.println(gateway);

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

//
// external events taken by this state machine
//

void DCBWiFiManager::OnUserConnectRequest() {
   // given the OnUserConnectRequest event, transition to a new state based upon 
   // the current state of the state machine - real work is done in the ST_XXX functions
    BEGIN_TRANSITION_MAP                            // - Current State -
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_ConnectingToSTA
        TRANSITION_MAP_ENTRY (ST_CONNECTINGTOSTA)   // ST_APMode
        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_STAMode

    END_TRANSITION_MAP(NULL)
}

void DCBWiFiManager::OnUserDisconnectRequest() {
   // given the OnUserConnectRequest event, transition to a new state based upon 
   // the current state of the state machine - real work is done in the ST_XXX functions
    BEGIN_TRANSITION_MAP                            // - Current State -
        TRANSITION_MAP_ENTRY (ST_APMODE)            // ST_ConnectingToSTA
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)        // ST_APMode
        TRANSITION_MAP_ENTRY (ST_APMODE)            // ST_STAMode

    END_TRANSITION_MAP(NULL)
}

// void DCBWiFiManager::ST_ConnectingToSTA(EventData* pData) {}
// void DCBWiFiManager::ST_APMode(EventData* pData) {}
// void DCBWiFiManager::ST_STAMode(EventData* pData) {}

STATE_DEFINE(DCBWiFiManager,     ConnectingToSTA,    NoEventData) {}
STATE_DEFINE(DCBWiFiManager,     APMode,             NoEventData) {}
STATE_DEFINE(DCBWiFiManager,     STAMode,            NoEventData) {}

// Initialize WiFi
bool DCBWiFiManager::initWiFi() {
  if(_ssid=="" || ip==""){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());


  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(_ssid.c_str(), _pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  configPortalPreviousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - configPortalPreviousMillis >= configPortalTimeoutMillis) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

void DCBWiFiManager::setConfigPortalTimeout(unsigned long seconds) {
  configPortalTimeoutMillis = seconds*1000;
}

// the client's function to call when wifi connects, to do client specific post connection (e.g. webserver) setup
void DCBWiFiManager::setWiFiConnectedCallback(std::function<void()> func)
{
  _wificonnectedcallback = func;
}

void DCBWiFiManager::resetSettings(){

  // Reset settings by deleting the connection files
  if(SPIFFS.exists(ssidPath)) SPIFFS.remove(ssidPath);
  if(SPIFFS.exists(passPath)) SPIFFS.remove(passPath);
  if(SPIFFS.exists(ipPath)) SPIFFS.remove(ipPath);
  if(SPIFFS.exists(gatewayPath)) SPIFFS.remove(gatewayPath);
}

void DCBWiFiManager::disconnectWiFi() {
  
  _server->end();
  WiFi.disconnect();
}

void DCBWiFiManager::ConfigPortal() {
    Serial.println("DCBWiFiManager_ConfigPortal");

      // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
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

void DCBWiFiManager::setup(AsyncWebServer* server, const char* APSSID) {
  
  if(initWiFi()) {
    Serial.println("DCB says WIFI Connected with saved params");

    // notify client we connected to wifi, calling their conneted function
    if (_wificonnectedcallback != NULL)
    {
      _wificonnectedcallback();
    }

    // Start the web_server->
    _server->begin();
  }
  else {
    // Launch the config portal to get WiFi connection parameters.
    this->ConfigPortal();
  }
}

void DCBWiFiManager::process() {

}
