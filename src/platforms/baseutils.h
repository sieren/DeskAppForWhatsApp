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


#ifndef BASEUTILS
#define BASEUTILS
#include <QSystemTrayIcon>
#include "../utilities.hpp"

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

#define UNUSED(x) (void)(x)

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

namespace deskapp
{
namespace platforms
{
namespace generic
{
  class BaseUtils
  {
  public:
     virtual void showDockIcon(bool show) { UNUSED(show); }
     virtual void showMessage(
        QSystemTrayIcon *mpIcon, NotificationData data, ReplyCallback cb = 0)
    {
      UNUSED(cb);
      mpIcon->showMessage(std::get<0>(data).c_str(), std::get<1>(data).c_str(),
        QSystemTrayIcon::Warning, 1000);
    }
  protected:
     ReplyCallback mReplyCallback;
  };

} // generic
} // platforms
} // deskapp

#endif // BASEUTILS

