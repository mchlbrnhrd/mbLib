# mbLib
Library for microcontroller projects with helper funtions and classes.

![watering system](doc/watering_system_small.jpg)

This software supports:
* start pump when moisture of soil is too low
* start pump after time out (e.g. after one day)
* stop pump when moisture is high enough or after a timeout (e.g. at least after 20 seconds)
* interact via terminal (seriell monitor of arduino IDE):
  - check sensor values
  - start and stop pump manualy
  - change values of variables during runtime (thresholds, time durations)
  - activate debug mode: print sensor values continously and internal states of software.
  - get log data (sensor data will be recorded every hour)
  - start auto calibraton
* Internet of Things (IoT) with Arduino Yún:
  - save log files and settings on SD card
  - push files to a server
  - evaluate log files and show graphically from remote

# MBHelper
Helper functions:
* void stringFromPgm(const char* f_StringPgm_pc, String& f_Value);
  _get string from progmem (PGM)_
* void lcdCharArrayFromPgm(const uint8_t* f_Pgm_pc, uint8_t* f_Value);
  _get char array from progmem (PGM)_
* void formatTime(unsigned long f_Seconds, String& f_Result);
 _format time out from "seconds": h:mm:ss_
* void formatTimeMillis(unsigned long f_Milliseconds, String& f_Result);
_format time out from "milliseconds": h:mm:ss.ms_
* void formatInt(int f_Value, int f_Length, String& f_Result);
_format integer_

# MBMenu

Class to create menu for liquid crystal display (LCD)

Idea: 
## Example

Menu should look like:
1. Foo
  1.1 FooA
  1.2 FooB
2. Bar
  2.1 BarA
  
  
// define text to display
const char MenuFoo_pc[] PROGMEM = {"1. Foo"};
const char MenuFoo_pc[] PROGMEM = {"1.1 FooA"};
const char MenuFoo_pc[] PROGMEM = {"1.2 FooB"};
const char MenuFoo_pc[] PROGMEM = {"2. Bar"};
const char MenuFoo_pc[] PROGMEM = {"2.1 BarA"};

// define function IDs
enum MenuFID {
MenuDummy,
MenuFoo,
MenuFooA,
MenuFooB,
MenuBar,
MenuBarA
}

// create CMBMenu instance
CMBMenu<100> g_Menu;

// add nodes
g_Menu.addNode(0, MenuFoo_pc , MenuFoo);
g_Menu.addNode(1, MenuFooA_pc, MenuFooA);
g_Menu.addNode(1, MenuFooB_pc, MenuFooB);

g_Menu.addNode(0, MenuBar_pc, MenuBar);
g_Menu.addNode(1, MenuBarA_pc, MenuBarA);

const char* info;
int fid = g_Menu.buildMenu(info);

g_Menu.printMenu();

