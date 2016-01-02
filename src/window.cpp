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

#include "window.h"
#include "utilities.hpp"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QtGui>

#include <QAction>
#include <QCheckBox>
#include <QApplication>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QSharedPointer>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <map>


//! Layout
#define maximumWidth 400
static const std::list<std::string> kIconSet(
  {":/images/deskappGrBlue.png",
  ":/images/deskappWhGrey.png"});
//! [0]
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
Window::Window()
  : mSettings("sieren", "DeskApp")
{
    loadSettings();
    createSettingsGroupBox();

    createActions();
    createTrayIcon();

    mpSettingsTabsWidget = new QTabWidget;
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    settingsLayout->setAlignment(Qt::AlignTop);
    QWidget *settingsPageWidget = new QWidget;
    settingsLayout->addWidget(mpAppearanceGroupBox);
    settingsPageWidget->setLayout(settingsLayout);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mpSettingsTabsWidget->addTab(settingsPageWidget, "Main");
    mainLayout->addWidget(mpSettingsTabsWidget);
    setLayout(mainLayout);
    setIcon(0);
    mpTrayIcon->show();
    #ifdef Q_OS_MAC
      this->setWindowIcon(QIcon(":/images/DeskApp.icns"));
    #endif
    setWindowTitle(tr("DeskApp For WhatsApp"));
    resize(maximumWidth / devicePixelRatio(), 150);
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    using namespace std::placeholders;
    mpWhatsAppView = new WhatsAppView(
      std::bind(&Window::showMessage, this, _1),
      std::bind(&Window::setUnreadMessages, this, _1));
  
    showWebView();
}


//------------------------------------------------------------------------------------//

void Window::setVisible(bool visible)
{
  QDialog::setVisible(visible);
  mSystemUtility.showDockIcon(visible);
  raise();
}


//------------------------------------------------------------------------------------//

void Window::closeEvent(QCloseEvent *event)
{
    if (mpTrayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
  mSystemUtility.showDockIcon(false);
  saveSettings();
}


//------------------------------------------------------------------------------------//

void Window::setIcon(int index)
{
  QIcon icon;
  std::string iconUrl = mIconMonochrome ?
    kIconSet.back() : kIconSet.front();
  switch(index)
  {
    case 0:
      icon = QIcon(iconUrl.c_str());
      break;
    case 1:
      icon = QIcon(iconUrl.c_str());
      break;
    default:
      icon = QIcon(iconUrl.c_str());
      break;
  }
  mpTrayIcon->setIcon(icon);
  setWindowIcon(icon);

  mpTrayIcon->setToolTip("DeskApp For WhatsApp");
}


//------------------------------------------------------------------------------------//

void Window::setUnreadMessages(int msgs)
{
  setIcon(0); // reset to default
  QPixmap pix = mpTrayIcon->icon().pixmap(744,744);
  QFont font = QApplication::font();
  font.setPointSize(mSystemUtility.getTrayFontPointSize());
  font.setBold(true);
  QPainter *painter = new QPainter(&pix);
  painter->setFont(font);
  painter->setPen(Qt::white);
  painter->drawText(pix.rect(), Qt::AlignCenter, std::to_string(msgs).c_str());
  painter->end();
  mpTrayIcon->setIcon(QIcon(pix));
  setWindowIcon(QIcon(pix));
}


//------------------------------------------------------------------------------------//

void Window::monoChromeIconChanged(int state)
{
  mIconMonochrome = state == 2 ? true : false;
  mSettings.setValue("monochromeIcon", mIconMonochrome);
  setIcon(0);
  setUnreadMessages(mpWhatsAppView->getLastUnreadMessageCount());
}


//------------------------------------------------------------------------------------//

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason)
  {
  case QSystemTrayIcon::Trigger:
  case QSystemTrayIcon::DoubleClick:
      break;
  case QSystemTrayIcon::MiddleClick:
      break;
  default:
      ;
  }
}


//------------------------------------------------------------------------------------//

void Window::showWebView()
{
  mpWhatsAppView->show();
  mpWhatsAppView->raise();
}


//------------------------------------------------------------------------------------//

