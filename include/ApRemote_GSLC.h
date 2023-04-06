//<File !Start!>
// FILE: [ApRemote_GSLC.h]
// Created by GUIslice Builder version: [0.17.b20]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XSlider.h"
#include "elem/XTextbox.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_BASE,E_PG_DIAG,E_PG_APR,E_PG_SPLASH_SCREEN,E_PG_DATA
      ,E_PG_WIFI};
enum {E_ELEM_BOX4,E_ELEM_BTN_APR_AUTO,E_ELEM_BTN_APR_MINUS_ONE
      ,E_ELEM_BTN_APR_MINUS_TEN,E_ELEM_BTN_APR_PLUS_ONE
      ,E_ELEM_BTN_APR_PLUS_TEN,E_ELEM_BTN_APR_PORT_TACK
      ,E_ELEM_BTN_APR_STBD_TACK,E_ELEM_BTN_APR_STDBY
      ,E_ELEM_BTN_APR_TRACK,E_ELEM_BTN_APR_WIND,E_ELEM_BTN_BASE_APR
      ,E_ELEM_BTN_BASE_DATA,E_ELEM_BTN_BASE_DIAG,E_ELEM_BTN_BASE_WIFI
      ,E_ELEM_BTN_WIFI_CONFIGURE_WIFI,E_ELEM_BTN_WIFI_RESET_WIFI
      ,E_ELEM_BTN_WIFI_WIFI_INFO,E_ELEM_RADIO_APR_AUTO
      ,E_ELEM_RADIO_APR_STANDBY,E_ELEM_RADIO_APR_TRACK
      ,E_ELEM_RADIO_APR_WIND,E_ELEM_TEXT10,E_ELEM_TEXT20,E_ELEM_TEXT21
      ,E_ELEM_TEXT22,E_ELEM_TEXT23,E_ELEM_TEXT24,E_ELEM_TEXT25
      ,E_ELEM_TEXT26,E_ELEM_TEXT27,E_ELEM_TEXT28,E_ELEM_TEXT29
      ,E_ELEM_TEXT30,E_ELEM_TEXT31,E_ELEM_TEXT32,E_ELEM_TEXT8
      ,E_ELEM_TEXT9,E_ELEM_TEXTBOX_APR_DISPLAY
      ,E_ELEM_TEXTBOX_BASE_STATUS,E_ELEM_TEXTBOX_DATA_DEPTH
      ,E_ELEM_TEXTBOX_DATA_HDG,E_ELEM_TEXTBOX_DATA_SOG
      ,E_ELEM_TEXTBOX_DATA_SOW,E_ELEM_TEXTBOX_DATA_WDIR
      ,E_ELEM_TEXTBOX_DATA_WIND,E_ELEM_TEXTBOX_DIAG_LOG
      ,E_ELEM_TEXT_SW_BUILD_DATE,E_TXTSCROLL_DIAG_LOG};
enum {E_GROUP1};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN20X32,E_BUILTIN5X8
      ,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                6

#define MAX_ELEM_PG_BASE 5 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM

#define MAX_ELEM_PG_DIAG 4 // # Elems total on page
#define MAX_ELEM_PG_DIAG_RAM MAX_ELEM_PG_DIAG // # Elems in RAM

#define MAX_ELEM_PG_APR 22 // # Elems total on page
#define MAX_ELEM_PG_APR_RAM MAX_ELEM_PG_APR // # Elems in RAM

#define MAX_ELEM_PG_SPLASH_SCREEN 4 // # Elems total on page
#define MAX_ELEM_PG_SPLASH_SCREEN_RAM MAX_ELEM_PG_SPLASH_SCREEN // # Elems in RAM

#define MAX_ELEM_PG_DATA 12 // # Elems total on page
#define MAX_ELEM_PG_DATA_RAM MAX_ELEM_PG_DATA // # Elems in RAM

