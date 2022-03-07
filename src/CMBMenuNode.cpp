//
//  CMBMenuNode.cpp
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

#include "CMBMenuNode.hpp"

//==========================================================================================
//  default constructor
//==========================================================================================
CMBMenuNode::CMBMenuNode()
{
  init("",0);
}


//==========================================================================================
//  additional constructor
//==========================================================================================
CMBMenuNode::CMBMenuNode(const char * const f_Text,
             const int f_FID,
             const uint8_t f_Layer // = 0
)
{
  init(f_Text, f_FID, f_Layer);
}


//==========================================================================================
//  destructor
//==========================================================================================
CMBMenuNode::~CMBMenuNode()
{
  
}


//==========================================================================================
//  get info
//==========================================================================================
void CMBMenuNode::getInfo(const char*& f_Info)
{
  f_Info = m_Text;
}


//==========================================================================================
//  init method
//==========================================================================================
void CMBMenuNode::init(const char * const f_Text,
                 const int f_FID,
                 const uint8_t f_Layer // = 0
)
{
  m_Text = f_Text;
  m_FID = f_FID;
  m_Layer = f_Layer;
}


//==========================================================================================
//  set layer
//==========================================================================================
void CMBMenuNode::setLayer(const uint8_t f_Layer)
{
  m_Layer = f_Layer;
}

