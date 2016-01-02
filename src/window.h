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

#ifndef WINDOW_H
#define WINDOW_H

#include "platforms.hpp"
#include "qwhatspageview.h"
#include "whatsappview.h"
#include "utilities.hpp"
#include <QSystemTrayIcon>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>
#include <QProcess>
#include <QFileDialog>
#include <QTabWidget>
#include <QWebChannel>
#include <QMovie>
#include <memory>

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

//! [0]
class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void showMessage(NotificationData msg);
    void setUnreadMessages(int msgs);
  
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showWebView();
    void messageClicked();
    void monoChromeIconChanged(int state);
    void showGitPage();
    void notificationCheckBoxChanged(int state);

private:
    void createSettingsGroupBox();
    void createActions();
    void createTrayIcon();
    void saveSettings();
    void loadSettings();
    void createDefaultSettings();

    QString loadJSFile(QString fileName);

    QTabWidget *mpSettingsTabsWidget;
    QGroupBox *mpSettingsGroupBox;

    QGroupBox *mpAppearanceGroupBox;
    QCheckBox *mpMonochromeIconBox;
    QCheckBox *mpNotificationsIconBox;

    QAction *mpShowWebViewAction;
    QAction *mpPreferencesAction;
    QAction *mpShowGitHubAction;
    QAction *mpQuitAction;

    QSystemTrayIcon *mpTrayIcon = nullptr;
    QMenu *mpTrayIconMenu = nullptr;
    QSettings mSettings;

    deskapp::sysutils::SystemUtility mSystemUtility;
    WhatsAppView *mpWhatsAppView;

    bool hasInjectedJS = false;
    bool mIconMonochrome;
    bool mNotificationsEnabled;
    bool mShouldAnimateIcon;
    int mLastConnectionState;

  };
//! [0]

#endif // QT_NO_SYSTEMTRAYICON

#endif