#define MAX_ELEM_PG_WIFI 3 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asBasePage1Elem[MAX_ELEM_PG_BASE_RAM];
gslc_tsElemRef                  m_asBasePage1ElemRef[MAX_ELEM_PG_BASE];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_DIAG_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_DIAG];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_APR_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_APR];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_SPLASH_SCREEN_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_SPLASH_SCREEN];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_DATA_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_DATA];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PG_WIFI_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PG_WIFI];
gslc_tsXTextbox                 m_sTextbox11;
char                            m_acTextboxBuf11[35]; // NRows=1 NCols=35
gslc_tsXTextbox                 m_sTextbox3;
char                            m_acTextboxBuf3[168]; // NRows=6 NCols=28
gslc_tsXSlider                  m_sTextScroll3;
gslc_tsXCheckbox                m_asXRadio9;
gslc_tsXCheckbox                m_asXRadio10;
gslc_tsXCheckbox                m_asXRadio11;
gslc_tsXCheckbox                m_asXRadio12;
gslc_tsXTextbox                 m_sTextbox10;
char                            m_acTextboxBuf10[28]; // NRows=1 NCols=28
gslc_tsXTextbox                 m_sTextbox4;
char                            m_acTextboxBuf4[5]; // NRows=1 NCols=5
gslc_tsXTextbox                 m_sTextbox5;
char                            m_acTextboxBuf5[5]; // NRows=1 NCols=5
gslc_tsXTextbox                 m_sTextbox6;
char                            m_acTextboxBuf6[5]; // NRows=1 NCols=5
gslc_tsXTextbox                 m_sTextbox7;
char                            m_acTextboxBuf7[5]; // NRows=1 NCols=5
gslc_tsXTextbox                 m_sTextbox8;
char                            m_acTextboxBuf8[5]; // NRows=1 NCols=5
gslc_tsXTextbox                 m_sTextbox9;
char                            m_acTextboxBuf9[5]; // NRows=1 NCols=5

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pEleBtnWifiWifiInfo;
extern gslc_tsElemRef* m_pElemBrnBaseWiFi;
extern gslc_tsElemRef* m_pElemBtnAprAuto;
extern gslc_tsElemRef* m_pElemBtnAprMinusOne;
extern gslc_tsElemRef* m_pElemBtnAprMinusTen;
extern gslc_tsElemRef* m_pElemBtnAprPlusOne;
extern gslc_tsElemRef* m_pElemBtnAprPlusTen;
extern gslc_tsElemRef* m_pElemBtnAprPortTack;
extern gslc_tsElemRef* m_pElemBtnAprStandby;
extern gslc_tsElemRef* m_pElemBtnAprStbdTack;
extern gslc_tsElemRef* m_pElemBtnAprTrack;
extern gslc_tsElemRef* m_pElemBtnAprWind;
extern gslc_tsElemRef* m_pElemBtnBaseApr;
extern gslc_tsElemRef* m_pElemBtnBaseData;
extern gslc_tsElemRef* m_pElemBtnBaseDiag;
extern gslc_tsElemRef* m_pElemBtnWifiConfigureWifi;
extern gslc_tsElemRef* m_pElemBtnWifiResetWifi;
extern gslc_tsElemRef* m_pElemRadioButtonAprAuto;
extern gslc_tsElemRef* m_pElemRadioButtonAprStandby;
extern gslc_tsElemRef* m_pElemRadioButtonAprTrack;
extern gslc_tsElemRef* m_pElemRadioButtonAprWind;
extern gslc_tsElemRef* m_pElemTextboxAprDisplay;
extern gslc_tsElemRef* m_pElemTextboxDataDepth;
extern gslc_tsElemRef* m_pElemTextboxDataHdg;
extern gslc_tsElemRef* m_pElemTextboxDataSog;
extern gslc_tsElemRef* m_pElemTextboxDataSow;
extern gslc_tsElemRef* m_pElemTextboxDataWDir;
extern gslc_tsElemRef* m_pElemTextboxDataWind;
extern gslc_tsElemRef* m_pElemTextboxDiagLog;
extern gslc_tsElemRef* m_pElemTextboxStatus;
extern gslc_tsElemRef* m_pTextSlider10;
extern gslc_tsElemRef* m_pTextSlider4;
extern gslc_tsElemRef* m_pTextSlider4;
extern gslc_tsElemRef* m_pTextSlider4;
extern gslc_tsElemRef* m_pTextSlider4;
extern gslc_tsElemRef* m_pTextSlider4;
extern gslc_tsElemRef* m_pTextSlider4;
extern gslc_tsElemRef* m_pTextSliderBaseStatus;
extern gslc_tsElemRef* m_pTextSliderDiagLog;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN15X24,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN20X32,GSLC_FONTREF_PTR,NULL,4)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_DIAG,m_asPage1Elem,MAX_ELEM_PG_DIAG_RAM,m_asPage1ElemRef,MAX_ELEM_PG_DIAG);
  gslc_PageAdd(&m_gui,E_PG_APR,m_asPage2Elem,MAX_ELEM_PG_APR_RAM,m_asPage2ElemRef,MAX_ELEM_PG_APR);
  gslc_PageAdd(&m_gui,E_PG_SPLASH_SCREEN,m_asPopup1Elem,MAX_ELEM_PG_SPLASH_SCREEN_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_SPLASH_SCREEN);
  gslc_PageAdd(&m_gui,E_PG_DATA,m_asPage3Elem,MAX_ELEM_PG_DATA_RAM,m_asPage3ElemRef,MAX_ELEM_PG_DATA);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage4Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage4ElemRef,MAX_ELEM_PG_WIFI);

  // Now mark E_PG_BASE as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, E_PG_BASE);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_DIAG);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_GRAY);

  // -----------------------------------
  // PAGE: E_PG_BASE
  
  
  // create E_ELEM_BTN_BASE_DIAG button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BASE_DIAG,E_PG_BASE,
    (gslc_tsRect){10,290,40,20},(char*)"Diag",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemBtnBaseDiag = pElemRef;
  
  // create E_ELEM_BTN_BASE_APR button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BASE_APR,E_PG_BASE,
    (gslc_tsRect){190,290,40,20},(char*)"APR",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemBtnBaseApr = pElemRef;
  
  // create E_ELEM_BTN_BASE_WIFI button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BASE_WIFI,E_PG_BASE,
    (gslc_tsRect){70,290,40,20},(char*)"Wi-Fi",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemBrnBaseWiFi = pElemRef;
  
  // create E_ELEM_BTN_BASE_DATA button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BASE_DATA,E_PG_BASE,
    (gslc_tsRect){130,290,40,20},(char*)"Data",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_pElemBtnBaseData = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_BASE_STATUS,E_PG_BASE,&m_sTextbox11,
    (gslc_tsRect){20,270,212,10},E_BUILTIN5X8,
    (char*)&m_acTextboxBuf11,1,35);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_GRAY);
  m_pElemTextboxStatus = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_DIAG
  
  
  // Create E_ELEM_TEXT20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT20,E_PG_DIAG,(gslc_tsRect){36,10,168,16},
    (char*)"Diagnostic Log",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
   
  // Create wrapping box for textbox E_ELEM_TEXTBOX_DIAG_LOG and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_DIAG,(gslc_tsRect){10,45,220,200});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DIAG_LOG,E_PG_DIAG,&m_sTextbox3,
    (gslc_tsRect){10+2,45+4,220-4-20,200-7},E_BUILTIN5X8,
    (char*)&m_acTextboxBuf3,6,28);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDiagLog = pElemRef;

  // Create vertical scrollbar for textbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_TXTSCROLL_DIAG_LOG,E_PG_DIAG,&m_sTextScroll3,
          (gslc_tsRect){10+220-2-20,45+4,20,200-8},0,100,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pTextSliderDiagLog = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_APR
  
  
  // create E_ELEM_BTN_APR_STDBY button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_STDBY,E_PG_APR,
    (gslc_tsRect){79,128,80,30},(char*)"Stdby",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_RED,GSLC_COL_RED_DK4);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprStandby = pElemRef;
  
  // create E_ELEM_BTN_APR_AUTO button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_AUTO,E_PG_APR,
    (gslc_tsRect){79,163,80,30},(char*)"Auto",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_RED,GSLC_COL_RED_DK4);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprAuto = pElemRef;
  
  // create E_ELEM_BTN_APR_WIND button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_WIND,E_PG_APR,
    (gslc_tsRect){79,198,80,30},(char*)"Wind",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprWind = pElemRef;
  
  // create E_ELEM_BTN_APR_TRACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_TRACK,E_PG_APR,
    (gslc_tsRect){79,233,80,30},(char*)"Track",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprTrack = pElemRef;
  
  // create E_ELEM_BTN_APR_PLUS_ONE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_PLUS_ONE,E_PG_APR,
    (gslc_tsRect){169,163,60,30},(char*)"+1",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprPlusOne = pElemRef;
  
  // create E_ELEM_BTN_APR_PLUS_TEN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_PLUS_TEN,E_PG_APR,
    (gslc_tsRect){169,198,60,30},(char*)"+10",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprPlusTen = pElemRef;
  
  // create E_ELEM_BTN_APR_STBD_TACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_STBD_TACK,E_PG_APR,
    (gslc_tsRect){169,233,60,30},(char*)"Tack",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprStbdTack = pElemRef;
  
  // create E_ELEM_BTN_APR_MINUS_ONE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_MINUS_ONE,E_PG_APR,
    (gslc_tsRect){9,163,60,30},(char*)"-1",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprMinusOne = pElemRef;
  
  // create E_ELEM_BTN_APR_MINUS_TEN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_MINUS_TEN,E_PG_APR,
    (gslc_tsRect){9,198,60,30},(char*)"-10",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprMinusTen = pElemRef;
  
  // create E_ELEM_BTN_APR_PORT_TACK button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_APR_PORT_TACK,E_PG_APR,
    (gslc_tsRect){9,233,60,30},(char*)"Tack",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAprPortTack = pElemRef;
   
  // Create E_ELEM_BOX4 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX4,E_PG_APR,(gslc_tsRect){10,60,220,50});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY,GSLC_COL_GRAY);
  
  // Create radio button E_ELEM_RADIO_APR_STANDBY
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO_APR_STANDBY,E_PG_APR,&m_asXRadio9,
    (gslc_tsRect){34,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,true);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonAprStandby = pElemRef;
  
  // Create radio button E_ELEM_RADIO_APR_AUTO
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO_APR_AUTO,E_PG_APR,&m_asXRadio10,
    (gslc_tsRect){84,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonAprAuto = pElemRef;
  
  // Create radio button E_ELEM_RADIO_APR_WIND
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO_APR_WIND,E_PG_APR,&m_asXRadio11,
    (gslc_tsRect){134,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonAprWind = pElemRef;
  
  // Create radio button E_ELEM_RADIO_APR_TRACK
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO_APR_TRACK,E_PG_APR,&m_asXRadio12,
    (gslc_tsRect){184,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonAprTrack = pElemRef;
  
  // Create E_ELEM_TEXT21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT21,E_PG_APR,(gslc_tsRect){25,90,30,8},
    (char*)"Stdby",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT22,E_PG_APR,(gslc_tsRect){75,90,24,8},
    (char*)"Auto",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT23,E_PG_APR,(gslc_tsRect){130,90,24,8},
    (char*)"Wind",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT24 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT24,E_PG_APR,(gslc_tsRect){175,90,30,8},
    (char*)"Track",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT25 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT25,E_PG_APR,(gslc_tsRect){20,135,48,16},
    (char*)"PORT",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_TEXT26 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT26,E_PG_APR,(gslc_tsRect){180,135,48,16},
    (char*)"STBD",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_APR_DISPLAY,E_PG_APR,&m_sTextbox10,
    (gslc_tsRect){20,10,200,50},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf10,1,28);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_MAGENTA);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxAprDisplay = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_SPLASH_SCREEN
  
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_SPLASH_SCREEN,(gslc_tsRect){66,45,108,16},
    (char*)"Raymarine",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT9,E_PG_SPLASH_SCREEN,(gslc_tsRect){54,95,132,16},
    (char*)"Auto Pilot ",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PG_SPLASH_SCREEN,(gslc_tsRect){84,130,72,16},
    (char*)"Remote",0,E_BUILTIN10X16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT_SW_BUILD_DATE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_SW_BUILD_DATE,E_PG_SPLASH_SCREEN,(gslc_tsRect){48,240,144,16},
    (char*)"<Build Date>",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_PG_DATA
  
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DATA_SOG,E_PG_DATA,&m_sTextbox4,
    (gslc_tsRect){105,20,122,34},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf4,1,5);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDataSog = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DATA_SOW,E_PG_DATA,&m_sTextbox5,
    (gslc_tsRect){108,65,122,34},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf5,1,5);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDataSow = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DATA_WIND,E_PG_DATA,&m_sTextbox6,
    (gslc_tsRect){108,105,122,34},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf6,1,5);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDataWind = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DATA_WDIR,E_PG_DATA,&m_sTextbox7,
    (gslc_tsRect){108,150,122,34},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf7,1,5);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDataWDir = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DATA_HDG,E_PG_DATA,&m_sTextbox8,
    (gslc_tsRect){108,190,122,34},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf8,1,5);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDataHdg = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX_DATA_DEPTH,E_PG_DATA,&m_sTextbox9,
    (gslc_tsRect){108,230,122,34},E_BUILTIN20X32,
    (char*)&m_acTextboxBuf9,1,5);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextboxDataDepth = pElemRef;
  
  // Create E_ELEM_TEXT27 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT27,E_PG_DATA,(gslc_tsRect){15,25,54,24},
    (char*)"SOG",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT28 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT28,E_PG_DATA,(gslc_tsRect){15,65,54,24},
    (char*)"SOW",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT29 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT29,E_PG_DATA,(gslc_tsRect){15,110,72,24},
    (char*)"Wind",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT30 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT30,E_PG_DATA,(gslc_tsRect){15,150,90,24},
    (char*)"W.Dir",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT31 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT31,E_PG_DATA,(gslc_tsRect){10,190,54,24},
    (char*)"Hdg",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT32 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT32,E_PG_DATA,(gslc_tsRect){15,230,90,24},
    (char*)"Depth",0,E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_PG_WIFI
  
  
  // create E_ELEM_BTN_WIFI_CONFIGURE_WIFI button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_WIFI_CONFIGURE_WIFI,E_PG_WIFI,
    (gslc_tsRect){70,35,100,25},(char*)"Configure Wi-Fi",0,E_BUILTIN5X8,&CbBtnCommon);
  m_pElemBtnWifiConfigureWifi = pElemRef;
  
  // create E_ELEM_BTN_WIFI_WIFI_INFO button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_WIFI_WIFI_INFO,E_PG_WIFI,
    (gslc_tsRect){70,80,100,25},(char*)"Wi-Fi Info",0,E_BUILTIN5X8,&CbBtnCommon);
  m_pEleBtnWifiWifiInfo = pElemRef;
  
  // create E_ELEM_BTN_WIFI_RESET_WIFI button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_WIFI_RESET_WIFI,E_PG_WIFI,
    (gslc_tsRect){70,125,100,25},(char*)"Reset Wi-Fi",0,E_BUILTIN5X8,&CbBtnCommon);
  m_pElemBtnWifiResetWifi = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 2);
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
