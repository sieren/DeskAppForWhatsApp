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

#include <QApplication>
#include <QSharedMemory>
#include <QSystemSemaphore>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QMessageBox>
#include "window.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(deskapp);

    QApplication app(argc, argv);

    QSystemSemaphore sema("75ddae3a-1e79-43d5-9efa-ea7ffd67d02a", 1);
    sema.acquire();

    #ifndef Q_OS_WIN32
    // on posix systemsshared memory is not freed upon crash
    // so if there is anything left from a previous instance
    // we'll do some cleanup
    QSharedMemory nix_fix_shmem("75ddae3a-1e79-43d5-9efa-ea7ffdddd02a");
    if(nix_fix_shmem.attach())
    {
      nix_fix_shmem.detach();
    }
    #endif

    QSharedMemory shmem("75ddae3a-1e79-43d5-9efa-ea7ffdddd02a");
    bool is_running;
    if (shmem.attach())
    {
      is_running = true;
    }
    else
    {
      shmem.create(1);
      is_running = false;
    }
    sema.release();

    if(is_running)
    {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.setText("You already have this app running."
                     "\r\nOnly one instance is allowed.");
      msgBox.exec();
      return 1;
    }

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("DeskApp For WhatsApp"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    Window window;
#ifdef QT_DEBUG
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "23654");
#endif
    return app.exec();
}

#else

#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSyncthingTray is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;
    QCoreApplication::setOrganizationName("sieren");
    QCoreApplication::setOrganizationDomain("sieren.com");
    QCoreApplication::setApplicationName("QSyncthingTray");
    app.exec();
}

#endif
