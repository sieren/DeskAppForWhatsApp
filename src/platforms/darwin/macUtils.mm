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

#import "macUtils.h"
#include <Foundation/Foundation.h>
#include "../../lib/Sparkle.framework/Headers/Sparkle.h"

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

@interface NotificationView : NSObject<NSUserNotificationCenterDelegate>
{
  ReplyCallback replyCallback;
}
-(void)showNotification:(NotificationData) data withCallback:(ReplyCallback)cb;
@end


//------------------------------------------------------------------------------------//

namespace
{

NotificationView *notificationView()
{
  static NotificationView *view = [NotificationView new];
  return view;
}

} // anon

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

namespace deskapp
{
namespace platforms
{
namespace darwin
{
  class MacUtils::UpdateContainer
  {
    public:
      UpdateContainer() = default;
      NSAutoreleasePool* autoReleasePool;
      SUUpdater *updater;

  };
  
  MacUtils::~MacUtils()
  {
    if (sparkleContainer)
    {
      [sparkleContainer->autoReleasePool release];
    }
  }

  MacUtils::MacUtils(QString url)
  {
    NSApplicationLoad();
    sparkleContainer = new UpdateContainer;
    sparkleContainer->autoReleasePool = [NSAutoreleasePool new];
    NSString *feedUrl = [NSString stringWithUTF8String: url.toUtf8().data()];
    [[NSUserDefaults standardUserDefaults] setValue:feedUrl forKey:@"SUFeedURL"];
    sparkleContainer->updater = [[SUUpdater sharedUpdater] retain];
  }

  void MacUtils::showMessage(
     QSystemTrayIcon *mpIcon, NotificationData data, ReplyCallback cb)
  {
    UNUSED(mpIcon);
    mReplyCallback = cb;
    [notificationView() showNotification:data withCallback:cb];
  }
} // darwin
} // platforms
} // deskapp

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

@implementation NotificationView

-(id) init
{
  if ((self = [super init]))
  {
    [NSUserNotificationCenter defaultUserNotificationCenter].delegate = self;
  }
  return self;
}


//------------------------------------------------------------------------------------//

-(void)userNotificationCenter:(NSUserNotificationCenter *)center
       didActivateNotification:(NSUserNotification *)notification
{
#pragma unused(center)
  replyCallback(std::make_tuple(
    [notification.response.string UTF8String],
    [notification.identifier UTF8String]));
}


//------------------------------------------------------------------------------------//

-(void)showNotification:(NotificationData)data withCallback:(ReplyCallback)cb
{
  replyCallback = cb;
  NSUserNotification *notification = [NSUserNotification new];
  notification.hasReplyButton = true;
  notification.hasActionButton = true;
  notification.responsePlaceholder = @"Reply...";

  notification.title = [NSString stringWithCString:std::get<0>(data).c_str()
      encoding:NSUTF8StringEncoding];
  notification.subtitle = [NSString stringWithCString:std::get<1>(data).c_str()
      encoding:NSUTF8StringEncoding];
  notification.identifier = [NSString stringWithCString:std::get<2>(data).c_str()
      encoding:NSUTF8StringEncoding];
  [[NSUserNotificationCenter defaultUserNotificationCenter] scheduleNotification:notification];
}

//------------------------------------------------------------------------------------//

@end

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
// EOF
//------------------------------------------------------------------------------------//
