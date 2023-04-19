
#pragma once

#include <Arduino.h>
#include "GSLC_Helpers.h"

// just for things (e.g. maintenance call backs) that need sharing down to lower level modules...

void ApGslc_Update();

// BASE Page
extern GSLC_Txt_Helper txtBaseWiFiStrength;

// DIAG Page
extern GSLC_TextBox_Helper txtDiagLog;

// WiFi Page
extern GSLC_TextBox_Helper txtWiFiDiag;
extern GSLC_Txt_Helper txtWiFiStatus;
extern GSLC_Txt_Helper txtWiFiSSID;
extern GSLC_Txt_Helper txtWiFiIp;
extern GSLC_Txt_Helper txtWiFiClient;

// APR Page
extern GSLC_Txt_Helper txtAprDisplay; 

// Data Page

extern GSLC_Txt_Helper txtDataSog;
extern GSLC_Txt_Helper txtDataSow;
extern GSLC_Txt_Helper txtDataWind;
extern GSLC_Txt_Helper txtDataWDir;
extern GSLC_Txt_Helper txtDataHdg;
extern GSLC_Txt_Helper txtDataDepth;