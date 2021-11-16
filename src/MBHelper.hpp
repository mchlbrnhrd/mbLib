//
//  CMBMenuNode.hpp
//  Menu_test
//
//  Created by Michael on 13.09.20.
//  Copyright © 2020 ___MICHAEL_BERNHARD___. All rights reserved.
//

#ifndef MBHelper_hpp
#define MBHelper_hpp

#ifdef ARDUINO_EMULATOR
#include "ArduinoEmulator.h"
#else
#include "Arduino.h"
#endif
#include <stdint.h>

//==========================================================================================
//  constants
//==========================================================================================

// store text in PROGMEM example:
// const char g_PgmMenuFunctionTest_pc[] PROGMEM  = {"1. function test"};

namespace MBHelper
{
  enum timeFormat_en {
    TimeFormatMillis_enm = 0,
    TimeFormatSeconds_enm = 1,
    TimeFormatMinutes_enm = 2,
    TimeFormatHours_enm = 3,
    TimeFormat_H_MM_SS_MS_enm = 4,
    TimeFormat_H_MM_SS_enm = 5,
    TimeFormat_HH_MM_SS_enm = 6,
    TimeFormat_HH_MM_enm=7
  };
  
  // get string from progmem (PGM)
  void stringFromPgm(const char* f_StringPgm_pc, String& f_Value);
  
  // get char array from progmem (PGM)
  void lcdCharArrayFromPgm(const uint8_t* f_Pgm_pc, uint8_t* f_Value);
  
  void formatTime(unsigned long f_Value_ul, String& f_Result_s, const timeFormat_en f_From_en, const timeFormat_en f_To_en);
  
  // format time out from "seconds": h:mm:ss
  void formatTime(unsigned long f_Seconds, String& f_Result);
  
  // format time out from "seconds": hh:mm
  void formatTimeHHMM(unsigned long f_Seconds, String& f_Result);
  
  // format time out from "milliseconds": h:mm:ss.ms
  void formatTimeMillis(unsigned long f_Milliseconds, String& f_Result);
  
  // format integer
  void formatInt(const int f_Value, const int f_Length, String& f_Result, const char f_Fill_cc=' ');
};

#endif /* MBHelper_hpp */
