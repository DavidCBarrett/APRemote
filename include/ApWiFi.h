
#ifndef _APWIFI_H
#define _APWIFI_H

#include <Arduino.h>
#include "DCBWiFiManager.h"

extern DCBWiFiManager wm;

void ApWiFi_Setup();

void APWiFi_Loop();

#endif // _APWIFI_H