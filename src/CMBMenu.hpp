//
//  CMBMenu.hpp
//
//  Author:          Michael Bernhard
//  Available from:  https://github.com/mchlbrnhrd/mbLib
//
//  Description:     C++ class to create menu for liquid crystal display (LCD) for example.
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

#ifndef CMBMenu_hpp
#define CMBMenu_hpp

#ifdef ARDUINO_EMULATOR
#include "ArduinoEmulator.h"
#else
#include "Arduino.h"
#endif
#include "CMBMenuNode.hpp"
#include "MBHelper.hpp"
#include <stdint.h>

// template class
template <int maxElements> class CMBMenu {
public:
  
  //==========================================================================================
  //  constructor
  //==========================================================================================
  CMBMenu(){
    m_index = 0;
    m_topNode = 0;
    m_numUsedElements = 0;
  }
  
  
  //==========================================================================================
  //  destructor
  //==========================================================================================
  ~CMBMenu(){}

  
  //==========================================================================================
  //  add node to menu
  //==========================================================================================
  void addNode(const CMBMenuNode& f_Node) {
    if (m_index < maxElements) {
      m_nodes[m_index++]=f_Node;
      ++m_numUsedElements;
    }
  }
  
  
  //==========================================================================================
  //  add node to menu
  //==========================================================================================
  void addNode(int f_Layer, const char* const f_Text, const int f_FID) {
    if (m_index < maxElements) {
      m_nodes[m_index] = CMBMenuNode(f_Text, f_FID, f_Layer);
      ++m_index;
      ++m_numUsedElements;
    }
  }
  
  
  //==========================================================================================
  //  print menu
  //==========================================================================================
  void printMenu() {
    Serial.println(F("menu:"));
    for (int i=0; i < m_numUsedElements; ++i) {
      for (int k=0; k < m_nodes[i].getLayer(); ++k) {
        Serial.print(F("  "));
      }
      const char* info;
      m_nodes[i].getInfo(info);
      String info_s;
      MBHelper::stringFromPgm(info, info_s);
      Serial.print(info_s);
      Serial.print(F(", "));
      Serial.println(m_nodes[i].getFID());
    }
  }
  
  
  //==========================================================================================
  //  enter
  //==========================================================================================
  void enter() {
    bool layerChangedDummy;
    enter(layerChangedDummy);
  }
  
  
  //==========================================================================================
  //  enter
  //==========================================================================================
  void enter(bool& f_LayerChanged) {
    f_LayerChanged=false;
    if (m_index+1 < m_numUsedElements) {
      if (m_nodes[m_index+1].getLayer() == m_nodes[m_index].getLayer()+1) {
        ++m_index;
        f_LayerChanged=true;
      }
    }
  }
  
  
  //==========================================================================================
  //  exit
  //==========================================================================================
  void exit() {
    if (m_nodes[m_index].getLayer() > 0 && m_index > 0) {
      // seek for exit node in backwards direction
      int ctr = m_index - 1;
      int exitNodeIdx = -1;
      while ((-1 == exitNodeIdx) && (ctr >= 0)) {
        if (m_nodes[ctr].getLayer()+1 == m_nodes[m_index].getLayer()) {
          exitNodeIdx = ctr;
        }
        --ctr;
      }
      if (exitNodeIdx != -1) {
        m_index = exitNodeIdx;
      }
    }
  }
  
  
  //==========================================================================================
  //  left
  //==========================================================================================
  void left() {
    if (m_index > 0) {
      // seek left node in backwards direction
      int ctr = m_index - 1;
      int leftNodeIdx = -1;
      while ((-1 == leftNodeIdx) && (ctr >= 0) &&
             (m_nodes[ctr].getLayer() >= m_nodes[m_index].getLayer())) {
        if (m_nodes[ctr].getLayer() == m_nodes[m_index].getLayer()) {
          leftNodeIdx = ctr;
        }
        --ctr;
      }
      if (-1 != leftNodeIdx) {
        m_index = leftNodeIdx;
      }
    }
  }
  
  
  //==========================================================================================
  //  right
  //==========================================================================================
  void right() {
    int rightNodeIdx = -1;
    int ctr = m_index + 1;
    while ((-1 == rightNodeIdx) && (ctr < m_numUsedElements) &&
           (m_nodes[ctr].getLayer() >= m_nodes[m_index].getLayer())){
      if (m_nodes[ctr].getLayer() == m_nodes[m_index].getLayer()) {
        rightNodeIdx = ctr;
      }
      ++ctr;
    }
    if (-1 != rightNodeIdx) {
      m_index = rightNodeIdx;
    }
  }
  
  
  //==========================================================================================
  //  setMenuNode
  //==========================================================================================
  void setMenuNode(const int f_FID)
  {
    // seek for first match of f_FID and set current menu node to this
    bool found=false;
    int ctr=0;
    while ((!found) && (ctr < m_numUsedElements)) {
      if (f_FID == m_nodes[ctr].getFID()) {
        m_index=ctr;
        found=true;
      }
      ++ctr;
    }
  }
  
  
  //==========================================================================================
  //  getInfo
  //==========================================================================================
  int getInfo(const char*& f_Info) {
    m_nodes[m_index].getInfo(f_Info);
    return m_nodes[m_index].getFID();
  }
  
  
  //==========================================================================================
  //  getFID
  //==========================================================================================
  int getFID() {
    return m_nodes[m_index].getFID();
  }
  
  
  //==========================================================================================
  //  build menu
  //==========================================================================================
  int buildMenu(const char* &f_Info) {
    //    m_nodes[0].buildMenu(0);
    m_index = 0; // new version
    m_nodes[m_index].getInfo(f_Info);
    return m_nodes[m_index].getFID();
  }
  
  /*
  void addChapter() {
    addNode(1,);
  }
  
  void addSection() {
    addNode(2,);
  }
  
  void addSubSection() {
    addNode(3,);
  }
  
  void addSubSubSection() {
    addNode(4,);
  }

  */
private:
  
  // array of all nodes
  CMBMenuNode m_nodes[maxElements];
  
  // pointer to top node
  CMBMenuNode* m_topNode;
  
  // index
  int m_index;
  
  // number of used elements; can be less then maxElements
  int m_numUsedElements;
};

#endif /* CMBMenu_hpp */
