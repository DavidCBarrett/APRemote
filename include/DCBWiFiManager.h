
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

    // state enumeration order must match the order of state
    // method entries in the state map
    enum States { 
        ST_CONNECTINGTOSTA = 0,
        ST_APMODE,
        ST_STAMODE,
        ST_MAX_STATES
    };
  
  // state machine state functions
    void ST_ConnectingToSTA(EventData*);
    void ST_APMode(EventData*);
    void ST_STAMode(EventData*);
    
    //STATE_DECLARE(DCBWiFiManager,     ConnectingToSTA,    NoEventData)
    // STATE_DECLARE(DCBWiFiManager,     APMode,             NoEventData)
    // STATE_DECLARE(DCBWiFiManager,     STAMode,            NoEventData)

//  state map to define state function order
    BEGIN_STATE_MAP
		STATE_MAP_ENTRY(&DCBWiFiManager::ST_ConnectingToSTA)
        STATE_MAP_ENTRY(&DCBWiFiManager::ST_ConnectingToSTA)
        STATE_MAP_ENTRY(&DCBWiFiManager::ST_APMode)
        STATE_MAP_ENTRY(&DCBWiFiManager::ST_STAMode)
    END_STATE_MAP

    // BEGIN_STATE_MAP_EX
		//     STATE_MAP_ENTRY_EX(&ConnectingToSTA)
    //     STATE_MAP_ENTRY_EX(&APMode)
    //     STATE_MAP_ENTRY_EX(&STAMode)
    // END_STATE_MAP_EX

  bool initWiFi();

  std::function<void()> _wificonnectedcallback;

  String  readFile(fs::FS &fs, const char * path);
  void    writeFile(fs::FS &fs, const char * path, const char * message);

};
#endif 