/**************************************************************************************
 // DeskApp for WhatsApp
 // Copyright (c) Matthias Frick, All rights reserved.
 //
 // This library is free software; you can redistribute it and/or
 // modify it under the terms of the GNU Lesser General Public
 // License as published by the Free Software Foundation; either
 // version 3.0 of the License, or (at your option) any later version.
 //
 // This library is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 // Lesser General Public License for more details.
 //
 // You should have received a copy of the GNU Lesser General Public
 // License along with this library.
 **************************************************************************************/

#ifndef QSyncthingTray_winUtils_hpp
#define QSyncthingTray_winUtils_hpp
#include <sstream>
#include <string>
#include <iostream>
#include <cstdio>
#include "../baseutils.h"
#include <windows.h>
#include <tlhelp32.h>
#include <comdef.h>

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

#define UNUSED(x) (void)(x)

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

namespace deskapp
{
namespace platforms
{
namespace windows
{
  struct WinUtils : public generic::BaseUtils
  {
    int getTrayFontPointSize() override
    {
       return 120;
    }
  };
} // windows
} // platforms
} // deskapp

#endif
