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
//  format value from given format (from) into user defined format (to)
//==========================================================================================
void MBHelper::formatTime(unsigned long f_Value_ul, String& f_Result_s, const timeFormat_en f_From_en, const timeFormat_en f_To_en)
{
  f_Result_s = "";
  const String l_Invalid_sc = "inv";
  String l_Tmp_s="";
  if (TimeFormatSeconds_enm == f_From_en) {
    unsigned long l_Hours_ul = f_Value_ul / 60UL / 60UL;
    unsigned long l_Minutes_ul = (f_Value_ul - l_Hours_ul * 60UL * 60UL) / 60UL;
    unsigned long l_Seconds_ul = f_Value_ul - l_Hours_ul * 60UL * 60UL - l_Minutes_ul * 60UL;
    if (TimeFormat_HH_MM_SS_enm == f_To_en) {
      formatInt((int)l_Hours_ul, 2, l_Tmp_s, '0');
      f_Result_s += l_Tmp_s;
      f_Result_s += ":";
      formatInt((int)l_Minutes_ul, 2, l_Tmp_s, '0');
      f_Result_s += l_Tmp_s;
      f_Result_s += ":";
      formatInt((int)l_Seconds_ul, 2, l_Tmp_s, '0');
      f_Result_s += l_Tmp_s;
    } else {
      f_Result_s = l_Invalid_sc;
    }
  } else if (TimeFormatMinutes_enm == f_From_en) {
    unsigned long l_Hours_ul = f_Value_ul / 60UL;
    unsigned long l_Minutes_ul = (f_Value_ul - l_Hours_ul * 60UL);
    if (TimeFormat_HH_MM_enm == f_To_en) {
      formatInt((int)l_Hours_ul, 2, l_Tmp_s, '0');
      f_Result_s += l_Tmp_s;
      f_Result_s += ":";
      formatInt((int)l_Minutes_ul, 2, l_Tmp_s, '0');
      f_Result_s += l_Tmp_s;
    }
    else
    {
      f_Result_s=l_Invalid_sc;
    }
  } else {
    f_Result_s=l_Invalid_sc;
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
//  format seconds into hh:mm
//==========================================================================================
void MBHelper::formatTimeHHMM(unsigned long f_Seconds, String& f_Result)
{
  unsigned long hours = f_Seconds / 60UL / 60UL;
  unsigned long minutes = (f_Seconds - hours * 60UL * 60UL) / 60UL;
  formatInt((int)hours, 2, f_Result);
  f_Result += ":";
  if (minutes < 10) {
    f_Result += "0";
  }
  f_Result += String((unsigned)minutes);
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
//  format integer: f=4; (f, 3, s) => s = "  4"
//==========================================================================================
void MBHelper::formatInt(const int f_Value, const int f_Length, String &f_Result, const char f_Fill_cc)
{
  const String val = String(f_Value);
  f_Result = "";
  for (int k=0; k < f_Length - (int)val.length(); ++k) {
    f_Result += f_Fill_cc;
  }
  f_Result += val;
}
