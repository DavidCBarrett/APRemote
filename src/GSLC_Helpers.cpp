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
// GSLC_TextBox_Helper 
//
GSLC_TextBox_Helper::GSLC_TextBox_Helper(gslc_tsGui* _pGui, gslc_tsElemRef** _ppElemRef) : GSLC_Helpers(_pGui, _ppElemRef) {}

void GSLC_TextBox_Helper::clear() {
  gslc_ElemXTextboxReset(pGui, *ppElemRef);
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
  if (getTextOutStatus()== TxtOutStatusEnum::TxtOutPlay)  gslc_ElemXTextboxAdd(pGui, *ppElemRef, cDisp); 
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