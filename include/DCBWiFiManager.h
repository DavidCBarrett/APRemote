
#ifndef _DCBWIFIMANAGER_H
#define _DCBWIFIMANAGER_H

#include <ESPAsyncWebServer.h>

class DCBWiFiManager
{
public:

  DCBWiFiManager();

  void setup(AsyncWebServer* server, char* APSSID);

  void process();

  void ConfigPortal();

  // sets timeout before webserver loop ends and exits even if there has been no setup.
  void setConfigPortalTimeout(unsigned long seconds);

  void resetSettings();

  // called when AP mode and config portal is started
  void setWiFiConnectedCallback(std::function<void()>);

private:

    std::function<void()> _wificonnectedcallback;
};
#endif 