#include "GSLC_Helpers.h"

////
// GSLC_Helpers
//
GSLC_Helpers::GSLC_Helpers(gslc_tsGui* _pGui, gslc_tsElemRef** _ppElemRef) 
{
  pGui=_pGui; 
  ppElemRef=_ppElemRef;
}

////
// GSLC_RadioBtn_Helper 
//
GSLC_RadioBtn_Helper::GSLC_RadioBtn_Helper(gslc_tsGui* _pGui, gslc_tsElemRef** _ppElemRef) : GSLC_Helpers(_pGui, _ppElemRef) {}

void GSLC_RadioBtn_Helper::setStatus(bool Status) {
  gslc_ElemXCheckboxSetState(pGui, *ppElemRef, Status);
}


////
// GSLC_TextBox_Helper 
//
GSLC_TextBox_Helper::GSLC_TextBox_Helper(gslc_tsGui* _pGui, gslc_tsElemRef** _ppElemRef, gslc_tsElemRef** _ppSliderRef) : GSLC_Helpers(_pGui, _ppElemRef) 
{
  ppSliderRef = _ppSliderRef;
}

void GSLC_TextBox_Helper::clear() {
  gslc_ElemXTextboxReset(pGui, *ppElemRef);

  // also reset the slider / scrollbar.
  gslc_ElemXSliderSetPos(pGui, *ppSliderRef, 0);
}

// A printf for GSLC Textbox elements, max 100 chars
void GSLC_TextBox_Helper::printf(const char* format, ...){
  char cDisp[MAX_STR] = {0};
  va_list args;

  va_start( args, format );
  //vsprintf( cDisp, format, args );
  vsnprintf(cDisp,MAX_STR,format, args);
  va_end( args );

  // Only output if we are in play mode, otherwize lines are discarded.
  if (getTextOutStatus()== TxtOutStatusEnum::TxtOutPlay){
      gslc_ElemXTextboxAdd(pGui, *ppElemRef, cDisp); 

    // Get textbox extended data...
    gslc_tsElem*      pElem = gslc_GetElemFromRef(pGui,*ppElemRef);
    gslc_tsXTextbox*  pBox = (gslc_tsXTextbox*)(pElem->pXData);

    // DCB if the line added scrolls off the bottom of the visible screen, scrollup
    if (pBox->nBufPosY >= pBox->nScrollPos+pBox->nWndRows) {
      // update the scroll position...
      pBox->nScrollPos = pBox->nBufPosY-pBox->nWndRows+1;
      gslc_ElemXSliderSetPos(pGui,*ppSliderRef, pBox->nScrollPos);

      // Ensure all rows get redrawn
      pBox->nRedrawRow = XTEXTBOX_REDRAW_ALL;
    }
  }
};

////
// GSLC_Txt_Helper 
//
GSLC_Txt_Helper::GSLC_Txt_Helper(gslc_tsGui* _pGui, gslc_tsElemRef** _ppElemRef) : GSLC_Helpers(_pGui, _ppElemRef) {}

// A printf for GSLC Txt elements, max 100 chars
// TODO: one that accepts a String might be good, similar to Serial.println
void GSLC_Txt_Helper::printf(const char* format, ...){
  char cDisp[MAX_STR] = {0};
  va_list args;

  va_start( args, format );
  vsnprintf( cDisp, MAX_STR, format, args );
  va_end( args );

  gslc_ElemSetTxtStr(pGui, *ppElemRef, cDisp); 
};