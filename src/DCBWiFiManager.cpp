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

#include "main.h"
#include "GSLC_Helpers.h"

#define DNS_PORT 53

DCBWiFiManager::DCBWiFiManager(AsyncWebServer* server, const char* APSSID) : StateMachine(ST_MAX_STATES) {
  _apssid = APSSID;
  _server = server;
}

void DCBWiFiManager::setup(){

  deserializeJson(DefaultJsonWiFiCredentials, DefaultJsonWiFiCredentialsCstr);

  if (SPIFFS.begin(true)!=true) {
    Serial.println("DCBWiFiManager::DCBWiFiManager error mounting SPIFFS, loading defaults");
    deserializeJson(JsonWiFiCredentials, DefaultJsonWiFiCredentialsCstr);
    return;
  }

  // if (e.g. on first start) the credentials files doesn't exist, create it.
  if(!SPIFFS.exists(JsonWiFiCredentialsPath))
    clearWiFiCredentials();
  
  // Load values saved in SPIFFS
  loadWiFiCredentials(&JsonWiFiCredentials);

  // Web Server setup. Root URL belongs to the application. the wifimanager.html page is a website page served up 
  // by "serveStatic("/", SPIFFS, "/")"" set up the applicaiton.
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
  
  if(WiFi.softAP(_apssid.c_str())) {
    Serial.printf("AP IP address: %s\r\n", WiFi.softAPIP().toString().c_str());

    txtWiFiStatus.printf("AP Mode");
    txtWiFiSSID.printf("%s", _apssid.c_str());
    txtWiFiIp.printf("%s", WiFi.softAPIP().toString().c_str());

    if (!dnsServer)
    {
      dnsServer = new DNSServer();
    }

    _server->begin();

    //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1
    if (_server && dnsServer)
    {
      // CaptivePortal
      // if DNSServer is started with "*" for domain name, it will reply with provided IP to all DNS requests
      dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());
    }
  }
  else{
    // Starting AP mode failed....
    txtWiFiDiag.printf("WM::EntryAPMode - Starting AP Mode failed");
  }  
}

STATE_DEFINE(DCBWiFiManager,     APMode,                  NoEventData) 
{
  if (dnsServer) dnsServer->processNextRequest();
}

GUARD_DEFINE(DCBWiFiManager,     GuardConnectingToSTA,   NoEventData) {
 
  IPAddress localIP, localGateway;
  IPAddress subnet(255, 255, 0, 0);
 
  // if no SSID or IP provided, don't proceed, fall back to AP mode.
  if(JsonWiFiCredentials["MsgBody"][0]["SSID"]==""){
      Serial.println("GuardConnectingToSTA::Undefined SSID entering ApMode");
      InternalEvent(ST_APMODE);
      return FALSE; // note use of upper BOOL, TRUE and FALSE in GUARD functions.
  }
  else{
      Serial.printf("SSID[0] = %s\r\n", JsonWiFiCredentials["MsgBody"][0]["SSID"].as<const char*>());
      Serial.printf("Pwd[0]  = %s\r\n", JsonWiFiCredentials["MsgBody"][0]["Pwd"].as<const char*>());
  }

  // Move to station mode, & configure, only proceed to ST_CONNECTINGTOSTA if this succeeds.
  WiFi.mode(WIFI_STA);
  localIP.fromString(staip.c_str());
  localGateway.fromString(gateway.c_str());

  // if configuring WiFi fails, don't proceed.
  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("GuardConnectingToSTA::STA Failed to configure, entering ApMode");
    InternalEvent(ST_APMODE);
    return FALSE;
  }

  // STA preparations successful, proceed
  return TRUE;
}

ENTRY_DEFINE(DCBWiFiManager,     EntryConnectingToSTA,    NoEventData) {
  // Attempt connecion with provided info.
  Serial.println("EntryConnectingToSTA::Connecting to WiFi...");
  WiFi.begin(JsonWiFiCredentials["MsgBody"][0]["SSID"].as<const char*>(), JsonWiFiCredentials["MsgBody"][0]["Pwd"].as<const char*>());

  // start the connection timer.
  WifiConnectTimeout.start(connectionTimeout_ms);
}

