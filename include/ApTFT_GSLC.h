//<File !Start!>
// FILE: [ApTFT_GSLC.h]
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
#include "elem/XKeyPad_Alpha.h"
#include "elem/XSlider.h"
#include "elem/XTextbox.h"

// Ensure optional features are enabled in the configuration
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
// #include "NULLFreeSansBold12pt7b.h"
// #include "NULLFreeSansBold18pt7b.h"
// #include "NULLFreeSerif12pt7b.h"
// #include "NULLFreeSerif9pt7b.h"
// #include "NULLFreeSerifBold12pt7b.h"
// #include "NULLFreeSerifBold9pt7b.h"
#include "NotoSerifBold20pt7b.h"
#include "NotoSerifBoldItalic22pt7b.h"
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
enum {E_PG_BASE,E_PG_MAIN,E_PG_AP,E_PG_SPLASH_SCREEN,E_POP_KEYPAD_ALPHA};
enum {E_ELEM_BOX4,E_ELEM_BTN25,E_ELEM_BTN26,E_ELEM_BTN27,E_ELEM_BTN28
      ,E_ELEM_BTN29,E_ELEM_BTN30,E_ELEM_BTN31,E_ELEM_BTN32,E_ELEM_BTN33
      ,E_ELEM_BTN34,E_ELEM_BTN_PAGE_RIGHT,E_ELEM_PAGE_LEFT
      ,E_ELEM_RADIO10,E_ELEM_RADIO11,E_ELEM_RADIO12,E_ELEM_RADIO9
      ,E_ELEM_TEXT10,E_ELEM_TEXT20,E_ELEM_TEXT21,E_ELEM_TEXT22
      ,E_ELEM_TEXT23,E_ELEM_TEXT24,E_ELEM_TEXT25,E_ELEM_TEXT26
      ,E_ELEM_TEXT8,E_ELEM_TEXT9,E_ELEM_TEXTBOX3,E_ELEM_TEXTINPUT3
      ,E_ELEM_TEXT_SW_BUILD_DATE,E_TXTSCROLL_LOG,E_ELEM_KEYPAD_ALPHA};
enum {E_GROUP1};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN5X8,E_FREESANSBOLD12,E_FREESANSBOLD18,E_FREESERIF12
      ,E_FREESERIF9,E_FREESERIFBOLD12,E_FREESERIFBOLD9
      ,E_NOTOSERIFBOLD20,E_NOTOSERIFBOLDITALIC22,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                5

#define MAX_ELEM_PG_BASE 2 // # Elems total on page
#define MAX_ELEM_PG_BASE_RAM MAX_ELEM_PG_BASE // # Elems in RAM

#define MAX_ELEM_PG_MAIN 4 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
// Define the maximum number of elements per page
// - To enable the same code to run on devices that support storing
//   data into Flash (PROGMEM) and those that don't, we can make the
//   number of elements in Flash dependent upon GSLC_USE_PROGMEM
// - This should allow both Arduino and ARM Cortex to use the same code.

#define MAX_ELEM_PG_AP 22 // # Elems total on page
#if (GSLC_USE_PROGMEM)
  #define MAX_ELEM_PG_AP_PROG 1 // # Elems in Flash
#else
  #define MAX_ELEM_PG_AP_PROG 0 // No Elems in Flash
#endif
#define MAX_ELEM_PG_AP_RAM MAX_ELEM_PG_AP - MAX_ELEM_PG_AP_PROG 

