
// For statemachine class documentation see here https://www.codeproject.com/Articles/1087619/State-Machine-Design-in-Cplusplus-2
// implementation description is in the .cpp header.

#ifndef _DCBWIFIMANAGER_H
#define _DCBWIFIMANAGER_H

#include <ESPAsyncWebServer.h>

#include "StateMachine\StateMachine.h"

extern String _ssid;
extern String _pass;

class DCBWiFiManager : public StateMachine
{
public:

  DCBWiFiManager(AsyncWebServer* server, const char* APSSID);

  // external events taken by this state machine
  void OnUserConnectRequest();
  void OnUserDisconnectRequest();

  // other functions 
  void setup(AsyncWebServer* server, const char* APSSID);

  void process();

  void ConfigPortal();

  // sets timeout before webserver loop ends and exits even if there has been no setup.
  void setConfigPortalTimeout(unsigned long seconds);

  void resetSettings();

  void disconnectWiFi();

  String getConfiguredSTASSID(){
      return _ssid;
  }

  String getConfiguredSTAPassword(){
      return _pass;
  }

  // called when AP mode and config portal is started
  void setWiFiConnectedCallback(std::function<void()>);

private:

  String _apssid;

  // AsyncWebServer to use ...
  AsyncWebServer* _server;

    //Variables to save values from HTML form
  String _ssid;
  String _pass;
  String ip;
  String gateway;

  // Timer variables
  unsigned long configPortalPreviousMillis  = 0;
  unsigned long configPortalTimeoutMillis   = 120;        // seconds to run Wifi manager's AP config portal 
  unsigned long configPortalStartTimeMillis = millis();

  // File paths to save input values permanently
  const char* ssidPath = "/ssid.txt";
  const char* passPath = "/pass.txt";
  const char* ipPath = "/ip.txt";
  const char* gatewayPath = "/gateway.txt";

  // Search for parameter in HTTP POST request
  const char* PARAM_INPUT_1 = "ssid";
  const char* PARAM_INPUT_2 = "pass";
  const char* PARAM_INPUT_3 = "ip";
  const char* PARAM_INPUT_4 = "gateway";

  // state enumeration order must match the order of state
  // method entries in the state map
  enum States { 
      ST_CONNECTINGTOSTA = 0,
      ST_APMODE,
      ST_STAMODE,
      ST_MAX_STATES
  };

  // state machine state functions
     
    ENTRY_DECLARE(DCBWiFiManager,     EntryConnectingToSTA,   NoEventData)
    STATE_DECLARE(DCBWiFiManager,     ConnectingToSTA,        NoEventData)
    ENTRY_DECLARE(DCBWiFiManager,     EntryAPMode,            NoEventData)
    STATE_DECLARE(DCBWiFiManager,     APMode,                 NoEventData)
    STATE_DECLARE(DCBWiFiManager,     STAMode,                NoEventData)

    // State, Guard, entry and exit functions (in that order) are given for  STATE_MAP_ENTRY_ALL_EX map lines
    // (guards can do checks to see if its safe to enter the next state - e.g. motor stopped turning)
    BEGIN_STATE_MAP_EX
		    STATE_MAP_ENTRY_ALL_EX(&ConnectingToSTA,  NULL,     &EntryConnectingToSTA,    NULL)
        STATE_MAP_ENTRY_ALL_EX(&APMode,           NULL,     &EntryAPMode,             NULL)
        STATE_MAP_ENTRY_ALL_EX(&STAMode,          NULL,     NULL,                     NULL)
    END_STATE_MAP_EX

  bool initWiFi();

  std::function<void()> _wificonnectedcallback;

  String  readFile(fs::FS &fs, const char * path);
  void    writeFile(fs::FS &fs, const char * path, const char * message);

};
#endif 