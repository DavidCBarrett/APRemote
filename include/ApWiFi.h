
#pragma once

#include <Arduino.h>
#include "DCBWiFiManager.h"

extern DCBWiFiManager wm;

void ApWiFi_Setup();

void ApWiFi_Disconnect();

void APWiFi_Loop();
