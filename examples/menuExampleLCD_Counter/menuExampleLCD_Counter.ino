/*
 * mblib - MB library
 *
 * created by Michael Bernhard
 *
 * Example how to create a menu for LCD with variable to count.
 * Serial monitor (terminal) is also used.
 * 
 * Example by Ekhiw
 * 
 * Code for C++ class CMBMenu is marked with ** menu **
 * the other code are helper function sfor demonstration
 *
 *
 * https://github.com/mchlbrnhrd/mbLib
 */

//
// GNU General Public License v3.0
//
// Copyright (C) 2022  Michael Bernhard
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


// ** menu **
// include CMBMenu
#include "CMBMenu.hpp"

// include library for LCD for IC2
#include "LiquidCrystal_I2C.h"

// ********************************************
// definitions
// ********************************************
// LCD pins
const uint8_t g_PinLcdScl_ui8c = A5; // SCL
const uint8_t g_PinLcdSda_ui8c = A4; // SDA

// Counter variable
bool countModeFlag = false;
int counterA = 0;
int counterB1 = 0;
int counterB2 = 0;
int variable = 0;

// define text to display
const char g_MenuCounter_pc[] PROGMEM = {"1. Counter"};
const char g_MenuCounterA_pc[] PROGMEM = {"1.1 CounterA"};
const char g_MenuCounterB_pc[] PROGMEM = {"1.2 CounterB"};
const char g_MenuCounterB1_pc[] PROGMEM = {"1.2.1 CounterB1"};
const char g_MenuCounterB2_pc[] PROGMEM = {"1.2.2 CounterB2"};
const char g_MenuVariable_pc[] PROGMEM = {"2. Variable"};


// define function IDs
enum MenuFID {
  MenuDummy, // Reserved (index 0)
  MenuCounter,
  MenuCounterA,
  MenuCounterB,
  MenuCounterB1,
  MenuCounterB2,
  MenuVariable
};

// define key types
enum KeyType {
  KeyNone, // Reserved (no key is pressed)
  KeyLeft,
  KeyRight,
  KeyEnter,
  KeyExit
};

// ** menu **
// create global CMBMenu instance
// (here for maximum 100 menu entries)
CMBMenu<100> g_Menu;

// LCD, here 16x2 characters; SCL at A5, SDA at A4
LiquidCrystal_I2C g_Lcd(0x27, 16, 2);

// ********************************************
// setup
// ********************************************
void setup()
{
  // LCD
  pinMode(g_PinLcdScl_ui8c, OUTPUT);
  pinMode(g_PinLcdSda_ui8c, OUTPUT);
  g_Lcd.init();
  g_Lcd.backlight();
  g_Lcd.clear();
  g_Lcd.print("mblib example");
  delay(1000);

  Serial.begin(115200);
  Serial.println("===========================");
  Serial.println("mblib - example for CMBMenu");
  Serial.println("===========================");
  Serial.println("");
  Serial.println("l: left, r: right, e: enter, x: exit, m: print menu");
  Serial.println("");

  // ** menu **
  // add nodes to menu (layer, string, function ID)
  g_Menu.addNode(0, g_MenuCounter_pc, MenuCounter);
  g_Menu.addNode(1, g_MenuCounterA_pc, MenuCounterA);
  g_Menu.addNode(1, g_MenuCounterB_pc, MenuCounterB);
  g_Menu.addNode(2, g_MenuCounterB1_pc, MenuCounterB1);
  g_Menu.addNode(2, g_MenuCounterB2_pc, MenuCounterB2);

  g_Menu.addNode(0, g_MenuVariable_pc, MenuVariable);


  // ** menu **
  // build menu and print menu
  // (see terminal for output)
  const char* info;
  g_Menu.buildMenu(info);
  g_Menu.printMenu();

  // ** menu **
  // print current menu entry
   printMenuEntry(info);
}


