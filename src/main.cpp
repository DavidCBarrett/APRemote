//<App !Start!>
// FILE: [main.cpp]
// Created by GUIslice Builder version: [0.17.b21]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

/*
WebServer for Raymarine Seatalk 1 based autohelm (with other boat data). 
Control your autohelm & see boat data using your phone's web browser.

Original project from https://github.com/richardJG/APRemote 

Main changes: 
1. Migrated to VS Code with PlatformIO enviornment

2. Swapped out WebSockets_Generic (which caused me lots of comple problems) for the Web Socket Server already in ESPAsyncWebServer. 
   Inpiration / info for the changes taken from the tutorial at https://m1cr0lab-esp32.github.io/remote-control-with-websocket/

3. Moved from hard coded WiFI credentials to using WiFiManager with AutoPilot Remote Access Point Web page at 192.168.4.1. 
   Connecting to the AutoPilot Remote network will bring up the web page.

4. Added buttons to ESP32. use is up/sel/down for (future) menu items, or to start a wifimanager connect session...
   using "PinButton" (AKA poelstra/MultiButton & poelstra/arduino-multi-button) library from 
   https://github.com/poelstra/arduino-multi-button/?utm_source=platformio&utm_medium=piohome

5. Added heartbeat LED using HeartBeat library by Rob Tillaart 
   https://github.com/RobTillaart/HeartBeat?utm_source=platformio&utm_medium=piohome
   Using the onboard LED (GPIO 2). 

6. Added "ILI9341 SPI TFT with XPT2046 SPI touch screen" to act as an alternative AP remote UI device, when phone or wifi isnt working
   Library is Bodmer/TFT_eSPI at https://github.com/Bodmer/TFT_eSPI?utm_source=platformio&utm_medium=piohome

7. Using phone as a webclient, when the phone autolocks, it drops the websocket connection & had to refresh the page to get connection back. 
   In the client' Javascript, changed from WebSocket to ReconnectingWebSocket to give auto-reconnect on unlock.
       Reconnecting websockets javascript: https://github.com/joewalnes/reconnecting-websocket; 
       Reconnecting websocketsexample: https://mpolinowski.github.io/docs/Development/Javascript/2021-09-10--websocket-recconects/2021-09-10/
   Had to change webserver setup code to include "server.serveStatic("/", SPIFFS, "/");". I beleive this serves all files requested by the 
   client from the SPIFF file system.

8. Browser's inspector was grumbling "favicon.ico" was missing. Favicon files created using https://favicon.io/favicon-generator/ and added to data directory. 
   Link tags added to HTML head as suggested on above page.

libraries used at Mar 20223 were:
	plerup/EspSoftwareSerial@7.0.0
  esphome/AsyncTCP-esphome@^1.2.2
  esphome/ESPAsyncWebServer-esphome@^2.1.0
  alanswx/ESPAsyncWifiManager
  poelstra/MultiButton@^1.2.0
  robtillaart/HeartBeat@^0.3.2
  bodmer/TFT_eSPI@^2.5.23

TODO'S:

 1. Need to add WiFi reconnection code from here: https://github.com/alanswx/ESPAsyncWiFiManager/issues/92

 2. Finish TFT touch screen alternative UI.

 3. esp32 only works (connects to wifi) when there is an active serial monitor connected in platformio. work out why and fix.

 4. Move to a GUIslice type project, for easier TFT UI updates.

*/

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include <Arduino.h>
#include <PinButton.h>
#include "HeartBeat.h"

#include "ApEsp32Pins.h"
#include "ApWiFi.h"
#include "SeaTalk.h"
#include "ApRemote_GSLC.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

//create button objects
// PinButton btnUp(BTN_UP);
PinButton btnDown(BTN_DOWN);
PinButton btnSelect(BTN_SELECT);

