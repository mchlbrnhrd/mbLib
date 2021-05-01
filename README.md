# mbLib
Library for microcontroller projects with helper funtions and classes.

# MBHelper
Helper functions:
* void stringFromPgm(const char* f_StringPgm_pc, String& f_Value);<br>
  _get string from progmem (PGM)_
* void lcdCharArrayFromPgm(const uint8_t* f_Pgm_pc, uint8_t* f_Value);<br>
  _get char array from progmem (PGM)_
* void formatTime(unsigned long f_Seconds, String& f_Result);<br>
 _format time out from "seconds": h:mm:ss_
* void formatTimeMillis(unsigned long f_Milliseconds, String& f_Result);<br>
_format time out from "milliseconds": h:mm:ss.ms_
* void formatInt(int f_Value, int f_Length, String& f_Result);<br>
_format integer_

# MBMenu

Class to create menu for liquid crystal display (LCD)
 
## Example

Menu should look like:
1. Foo<br>
  1.1 FooA<br>
  1.2 FooB<br>
2. Bar<br>
  2.1 BarA<br>
  
```C++  
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