// ********************************************
// loop
// ********************************************
void loop()
{
  // function ID
  int fid = 0;

  // info text from menu
  const char* info;

  // go to deeper or upper layer?
  bool layerChanged=false;

  // determine pressed key
  KeyType key = getKey();

  // ** menu **
  // call menu methods regarding pressed key
  if(!countModeFlag){
    switch(key) {
      case KeyExit:
        g_Menu.exit();
        break;
      case KeyEnter:
        g_Menu.enter(layerChanged);
        break;
      case KeyRight:
        g_Menu.right();
        break;
      case KeyLeft:
        g_Menu.left();
        break;
      default:
        break;
    }
  }

  // ** menu **
  // pint/update menu when key was pressed
  // and get current function ID "fid"
  if (KeyNone != key) {
    fid = g_Menu.getInfo(info);
    printMenuEntry(info);
  }

  // ** menu **
  // do action regarding function ID "fid"
  if ((0 != fid) && (KeyEnter == key) && (!layerChanged)) {
    switch (fid) {
      case MenuCounterA:
        if(!countModeFlag){
          g_Lcd.setCursor(0,1);
          g_Lcd.print(counterA);
        }
        toggleFlag();
        break;
      case MenuCounterB1:
        if(!countModeFlag){
          g_Lcd.setCursor(0,1);
          g_Lcd.print(counterB1);
        }
        toggleFlag();
        break;
      case MenuCounterB2:
        if(!countModeFlag){
          g_Lcd.setCursor(0,1);
          g_Lcd.print(counterB2);
        }
        toggleFlag();
        break;
      case MenuVariable:
        if(!countModeFlag){
          g_Lcd.setCursor(0,1);
          g_Lcd.print(variable);
        }
        toggleFlag();
        break;
      default:
        break;
    }
  }

  // MenuCounterA
  if ((fid == MenuCounterA) && countModeFlag && (!layerChanged)) {
    switch(key) {
      case KeyRight:
        counterA++;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(counterA);
        break;
      case KeyLeft:
        counterA--;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(counterA);
        break;
      default:
        handleExit(key,info);
        break;
    }
  }

  // MenuCounterB1
  if ((fid == MenuCounterB1) && countModeFlag && (!layerChanged)) {
    switch(key) {
      case KeyRight:
        counterB1++;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(counterB1);
        break;
      case KeyLeft:
        counterB1--;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(counterB1);
        break;
      default:
        handleExit(key,info);
        break;
    }
  }

  // MenuCounterB2
  if ((fid == MenuCounterB2) && countModeFlag && (!layerChanged)) {
    switch(key) {
      case KeyRight:
        counterB2++;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(counterB2);
        break;
      case KeyLeft:
        counterB2--;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(counterB2);
        break;
      default:
        handleExit(key,info);
        break;
    }
  }

  // Menuvariable
  if ((fid == MenuVariable) && countModeFlag && (!layerChanged)) {
    switch(key) {
      case KeyRight:
        variable++;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(variable);
        break;
      case KeyLeft:
        variable--;
        g_Lcd.setCursor(0,1);
        g_Lcd.print(variable);
        break;
      default:
        handleExit(key,info);
        break;
    }
  }

}


// ********************************************
// ** menu **
// printMenuEntry
// ********************************************
void printMenuEntry(const char* f_Info)
{
  String info_s;
  MBHelper::stringFromPgm(f_Info, info_s);

  // when using LCD: add/replace here code to
  // display info on LCD
  Serial.println("----------------");
  Serial.println(info_s);
  Serial.println("----------------");

  // print on LCD
  g_Lcd.clear();
  g_Lcd.setCursor(0, 0);
  g_Lcd.print(info_s);

  // you can print here additional infos into second line of LCD
  // g_Lcd.setCursor(0, 1);
  // g_Lcd.print("my text");
}


// ********************************************
// getKey
// ********************************************
KeyType getKey()
{
  KeyType key = KeyNone;

  // here for demonstration: get "pressed" key from terminal
  // replace code when using push buttons
  while(Serial.available() > 0) {
    String Key_s = Serial.readString();
    Key_s.trim();
    Serial.println("");
    if(Key_s.equals("l")) { // left
      key = KeyLeft;
      Serial.println("<left>");
    } else if (Key_s.equals("r")) { // right
      key = KeyRight;
      Serial.println("<right>");
    } else if (Key_s.equals("e")) { // enter
      key = KeyEnter;
      Serial.println("<enter>");
    } else if (Key_s.equals("x")) { // exit
      key = KeyExit;
      Serial.println("<exit>");
    } else if (Key_s.equals("m")) { // print menu
      g_Menu.printMenu();
    }
  }

 return key;
}


// ********************************************
// Count Mode Flag
// ********************************************
void toggleFlag()
{
  countModeFlag = !countModeFlag;
}

// ********************************************
// Count Mode Flag
// ********************************************

void handleExit(KeyType key,const char*& f_Info){
  if(key == KeyExit){
    countModeFlag = false;
    g_Menu.exit();
    g_Menu.getInfo(f_Info);
    printMenuEntry(f_Info);
  }
}
// ========================================================================
// naming convention
// prefix:
//   g  : global variable
//   f  : function/method variable
//   m  : private member of class
//      : without prefix: public member of class
//
//
// ========================================================================