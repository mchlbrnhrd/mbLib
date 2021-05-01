//
//  CMBMenuNode.hpp
//  Menu_test
//
//  Created by Michael on 13.09.20.
//  Copyright © 2020 ___MICHAEL_BERNHARD___. All rights reserved.
//

#ifndef CMBMenuNode_hpp
#define CMBMenuNode_hpp

#include <string.h>
#ifdef ARDUINO_EMULATOR
#include "ArduinoEmulator.h"
#else
#include "Arduino.h"
#endif

class CMBMenuNode {
public:
  
  // default constructor
  CMBMenuNode();
  
  // constructor
  CMBMenuNode(const char* const f_Text, int f_FID, uint8_t f_Layer=0);
  
  // destructor
  ~CMBMenuNode();
  
  // get info
  void getInfo(const char*& f_Info);
  
  // get function identifier (FID)
  inline int getFID() {return m_FID;};
  
  // set layer
  void setLayer(uint8_t f_Layer);
  
  // get layer
  uint8_t getLayer(){return m_Layer;};
  
protected:
  
  // text
  const char* m_Text;
  
  // function identifer (FID)
  int m_FID;
  
  // init method
  void init(const char* const f_Text, int f_FID, uint8_t f_Layer=0);
  
  // layer
  uint8_t m_Layer;
};

#endif /* CMBMenuNode_hpp */