#define MAX_ELEM_PG_SPLASH_SCREEN 4 // # Elems total on page
#define MAX_ELEM_PG_SPLASH_SCREEN_RAM MAX_ELEM_PG_SPLASH_SCREEN // # Elems in RAM
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
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_AP_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_AP];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_SPLASH_SCREEN_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_SPLASH_SCREEN];
gslc_tsElem                     m_asKeypadAlphaElem[1];
gslc_tsElemRef                  m_asKeypadAlphaElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadAlpha;
gslc_tsXTextbox                 m_sTextbox3;
char                            m_acTextboxBuf3[168]; // NRows=6 NCols=28
gslc_tsXSlider                  m_sTextScroll3;
gslc_tsXCheckbox                m_asXRadio9;
gslc_tsXCheckbox                m_asXRadio10;
gslc_tsXCheckbox                m_asXRadio11;
gslc_tsXCheckbox                m_asXRadio12;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemBtnAuto16_26;
extern gslc_tsElemRef* m_pElemBtnMinusOne22_32;
extern gslc_tsElemRef* m_pElemBtnMinusTen23_33;
extern gslc_tsElemRef* m_pElemBtnPlusOne19_29;
extern gslc_tsElemRef* m_pElemBtnPlusTen20_30;
extern gslc_tsElemRef* m_pElemBtnPortTack24_34;
extern gslc_tsElemRef* m_pElemBtnStandby15_25;
extern gslc_tsElemRef* m_pElemBtnStbdTack21_31;
extern gslc_tsElemRef* m_pElemBtnTrack18_28;
extern gslc_tsElemRef* m_pElemBtnWind17_27;
extern gslc_tsElemRef* m_pElemDisplay2_3;
extern gslc_tsElemRef* m_pElemRadioButtonAuto6_10;
extern gslc_tsElemRef* m_pElemRadioButtonStandby5_9;
extern gslc_tsElemRef* m_pElemRadioButtonTrack8_12;
extern gslc_tsElemRef* m_pElemRadioButtonWind7_11;
extern gslc_tsElemRef* m_pElemTextbox_Log3;
extern gslc_tsElemRef* m_pTextSliderLog;
extern gslc_tsElemRef* m_pElemKeyPadAlpha;
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
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANSBOLD12,GSLC_FONTREF_PTR,&FreeSansBold12pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANSBOLD18,GSLC_FONTREF_PTR,&FreeSansBold18pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESERIF12,GSLC_FONTREF_PTR,&FreeSerif12pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESERIF9,GSLC_FONTREF_PTR,&FreeSerif9pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESERIFBOLD12,GSLC_FONTREF_PTR,&FreeSerifBold12pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESERIFBOLD9,GSLC_FONTREF_PTR,&FreeSerifBold9pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSERIFBOLD20,GSLC_FONTREF_PTR,&NotoSerifBold20pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSERIFBOLDITALIC22,GSLC_FONTREF_PTR,&NotoSerifBoldItalic22pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_BASE,m_asBasePage1Elem,MAX_ELEM_PG_BASE_RAM,m_asBasePage1ElemRef,MAX_ELEM_PG_BASE);
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_AP,m_asPage2Elem,MAX_ELEM_PG_AP_RAM,m_asPage2ElemRef,MAX_ELEM_PG_AP);
  gslc_PageAdd(&m_gui,E_PG_SPLASH_SCREEN,m_asPopup1Elem,MAX_ELEM_PG_SPLASH_SCREEN_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_SPLASH_SCREEN);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_ALPHA,m_asKeypadAlphaElem,1,m_asKeypadAlphaElemRef,1);  // KeyPad

  // Now mark E_PG_BASE as a "base" page which means that it's elements
  // are always visible. This is useful for common page elements.
  gslc_SetPageBase(&m_gui, E_PG_BASE);


  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_GRAY);

  // -----------------------------------
  // PAGE: E_PG_BASE
  
  
  // create E_ELEM_PAGE_LEFT button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_PAGE_LEFT,E_PG_BASE,
    (gslc_tsRect){5,290,20,20},(char*)"<",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // create E_ELEM_BTN_PAGE_RIGHT button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PAGE_RIGHT,E_PG_BASE,
    (gslc_tsRect){210,290,20,20},(char*)">",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_ELEM_TEXT20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT20,E_PG_MAIN,(gslc_tsRect){42,10,155,21},
    (char*)"Diagnostic Log",0,E_FREESERIFBOLD12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
   
  // Create wrapping box for textbox E_ELEM_TEXTBOX3 and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){10,45,220,235});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX3,E_PG_MAIN,&m_sTextbox3,
    (gslc_tsRect){10+2,45+4,220-4-20,235-7},E_BUILTIN5X8,
    (char*)&m_acTextboxBuf3,6,28);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_BLACK);
  m_pElemTextbox_Log3 = pElemRef;

  // Create vertical scrollbar for textbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_TXTSCROLL_LOG,E_PG_MAIN,&m_sTextScroll3,
          (gslc_tsRect){10+220-2-20,45+4,20,235-8},0,100,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pTextSliderLog = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_AP
  
  
  // Create E_ELEM_TEXTINPUT3 text input field
  static char m_sInputText3[11] = "123D Mag";
  gslc_ElemCreateTxt_P_R_ext(&m_gui,E_ELEM_TEXTINPUT3,E_PG_AP,20,10,198,40,
    m_sInputText3,11,&m_asFont[E_FREESANSBOLD18],
    GSLC_COL_MAGENTA,GSLC_COL_MAGENTA,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_ALIGN_MID_MID,20,20,
    true,true,true,false,NULL,NULL,&CbBtnCommon,NULL);
  m_pElemDisplay2_3 = gslc_PageFindElemById(&m_gui,E_PG_AP,E_ELEM_TEXTINPUT3);
  
  // create E_ELEM_BTN25 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN25,E_PG_AP,
    (gslc_tsRect){79,128,80,30},(char*)"Stdby",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_RED,GSLC_COL_RED_DK4);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnStandby15_25 = pElemRef;
  
  // create E_ELEM_BTN26 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN26,E_PG_AP,
    (gslc_tsRect){79,163,80,30},(char*)"Auto",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_RED,GSLC_COL_RED_DK4);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnAuto16_26 = pElemRef;
  
  // create E_ELEM_BTN27 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN27,E_PG_AP,
    (gslc_tsRect){79,198,80,30},(char*)"Wind",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnWind17_27 = pElemRef;
  
  // create E_ELEM_BTN28 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN28,E_PG_AP,
    (gslc_tsRect){79,233,80,30},(char*)"Track",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnTrack18_28 = pElemRef;
  
  // create E_ELEM_BTN29 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN29,E_PG_AP,
    (gslc_tsRect){169,163,60,30},(char*)"+1",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnPlusOne19_29 = pElemRef;
  
  // create E_ELEM_BTN30 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN30,E_PG_AP,
    (gslc_tsRect){169,198,60,30},(char*)"+10",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnPlusTen20_30 = pElemRef;
  
  // create E_ELEM_BTN31 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN31,E_PG_AP,
    (gslc_tsRect){169,233,60,30},(char*)"Tack",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnStbdTack21_31 = pElemRef;
  
  // create E_ELEM_BTN32 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN32,E_PG_AP,
    (gslc_tsRect){9,163,60,30},(char*)"-1",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnMinusOne22_32 = pElemRef;
  
  // create E_ELEM_BTN33 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN33,E_PG_AP,
    (gslc_tsRect){9,198,60,30},(char*)"-10",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnMinusTen23_33 = pElemRef;
  
  // create E_ELEM_BTN34 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN34,E_PG_AP,
    (gslc_tsRect){9,233,60,30},(char*)"Tack",0,E_FREESANSBOLD12,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLUE_DK4,GSLC_COL_BLUE_DK1);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  m_pElemBtnPortTack24_34 = pElemRef;
   
  // Create E_ELEM_BOX4 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX4,E_PG_AP,(gslc_tsRect){10,60,220,50});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY,GSLC_COL_GRAY);
  
  // Create radio button E_ELEM_RADIO9
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO9,E_PG_AP,&m_asXRadio9,
    (gslc_tsRect){34,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,true);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonStandby5_9 = pElemRef;
  
  // Create radio button E_ELEM_RADIO10
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO10,E_PG_AP,&m_asXRadio10,
    (gslc_tsRect){84,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonAuto6_10 = pElemRef;
  
  // Create radio button E_ELEM_RADIO11
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO11,E_PG_AP,&m_asXRadio11,
    (gslc_tsRect){134,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonWind7_11 = pElemRef;
  
  // Create radio button E_ELEM_RADIO12
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO12,E_PG_AP,&m_asXRadio12,
    (gslc_tsRect){184,66,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_GREEN,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRadioButtonTrack8_12 = pElemRef;
  
  // Create E_ELEM_TEXT21 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT21,E_PG_AP,(gslc_tsRect){25,90,41,17},
    (char*)"Stdby",0,E_FREESERIF9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT22 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT22,E_PG_AP,(gslc_tsRect){75,90,36,12},
    (char*)"Auto",0,E_FREESERIF9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT23 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT23,E_PG_AP,(gslc_tsRect){120,90,40,13},
    (char*)"Wind",0,E_FREESERIF9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT24 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT24,E_PG_AP,(gslc_tsRect){175,90,43,13},
    (char*)"Track",0,E_FREESERIF9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT25 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT25,E_PG_AP,(gslc_tsRect){9,138,49,12},
    (char*)"PORT",0,E_FREESERIFBOLD9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_RED);
  
  // Create E_ELEM_TEXT26 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT26,E_PG_AP,(gslc_tsRect){174,138,45,12},
    (char*)"STBD",0,E_FREESERIFBOLD9);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN);

  // -----------------------------------
  // PAGE: E_PG_SPLASH_SCREEN
  
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_SPLASH_SCREEN,(gslc_tsRect){30,130,180,44},
    (char*)"Raymarine",0,E_NOTOSERIFBOLDITALIC22);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT9,E_PG_SPLASH_SCREEN,(gslc_tsRect){50,190,199,30},
    (char*)"Auto Pilot ",0,E_NOTOSERIFBOLD20);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PG_SPLASH_SCREEN,(gslc_tsRect){70,240,149,29},
    (char*)"Remote",0,E_NOTOSERIFBOLD20);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT_SW_BUILD_DATE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_SW_BUILD_DATE,E_PG_SPLASH_SCREEN,(gslc_tsRect){90,400,129,18},
    (char*)"<Build Date>",0,E_FREESERIF12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_ALPHA
  
  static gslc_tsXKeyPadCfg_Alpha sCfgTx;
  sCfgTx = gslc_ElemXKeyPadCfgInit_Alpha();
  m_pElemKeyPadAlpha = gslc_ElemXKeyPadCreate_Alpha(&m_gui, E_ELEM_KEYPAD_ALPHA, E_POP_KEYPAD_ALPHA,
    &m_sKeyPadAlpha, 65, 80, E_BUILTIN5X8, &sCfgTx);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadAlpha, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 2);
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