void Window::showMessage(NotificationData msg)
{
  if (mNotificationsEnabled)
  {
     mSystemUtility.showMessage(mpTrayIcon, msg, std::bind(
       &WhatsAppView::sendReplyMessage,
       mpWhatsAppView,
       std::placeholders::_1));
  }
}


//------------------------------------------------------------------------------------//

void Window::messageClicked()
{
  QDialog::setVisible(true);
  raise();
}


//------------------------------------------------------------------------------------//

void Window::createSettingsGroupBox()
{
  //
  // APPEARANCE BOX
  //

  mpAppearanceGroupBox = new QGroupBox(tr("Appearance"));
  mpMonochromeIconBox = new QCheckBox("Monochrome Icon");
  mpMonochromeIconBox->setChecked(mIconMonochrome);
  connect(mpMonochromeIconBox, SIGNAL(stateChanged(int)), this,
     SLOT(monoChromeIconChanged(int)));
  mpNotificationsIconBox = new QCheckBox("Notifications");
  mpNotificationsIconBox->setChecked(mNotificationsEnabled);
  connect(mpNotificationsIconBox, SIGNAL(stateChanged(int)), this,
    SLOT(notificationCheckBoxChanged(int)));

  QGridLayout *appearanceLayout = new QGridLayout;
  appearanceLayout->addWidget(mpMonochromeIconBox, 0, 0);
  appearanceLayout->addWidget(mpNotificationsIconBox, 1, 0);
  mpAppearanceGroupBox->setLayout(appearanceLayout);
  mpAppearanceGroupBox->setMinimumWidth(400);
  mpAppearanceGroupBox->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}


//------------------------------------------------------------------------------------//

void Window::createActions()
{
  mpShowWebViewAction = new QAction(tr("Open WhatsApp"), this);
  connect(mpShowWebViewAction, SIGNAL(triggered()), this, SLOT(showWebView()));

  mpPreferencesAction = new QAction(tr("Preferences"), this);
  connect(mpPreferencesAction, SIGNAL(triggered()), this, SLOT(showNormal()));
  connect(mpPreferencesAction, SIGNAL(closeEvent()), this, SLOT(closePrefs()));

  mpShowGitHubAction = new QAction(tr("Help"), this);
  connect(mpShowGitHubAction, SIGNAL(triggered()), this, SLOT(showGitPage()));

  mpQuitAction = new QAction(tr("&Quit"), this);
  connect(mpQuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


//------------------------------------------------------------------------------------//

void Window::createTrayIcon()
{
  if (mpTrayIconMenu == nullptr)
  {
    mpTrayIconMenu = new QMenu(this);
  }
  mpTrayIconMenu->addSeparator();
  mpTrayIconMenu->addAction(mpShowWebViewAction);
  mpTrayIconMenu->addAction(mpPreferencesAction);
  mpTrayIconMenu->addSeparator();
  mpTrayIconMenu->addAction(mpShowGitHubAction);
  mpTrayIconMenu->addSeparator();
  mpTrayIconMenu->addAction(mpQuitAction);
  if (mpTrayIcon == nullptr)
  {
    mpTrayIcon = new QSystemTrayIcon(this);
  }
  mpTrayIcon->setContextMenu(mpTrayIconMenu);
}


//------------------------------------------------------------------------------------//

void Window::saveSettings()
{
  mSettings.setValue("notificationsEnabled", mNotificationsEnabled);
}


//------------------------------------------------------------------------------------//

void Window::loadSettings()
{
  mNotificationsEnabled = mSettings.value("notificationsEnabled").toBool();
}


//------------------------------------------------------------------------------------//

void Window::createDefaultSettings()
{
}


//------------------------------------------------------------------------------------//

void Window::notificationCheckBoxChanged(int state)
{
    mNotificationsEnabled = state ? true : false;
    saveSettings();
}


//------------------------------------------------------------------------------------//

void Window::showGitPage()
{
  QString link = "http://www.github.com/sieren/DeskAppForWhatsApp";
  QDesktopServices::openUrl(QUrl(link));
}


//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
// EOF
//------------------------------------------------------------------------------------//

#endif
