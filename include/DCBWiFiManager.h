// For statemachine class documentation see here https://www.codeproject.com/Articles/1087619/State-Machine-Design-in-Cplusplus-2
// implementation description is in the .cpp header.

#pragma once

#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Timeout.h>
#include <ArduinoJson.h>  // WiFiCredentials stored in SPIFFS in JSON format https://arduinojson.org/v6/assistant/

#include "StateMachine\StateMachine.h"

class DCBWiFiManager : public StateMachine
{
public:

  DCBWiFiManager(AsyncWebServer* server, const char* APSSID);

  void setup();
  // Call from loop to process current state once per call.
  void poll();  // external events taken by this state machine


  void OnUserConnectRequest();
  void OnUserDisconnectRequest();

  // called when AP mode and config portal is started
  void setWiFiConnectedCallback(std::function<void()> func) {_wificonnectedcallback = func;}

  // WiFi Scanner temp call...
  int scanWifiNetworks(StaticJsonDocument<200>* doc);

  // WiFi file save & load
  bool saveWiFiCredentials(StaticJsonDocument<200> doc);
  bool loadWiFiCredentials(StaticJsonDocument<200> *doc);

  // clear the WiFiCredentials file (by wrting the default - blank - credentails).
  void clearWiFiCredentials();

  String getConfiguredSTASSID(){return JsonWiFiCredentials["MsgBody"][0]["SSID"].as<String>();}

  String getConfiguredSTAPassword(){return JsonWiFiCredentials["MsgBody"][0]["Pwd"].as<String>();}

private:

  const String apip    = "192.168.4.1"; 
  const String staip   = "192.168.0.168";
  const String gateway = "255.255.255.0";

  String _apssid;

  // AsyncWebServer to use ...
  AsyncWebServer* _server;

  // DNS server (for captivie website in AP mode)
  DNSServer *dnsServer = nullptr;

  // SSID scanning ...
  int  _minimumQuality     = -1;
  bool _removeDuplicateAPs = true;
 
  // Variables to save values from HTML form

  /* WiFi Credentials JSON format (an arry of SSID's and pwd's) in my message wrapper.
     first array element is primary SSID & pwd, second is the secondard SSID & pwd.
    {"Msg": "WiFiCredentials",
    "MsgBody":
      [
          {
            "SSID": "xxx",
            "Pwd": "yyy"
          },
          {
            "SSID": "xxx",
            "Pwd": "yyy"
          }
      ]
    }
  */

  // JSON Wifi Credentails, used in WiFiManager.html, SPIFFS
  StaticJsonDocument<200> JsonWiFiCredentials;

  StaticJsonDocument<200> DefaultJsonWiFiCredentials; 
  const char*DefaultJsonWiFiCredentialsCstr = 
    "{\"Msg\": \"WiFiCredentials\",\"MsgBody\":[{\"SSID\": \"\",\"Pwd\":\"\"},{\"SSID\":\"\",\"Pwd\":\"\"}]}";

  // File paths to save input values permanently
  const char* JsonWiFiCredentialsPath = "/WiFiCredentials.json";

  // Timer variables
  unsigned long connectionTimeout_ms = 60000;        // Milli seconds to run Wifi manager's AP config portal 
  Timeout       WifiConnectTimeout;

  // state enumeration order must match the order of state method entries in the state map
  enum States { 
    ST_BOOTUP = 0,
    ST_APMODE,
    ST_CONNECTINGTOSTA,
    ST_STAMODE,
    ST_MAX_STATES
  };

  // state machine state functions
  STATE_DECLARE(DCBWiFiManager,     Bootup,                 NoEventData)
  ENTRY_DECLARE(DCBWiFiManager,     EntryAPMode,            NoEventData)
  STATE_DECLARE(DCBWiFiManager,     APMode,                 NoEventData)
  GUARD_DECLARE(DCBWiFiManager,     GuardConnectingToSTA,   NoEventData)
  ENTRY_DECLARE(DCBWiFiManager,     EntryConnectingToSTA,   NoEventData)
  STATE_DECLARE(DCBWiFiManager,     ConnectingToSTA,        NoEventData)
  STATE_DECLARE(DCBWiFiManager,     STAMode,                NoEventData)

  // State, Guard, entry and exit functions (in that order) are given for  STATE_MAP_ENTRY_ALL_EX map lines
  // (guards can do checks to see if its safe to enter the next state - e.g. motor stopped turning)
  BEGIN_STATE_MAP_EX
    STATE_MAP_ENTRY_ALL_EX(&Bootup,           NULL,                   NULL,                     NULL)     // ST_BOOTUP
    STATE_MAP_ENTRY_ALL_EX(&APMode,           NULL,                   &EntryAPMode,             NULL)     // ST_APMODE
    STATE_MAP_ENTRY_ALL_EX(&ConnectingToSTA,  &GuardConnectingToSTA,  &EntryConnectingToSTA,    NULL)     // ST_CONNECTINGTOSTA
    STATE_MAP_ENTRY_ALL_EX(&STAMode,          NULL,                   NULL,                     NULL)     // ST_STAMODE
  END_STATE_MAP_EX

  std::function<void()> _wificonnectedcallback;

  int  getRSSIasQuality(const int& RSSI);
  void swap(int *thisOne, int *thatOne);

  void setMinimumSignalQuality(const int& quality){_minimumQuality = quality;}
  void setRemoveDuplicateAPs(const bool& removeDuplicates){ _removeDuplicateAPs = removeDuplicates;};
};