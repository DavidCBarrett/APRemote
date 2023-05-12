
// For statemachine class documentation see here https://www.codeproject.com/Articles/1087619/State-Machine-Design-in-Cplusplus-2
// implementation description is in the .cpp header.

#pragma once

#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Timeout.h>
#include <ArduinoJson.h>  // needed for JSON encapsulation (send multiple variables with one string) https://github.com/bblanchon/ArduinoJson?utm_source=platformio&utm_medium=piohome

#include "StateMachine\StateMachine.h"

extern String _ssid;
extern String _pass;

class DCBWiFiManager : public StateMachine
{
public:

  int *indices;  // WiFi network data, filled by scan (SSID, BSSID)

  DCBWiFiManager(AsyncWebServer* server, const char* APSSID);

  // external events taken by this state machine
  void OnUserConnectRequest();
  void OnUserDisconnectRequest();

  // Call from loop to process current state once per call.
  void poll();

  // other functions 
 
  void process();

  // sets timeout before webserver loop ends and exits even if there has been no setup.
  void setconnectionlTimeout(unsigned long seconds) {connectionlTimeout_ms = seconds*1000;}

  // Return connection timeout remaining in seconds (for optional display on a GUI).
  unsigned long getconnectionlTimeLeft() {return WifiConnectTimeout.time_left_ms()/1000;}

  void resetSettings();

  String getConfiguredSTASSID(){return _ssid;}

  String getConfiguredSTAPassword(){return _pass;}

  // called when AP mode and config portal is started
  void setWiFiConnectedCallback(std::function<void()> func) {_wificonnectedcallback = func;}

  // WiFi Scanner temp call...
  int  scanWifiNetworks(StaticJsonDocument<200>* doc);

private:

  String _apssid;

  // AsyncWebServer to use ...
  AsyncWebServer* _server;

  // DNS server (for captivie website in AP mode)
  DNSServer *dnsServer = nullptr;

  // SSID scanning ...
  int     _paramsCount        = 0;
  int     _minimumQuality     = -1;
  bool    _removeDuplicateAPs = true;
  String  ListOfSSIDs         = "";      // List of SSIDs found by scan, in HTML <option> format
  int     WiFiNetworksFound   = 0;    // Number of SSIDs found by WiFi scan, including low quality and duplicates

  //Variables to save values from HTML form
  String _ssid;
  String _pass;
  String ip;
  String gateway;

  // Timer variables
  unsigned long connectionlTimeout_ms = 60000;        // seconds to run Wifi manager's AP config portal 
  Timeout       WifiConnectTimeout;

  // File paths to save input values permanently
  const char* ssidPath      = "/ssid.txt";
  const char* passPath      = "/pass.txt";
  const char* ipPath        = "/ip.txt";
  const char* gatewayPath   = "/gateway.txt";

  // Search for parameter in HTTP POST request
  const char* PARAM_INPUT_1 = "ssid";
  const char* PARAM_INPUT_2 = "pass";
  const char* PARAM_INPUT_3 = "ip";
  const char* PARAM_INPUT_4 = "gateway";

  // state enumeration order must match the order of state
  // method entries in the state map
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

  String  readFile(fs::FS &fs, const char * path);
  void    writeFile(fs::FS &fs, const char * path, const char * message);

  // SSID scanning...
  int  getRSSIasQuality(const int& RSSI);
  void swap(int *thisOne, int *thatOne);
  void setMinimumSignalQuality(const int& quality);
  void setRemoveDuplicateAPs(const bool& removeDuplicates);

};