// Heartbeat object for onboard LED 
HeartBeatDiag HB;
HeartBeatDiag TXHB;
HeartBeatDiag RXHB;

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pEleBtnWifiWifiInfo= NULL;
gslc_tsElemRef* m_pElemBrnBaseWiFi= NULL;
gslc_tsElemRef* m_pElemBtnAprAuto = NULL;
gslc_tsElemRef* m_pElemBtnAprMinusOne= NULL;
gslc_tsElemRef* m_pElemBtnAprMinusTen= NULL;
gslc_tsElemRef* m_pElemBtnAprPlusOne= NULL;
gslc_tsElemRef* m_pElemBtnAprPlusTen= NULL;
gslc_tsElemRef* m_pElemBtnAprPortTack= NULL;
gslc_tsElemRef* m_pElemBtnAprStandby= NULL;
gslc_tsElemRef* m_pElemBtnAprStbdTack= NULL;
gslc_tsElemRef* m_pElemBtnAprTrack= NULL;
gslc_tsElemRef* m_pElemBtnAprWind = NULL;
gslc_tsElemRef* m_pElemBtnBaseApr = NULL;
gslc_tsElemRef* m_pElemBtnBaseData= NULL;
gslc_tsElemRef* m_pElemBtnBaseDiag= NULL;
gslc_tsElemRef* m_pElemBtnWifiConfigureWifi= NULL;
gslc_tsElemRef* m_pElemBtnWifiResetWifi= NULL;
gslc_tsElemRef* m_pElemRadioButtonAprAuto= NULL;
gslc_tsElemRef* m_pElemRadioButtonAprStandby= NULL;
gslc_tsElemRef* m_pElemRadioButtonAprTrack= NULL;
gslc_tsElemRef* m_pElemRadioButtonAprWind= NULL;
gslc_tsElemRef* m_pElemTextAprDisplay= NULL;
gslc_tsElemRef* m_pElemTextDataDepth= NULL;
gslc_tsElemRef* m_pElemTextDataHdg= NULL;
gslc_tsElemRef* m_pElemTextDataSog= NULL;
gslc_tsElemRef* m_pElemTextDataSow= NULL;
gslc_tsElemRef* m_pElemTextDataWDir= NULL;
gslc_tsElemRef* m_pElemTextDataWind= NULL;
gslc_tsElemRef* m_pElemTextboxDiagLog= NULL;
gslc_tsElemRef* m_pElemTextboxStatus= NULL;
gslc_tsElemRef* m_pTextSliderDiagLog= NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_BTN_BASE_DIAG:
        gslc_SetPageCur(&m_gui, E_PG_DIAG);
        break;
      case E_ELEM_BTN_BASE_APR:
        gslc_SetPageCur(&m_gui, E_PG_APR);
        break;
      case E_ELEM_BTN_BASE_WIFI:
        gslc_SetPageCur(&m_gui, E_PG_WIFI);
        break;
      case E_ELEM_BTN_BASE_DATA:
        gslc_SetPageCur(&m_gui, E_PG_DATA);
        break;
      case E_ELEM_BTN_APR_STDBY:
        gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nStandby");
        break;
      case E_ELEM_BTN_APR_AUTO:
        gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nAuto");
        break;
      case E_ELEM_BTN_APR_WIND:
        gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nWind");
        break;
      case E_ELEM_BTN_APR_TRACK:
        gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nTrack");
        break;
      case E_ELEM_BTN_APR_PLUS_ONE:
        break;
      case E_ELEM_BTN_APR_PLUS_TEN:
        break;
      case E_ELEM_BTN_APR_STBD_TACK:
        break;
      case E_ELEM_BTN_APR_MINUS_ONE:
        break;
      case E_ELEM_BTN_APR_MINUS_TEN:
        break;
      case E_ELEM_BTN_APR_PORT_TACK:
        break;
      case E_ELEM_BTN_WIFI_CONFIGURE_WIFI:
        APWiFi_ConfigPortal();
        break;
      case E_ELEM_BTN_WIFI_WIFI_INFO:
        break;
      case E_ELEM_BTN_WIFI_RESET_WIFI:
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
// Checkbox / radio callbacks
// - Creating a callback function is optional, but doing so enables you to
//   detect changes in the state of the elements.
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  if (pElemRef == NULL) {
    return false;
  }
  
  boolean bChecked = gslc_ElemXCheckboxGetState(pGui,pElemRef);

  // Determine which element issued the callback
  switch (pElem->nId) {
//<Checkbox Enums !Start!>
    case E_ELEM_RADIO_APR_STANDBY:
      break;
    case E_ELEM_RADIO_APR_AUTO:
      break;
    case E_ELEM_RADIO_APR_WIND:
      break;
    case E_ELEM_RADIO_APR_TRACK:
      break;

//<Checkbox Enums !End!>
    default:
      break;
  } // switch
  return true;
}
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_TXTSCROLL_DIAG_LOG:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pTextSliderDiagLog);
      gslc_ElemXTextboxScrollSet(pGui,m_pElemTextboxDiagLog,nVal,100);  // DCB: use slider position to set text box scroll posn
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

void ApGslc_Update() {
  gslc_Update(&m_gui);  
}

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  pinMode(RX_MON, INPUT);
  pinMode(RX_LED, OUTPUT_OPEN_DRAIN);
  pinMode(TX_LED, OUTPUT_OPEN_DRAIN);

  HB.begin(LED_PIN, 1);  // PIN ID and frequency 3
  HB.setDutyCycle(17.53);
 
  TXHB.begin(TX_LED, 1);
  RXHB.begin(RX_LED, 1);

  Serial.begin(115200);
  while(!Serial) delay(100);
  delay(500);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();

  Serial.printf("----------------------\n-- Sea Talk Web Remote\n----------------------\n");
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxDiagLog, (char*)"----------------------\n-- Sea Talk Web Remote\n----------------------\n");
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"--Seatalk APR--\n");

  ApWiFi_Init();

  Seatalk_Init();

  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxDiagLog, (char*)"Setup Done.\n");
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxStatus, (char*)"\nSetup Done.");
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{
  char cDisp[20];

  HB.beat();
  TXHB.beat();
  RXHB.beat();
  
  // do loop mainenance / updates
  // btnUp.update();
  btnDown.update();
  btnSelect.update();

  APWiFi_Tick();

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  /*
  //TODO - Add update code for any text, gauges, or sliders
  sprintf(cDisp, "%d Mag", hdg);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxAprDisplay, cDisp);

  sog = random(0,1000) / 50.0;

  sprintf(cDisp, "%.1f", sog);
  gslc_ElemSetTxtStr(&m_gui, m_pElemTextDataSog, cDisp);

  sprintf(cDisp, "%.1f", stw);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxDataSow, cDisp);

  sprintf(cDisp, "%.1f", aws);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxDataWind, cDisp);

  sprintf(cDisp, "%d Mag", awa);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxDataWDir, cDisp);

  sprintf(cDisp, "%d Mag", hdg);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxAprDisplay, cDisp);

  sprintf(cDisp, "%.1f", dpt);
  gslc_ElemXTextboxAdd(&m_gui, m_pElemTextboxDataDepth, cDisp);
*/
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
  
  delay (100);
}
