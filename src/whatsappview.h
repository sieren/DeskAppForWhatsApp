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

#ifndef WHATSAPPVIEW_H
#define WHATSAPPVIEW_H

#include <functional>
#include <QObject>
#include <QWebEngineView>
#include "qwhatspageview.h"
#include "utilities.hpp"
#include <QMenu>
#include <QWebEngineView>
#include <QDialog>

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

class WhatsAppView : public QWebEngineView
{
  Q_OBJECT

public:
  WhatsAppView();
  WhatsAppView(
    NotificationCallback notifyCb,
    UnreadMessagesCallback unreadCb);

  void sendReplyMessage(ReplyData msg);
  void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
  void show();
  int getLastUnreadMessageCount();
  virtual void contextMenuEvent(QContextMenuEvent * event) override;

public slots:
  void showNotification(QString sender, QString body, QString id,
    QString imageUrl);

private slots:
  void hasFinishedLoading(bool loaded);
  void updateUnreadMessages();

private:
  void initWebView();
  void setupMenu();

  int mLastUnreadMessageCount = 0;
  QWebChannel *webCommChannel;
  QWhatsAppPageView *newWeb;
  NotificationCallback mNotificationCallback;
  UnreadMessagesCallback mUnreadMessagesCallback;

  QMenu mContextMenu;

  template<typename F, typename T, typename... TArgs>
  void addActions(F &&funct, T action, TArgs... Actions);

  template<typename F, typename T>
  void addActions(F &&funct, T action);
};

#endif // WHATSAPPVIEW_H
