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

#include "whatsappview.h"
#include "utilities.hpp"
#include "platforms.hpp"
#include <QWebEnginePage>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>
#include <QWebEngineScript>
#include <QWebEngineProfile>
#include <QWebChannel>
#include <QRegExp>

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//


WhatsAppView::WhatsAppView(
  NotificationCallback notifyCb,
  UnreadMessagesCallback unreadCb)
 : mNotificationCallback(notifyCb)
 , mUnreadMessagesCallback(unreadCb)
{
  initWebView();
}


//------------------------------------------------------------------------------------//

WhatsAppView::WhatsAppView()
{
}


//------------------------------------------------------------------------------------//

void WhatsAppView::initWebView()
{
  QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
  profile->setHttpUserAgent(kUserAgent.c_str());
  profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
  newWeb = new QWhatsAppPageView(profile);

  webCommChannel = new QWebChannel();
  webCommChannel->registerObject(QStringLiteral("foo"), this);

  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(hasFinishedLoading(bool)));
  connect(this, SIGNAL(titleChanged(QString)), this, SLOT(updateUnreadMessages()));
  QWebEngineSettings* settings = newWeb->settings();
  settings->setAttribute(QWebEngineSettings::WebAttribute::JavascriptEnabled, true);
  settings->setAttribute(QWebEngineSettings::WebAttribute::AutoLoadImages,true);
  settings->setAttribute(QWebEngineSettings::WebAttribute::LocalContentCanAccessRemoteUrls, true);
  newWeb->load((QUrl(kWhatsAppUrl.c_str())));
  setPage(newWeb);
}


//------------------------------------------------------------------------------------//

void WhatsAppView::sendReplyMessage(ReplyData msg)
{
  std::cout << "GOT REPLY" << std::endl;
  QString openChatJs = QString("openChat(\"%1\")").arg(std::get<1>(msg).c_str());
  QString sendMessageJs = QString(
    "dispatch(document.querySelector('div.input'), 'textInput', '%1')").arg(
      std::get<0>(msg).c_str());
  
  newWeb->runJavaScript(openChatJs);
  newWeb->runJavaScript(sendMessageJs);
  newWeb->runJavaScript("triggerClick();");
}


//------------------------------------------------------------------------------------//

void WhatsAppView::showNotification(QString sender, QString body, QString id,
  QString imageUrl)
{
  UNUSED(imageUrl);
  NotificationData notification =
    std::make_tuple(sender.toStdString(), body.toUtf8().toStdString(), id.toStdString());
  mNotificationCallback(notification);
}


//------------------------------------------------------------------------------------//

void WhatsAppView::hasFinishedLoading(bool loaded)
{
    if(loaded)
    {
            using namespace deskapp::utilities;
            newWeb->setWebChannel(webCommChannel);
            QString webChannelJS = loadJSFile(kWebChannelPath.c_str());
            QString injectJS = loadJSFile(kinjectJSPath.c_str());
            QString jqueryJS = loadJSFile(kjQueryPath.c_str());
            newWeb->runJavaScript(jqueryJS, [](const QVariant &result){ qDebug() << result; });
            newWeb->runJavaScript(webChannelJS, [](const QVariant &result){ qDebug() << result; });
            newWeb->runJavaScript(injectJS, [](const QVariant &result){ qDebug() << result; });
    }
  updateUnreadMessages();
}


//------------------------------------------------------------------------------------//

void WhatsAppView::closeEvent(QCloseEvent *event)
{
  QWebEngineView::closeEvent(event);
  deskapp::sysutils::SystemUtility().showDockIcon(false);
}


//------------------------------------------------------------------------------------//

void WhatsAppView::show()
{
  QWebEngineView::show();
  deskapp::sysutils::SystemUtility().showDockIcon(true);
}


//------------------------------------------------------------------------------------//

void WhatsAppView::updateUnreadMessages()
{
  QRegExp numExpr("\\(([0-9]+)\\) WhatsApp Web");
  QString title = newWeb->title();
  int unreadMessages = 0;
  if (title != "WhatsApp Web")
  {
  QStringList list;
  int pos = 0;
  while ((pos = numExpr.indexIn(title, pos)) != -1) {
       list << numExpr.cap(1);
       pos += numExpr.matchedLength();
   }
  QString result = list.join("");
  try
  {
    unreadMessages = std::stoi(result.toStdString());
  }
  catch (std::exception &e)
  {
    std::cerr << "Unable to read number of unread messages." << std::endl;
  }
  }
  mUnreadMessagesCallback(unreadMessages);
  mLastUnreadMessageCount = unreadMessages;
}


//------------------------------------------------------------------------------------//

int WhatsAppView::getLastUnreadMessageCount()
{
  return mLastUnreadMessageCount;
}


//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
// EOF
//------------------------------------------------------------------------------------//
