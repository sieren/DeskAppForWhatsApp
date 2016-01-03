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

#ifndef utilities_h
#define utilities_h
#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <functional>
#include <tuple>
#include <QFile>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QTextStream>

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

static const std::string kWhatsAppUrl = "https://web.whatsapp.com";
static const std::string kUserAgent = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) \
  AppleWebKit/600.7.12 (KHTML, like Gecko) Version/8.0.7 Safari/600.7.12";
static const std::string kWebChannelPath = ":/js/qwebchannel.js";
static const std::string kjQueryPath = ":/js/jquery.js";
static const std::string kBindingsPath = ":/js/bindings.js";
static const std::string kinjectJSPath = ":/js/inject.js";

// Sender, Message, Identifier
using NotificationData = std::tuple<std::string, std::string, std::string>;
using NotificationCallback = std::function<void(NotificationData)>;

// Message, Identifier
using ReplyData = std::tuple<std::string, std::string>;
using ReplyCallback = std::function<void(ReplyData)>;

// Number of unread messages
using UnreadMessagesCallback = std::function<void(int)>;

// Auto Updater URLs
static const std::string kMacAppCastUrl =
    "https://raw.githubusercontent.com/sieren/DeskAppForWhatsApp/master/AppCast.xml";
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

namespace deskapp
{
namespace utilities
{

inline QString loadJSFile(QString fileName)
{
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly |
                QFile::Text))
  {
    qDebug() << " Could not open the file for reading" << fileName;
    return QString("");
  }

  QTextStream in(&file);
  QString myText = in.readAll();

  file.close();
  return myText;
}

} // utilities
} // deskapp
#endif /* utilities_h */
