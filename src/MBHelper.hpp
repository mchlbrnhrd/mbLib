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
//==========================================================================================
//  constants
//==========================================================================================

// store text in PROGMEM example:
// const char g_PgmMenuFunctionTest_pc[] PROGMEM  = {"1. function test"};

namespace MBHelper
{
  // get string from progmem (PGM)
  void stringFromPgm(const char* f_StringPgm_pc, String& f_Value);
  
  // get char array from progmem (PGM)
  void lcdCharArrayFromPgm(const uint8_t* f_Pgm_pc, uint8_t* f_Value);
  
  // format time out from "seconds": h:mm:ss
  void formatTime(unsigned long f_Seconds, String& f_Result);
  
  // format time out from "milliseconds": h:mm:ss.ms
  void formatTimeMillis(unsigned long f_Milliseconds, String& f_Result);
  
  // format integer
  void formatInt(int f_Value, int f_Length, String& f_Result);
};

#endif /* MBHelper_hpp */
