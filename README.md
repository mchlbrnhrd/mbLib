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

Class to create menu for liquid crystal display (LCD). Designed for easy use.
First setup menu by adding nodes with _addNode_ method. There you set the layer, the text to display and a function ID (FID).
To navigate in the menu just call _right()_, _left()_, _enter()_ and _exit()_. Then you can check the FID and take action by calling functions for example.
 
## Example

Menu should look like:
1. Foo<br>
  1.1 FooA<br>
  1.2 FooB<br>
2. Bar<br>
  2.1 BarA<br>
  
```C++  
// ********************************************
// some definitions
// ********************************************
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


// ********************************************
// create/setup menu
// ********************************************
// create CMBMenu instance (here for maximum 100 menu entries)
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


// ********************************************
// use menu
// ********************************************
loop() {
  // function ID
  int fid = 0;

  int key=getKey();

  // go to deeper or upper layer?
  bool layerChanged=false;

  // assume key holds current pressed key on a keyboard
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
  
  if (KeyNone != key) {
    // get current function ID and print menu
    fid = g_Menu.getInfo(info);
    printMenuEntry(info, fid);
    delay(100);
  }
  
  if ((0 != fid) && (KeyEnter == key) && (!layerChanged)) {
    switch (fid) {
      case MenuFooA:
        callFooA();
        break;
      case MenuFooB:
        callFooB();
        break;
      case MenuBarA:
        callBarA();
        break;
      default:
        break;
    }
  }
}

// example to print menu
void printMenuEntry(const char* f_Info, const int f_Fid)
{
  String info_s;
  MBHelper::stringFromPgm(f_Info, info_s);
  g_Lcd.clear();
  g_Lcd.setCursor(0, 0);
  g_Lcd.print(info_s);
}
```

