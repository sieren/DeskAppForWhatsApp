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

#ifndef QSyncthingTray_posixUtils_hpp
#define QSyncthingTray_posixUtils_hpp
#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <Carbon/Carbon.h>
#include "../baseutils.h"

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

namespace deskapp
{
namespace platforms
{
namespace darwin
{
  using namespace generic;
  class MacUtils : public BaseUtils
  {
  public:
    MacUtils(QString url);
    MacUtils() = default;
    ~MacUtils();

    void showDockIcon(bool show) override
    {
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
      ProcessSerialNumber psn;
      UInt32 transformState = show ? kProcessTransformToForegroundApplication :
        kProcessTransformToUIElementApplication;
      if (GetCurrentProcess(&psn) == noErr)
      {
        TransformProcessType(&psn,
          transformState);
      }
    #pragma clang diagnostic pop
    }

    int getTrayFontPointSize() override
    {
       return 400;
    }

    virtual void showMessage(
       QSystemTrayIcon *mpIcon, NotificationData data, ReplyCallback cb = 0) override;
    
  private:
    class UpdateContainer;
    UpdateContainer *sparkleContainer;

  };
} // darwin
} // platforms
} // deskapp


#endif
