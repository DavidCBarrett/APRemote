
#ifndef _DCBWIFIMANAGER_H
#define _DCBWIFIMANAGER_H

#include <ESPAsyncWebServer.h>

extern String _ssid;
extern String _pass;

class DCBWiFiManager
{
public:

  DCBWiFiManager();

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


  bool initWiFi();

  std::function<void()> _wificonnectedcallback;
};
#endif 