STATE_DEFINE(DCBWiFiManager,     ConnectingToSTA,         NoEventData) {
  // check for connection success, or timeout.
  wl_status_t status = WiFi.status();
  if(status==WL_CONNECTED) {

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
      Serial.printf("ConnectingToSTA::Connection to %s timeout.\n", JsonWiFiCredentials["MsgBody"][0]["SSID"].as<const char*>());
  
      //Connecition Timed out - move to ST_STAMODE
      InternalEvent(ST_APMODE);
    }

    // we haven't connected or timed out yet... just wait...
  }
}

STATE_DEFINE(DCBWiFiManager,     STAMode,                 NoEventData) {
  // Nothing to do...
}

bool DCBWiFiManager::saveWiFiCredentials(StaticJsonDocument<200> doc) {
  JsonWiFiCredentials = doc;
  File file = SPIFFS.open(JsonWiFiCredentialsPath, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return false;
  }

  // Msg given should be saveWiFiCredentials, replace with WiFiCredentials in the file on disk...
  doc["Msg"] = "WiFiCredentials";
  serializeJson(doc, file);
  file.close();
  return true;
}

bool DCBWiFiManager::loadWiFiCredentials(StaticJsonDocument<200> *doc) {

  StaticJsonDocument<0> doc2, filter;

  JsonWiFiCredentials.clear();
  
  File file = SPIFFS.open(JsonWiFiCredentialsPath, FILE_READ);

  // if we can't open the file, return default credentials
  if(!file){
    Serial.println("- failed to open file for reading");
    deserializeJson(DefaultJsonWiFiCredentials, DefaultJsonWiFiCredentialsCstr);
    deserializeJson(*doc, DefaultJsonWiFiCredentialsCstr);
    return false;
  }

  // i think the file can only be read once, so reading into a string for use many times.
  // feel i need to reseach file rewinds or suchlike...
  String JsonWiFiCredentialsString = file.readString();
  Serial.printf("%s = %s\n\r", JsonWiFiCredentialsPath, JsonWiFiCredentialsString.c_str());

  // if the file isn't a valid JSON doc, return default credentials
  if(deserializeJson(doc2, JsonWiFiCredentialsString, DeserializationOption::Filter(filter)) != DeserializationError::Ok) {
    Serial.printf("DCBWiFiManager::DCBWiFiManager %s isnt a valid JSON doc, defaults loaded\r\n", JsonWiFiCredentialsPath);
    file.close();
    deserializeJson(DefaultJsonWiFiCredentials, DefaultJsonWiFiCredentialsCstr);
    deserializeJson(*doc, DefaultJsonWiFiCredentialsCstr);
    return false;
  }

  // checks done - deserialise the file and return data / sucess.
  deserializeJson(*doc, JsonWiFiCredentialsString);
  deserializeJson(JsonWiFiCredentials, JsonWiFiCredentialsString);
  file.close();
  return true;
}

void DCBWiFiManager::clearWiFiCredentials(){
  saveWiFiCredentials(DefaultJsonWiFiCredentials);
}

//Scan for WiFiNetworks in range and sort by signal strength
int DCBWiFiManager::scanWifiNetworks(StaticJsonDocument<200>* doc)
{
  JsonArray SSIDs = doc->createNestedArray("SSIDs");

  Serial.println("Scanning Network");

  // not async, not hidden networks, passive scan, 100ms per channel.
  // sometimes async_tcp tread is causing a watchdog reset ... trying scannetwork parameters to alleviate ... 
  int n = WiFi.scanNetworks(false,false,true,100U);

  // WiFi.scanNetworks() returns n < 0 meanings in WiFiType.h:
  //   #define WIFI_SCAN_RUNNING   (-1)
  //   #define WIFI_SCAN_FAILED    (-2)
  if (n <= 0)
  {
    SSIDs.add("No WiFi Networks Found");
    return (0);
  }
  
  for(int i=0; i<n; i++) SSIDs.add(WiFi.SSID(i));

  // sort networks - RSSI SORT

  // remove duplicates (must be RSSI sorted)
  
  // Skip low quality Wi-Fi stations by marking their indicies as -1.
  
  return (n);
}

int DCBWiFiManager::getRSSIasQuality(const int& RSSI)
{
  // For RSSI db to 0-100% conversion see https://stackoverflow.com/questions/15797920/how-to-convert-wifi-signal-strength-from-quality-percent-to-rssi-dbm
  return std::min(std::max(2 * (RSSI + 100), 0), 100);
}

void DCBWiFiManager::swap(int *thisOne, int *thatOne)
  {
    int tempo;
    tempo    = *thatOne;
    *thatOne = *thisOne;
    *thisOne = tempo;
  }