//
//  CMBMenuNode.hpp
//
//  Author:          Michael Bernhard
//  Available from:  https://github.com/mchlbrnhrd/mbLib
//
//  Description:     C++ class to create nodes for menu which is used by CMBMenu.
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

#ifndef CMBMenuNode_hpp
#define CMBMenuNode_hpp

#include <string.h>
#ifdef ARDUINO_EMULATOR
#include "ArduinoEmulator.h"
#else
#include "Arduino.h"
#endif
#include <stdint.h>

class CMBMenuNode {
public:
  
  // default constructor
  CMBMenuNode();
  
  // constructor
  CMBMenuNode(const char* const f_Text, const int f_FID, const uint8_t f_Layer=0);
  
  // destructor
  ~CMBMenuNode();
  
  // get info
  void getInfo(const char*& f_Info);
  
  // get function identifier (FID)
  inline int getFID() {return m_FID;};
  
  // set layer
  void setLayer(const uint8_t f_Layer);
  
  // get layer
  uint8_t getLayer(){return m_Layer;};
  
protected:
  
  // text
  const char* m_Text;
  
  // function identifer (FID)
  int m_FID;
  
  // init method
  void init(const char* const f_Text, const int f_FID, const uint8_t f_Layer=0);
  
  // layer
  uint8_t m_Layer;
};

#endif /* CMBMenuNode_hpp */
