//
//  MBHelper.cpp
//  MBHelper
//
//  Created by Michael on 13.09.20.
//  Copyright © 2020 ___MICHAEL_BERNHARD___. All rights reserved.
//

#include "MBHelper.hpp"


namespace  {
//==========================================================================================
//  global variable
//==========================================================================================

}

namespace MBHelper {
  //void test();
 
  
  //******************************************************************************************
  //  module function
  //******************************************************************************************
  // void test()
  //{
  //
  //}
  
}

//==========================================================================================
//  string from PGM
//==========================================================================================
void MBHelper::stringFromPgm(const char* f_StringPgm_pc, String& f_Value)
{
  if (0 != f_StringPgm_pc) {
    const int len = (int)strlen_P(f_StringPgm_pc);
    for (int k = 0; k < len; ++k) {
      f_Value += (char)pgm_read_byte_near(f_StringPgm_pc + k);
    }
  }
}

//==========================================================================================
//  char array for LCD from PGM
//==========================================================================================
 void MBHelper::lcdCharArrayFromPgm(const uint8_t* f_Pgm_pc, uint8_t* f_Value)
{
  for (uint8_t k=0; k < 8; ++k) {
    f_Value[k] = (uint8_t)pgm_read_byte_near(f_Pgm_pc+k);
  }
}

//==========================================================================================
//  format seconds into h:mm:ss
//==========================================================================================
void MBHelper::formatTime(unsigned long f_Seconds, String& f_Result)
{
  unsigned long hours = f_Seconds / 60UL / 60UL;
  unsigned long minutes = (f_Seconds - hours * 60UL * 60UL) / 60UL;
  unsigned long seconds = f_Seconds - hours * 60UL * 60UL - minutes * 60UL;
  f_Result = String((unsigned)hours);
  f_Result += ":";
  if (minutes < 10) {
    f_Result += "0";
  }
  f_Result += String((unsigned)minutes);
  f_Result += ":";
  if (seconds < 10) {
    f_Result += "0";
  }
  f_Result += String((unsigned)seconds);
}


//==========================================================================================
//  format milliseconds into h:mm:ss.ms
//==========================================================================================
void MBHelper::formatTimeMillis(unsigned long f_Milliseconds, String& f_Result)
{
  unsigned long hours = f_Milliseconds / 60UL / 60UL / 1000UL;
  unsigned long minutes = (f_Milliseconds - hours * 60UL * 60UL * 1000UL) / 60UL / 1000UL;
  unsigned long seconds = (f_Milliseconds - hours * 60UL * 60UL * 1000UL - minutes * 60UL * 1000UL) / 1000UL;
  unsigned long milliseconds = f_Milliseconds - hours * 60UL * 60UL * 1000UL - minutes * 60UL * 1000UL - seconds * 1000UL;
  // hours
  f_Result = String((unsigned)hours);
  
  // minutes
  f_Result += ":";
  if (minutes < 10) {
    f_Result += "0";
  }
  f_Result += String((unsigned)minutes);
  
  // seconds
  f_Result += ":";
  if (seconds < 10) {
    f_Result += "0";
  }
  f_Result += String((unsigned)seconds);
  
  // milliseconds
  f_Result += ".";
  if (milliseconds < 10) {
    f_Result += "00";
  } else if (milliseconds < 100) {
    f_Result += "0";
  }
  f_Result += String((unsigned) milliseconds);
}


//==========================================================================================
//  format integer: (f, 3, s) => s = "  4"
//==========================================================================================
void MBHelper::formatInt(int f_Value, int f_Length, String &f_Result)
{
  String val = String(f_Value);
  f_Result = "";
  for (int k=0; k < f_Length - (int)val.length(); ++k) {
    f_Result += " ";
  }
  f_Result += val;
}
