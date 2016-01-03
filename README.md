DeskApp for WhatsApp (Unofficial)
=============
#### A Traybar Application for WhatsApp written in C++ 

![Travis CI](https://travis-ci.org/sieren/DeskAppForWhatsApp.svg?branch=master "Travis CI
Status")
[![Issues](https://img.shields.io/github/issues/sieren/DeskAppForWhatsApp.svg
"Issues")](https://github.com/sieren/DeskAppForWhatsApp/issues)
[![Downloads](https://img.shields.io/github/downloads/sieren/DeskAppForWhatsApp/total.svg "Downloads")](https://github.com/sieren/DeskAppForWhatsApp/releases)



A simple cross-platform desktop Client for WhatsApp which runs on OS X, Linux and Windows.
It makes use of the status-bar or tray-bar of the respective system so it doesn't get in
the way during every day use.
This is **NOT** an official client.
Currently supports **OS X**, **Windows** and **Linux**.

Written in C++ with Qt.

Precompiled and ready-to-install binaries are [here](https://github.com/sieren/DeskAppForWhatsApp/releases).

## Features

+ System Notifications on incoming messages.
+ Number of unread conversations in Tray Icon.
+ Optional monochrome icon for black/white themes.
+ OS X: Quick Reply functionality in notifications.

Is there a feature missing? Open an issue, send me an [email](mailto:info@s-r-n.de) or fork this project and add it yourself.


![alt text](https://raw.githubusercontent.com/sieren/DeskAppForWhatsApp/master/media/screenmac.png "Mac OSX ")
![alt text](https://raw.githubusercontent.com/sieren/DeskAppForWhatsApp/master/media/screengnome.png "Ubuntu")
![alt text](https://raw.githubusercontent.com/sieren/DeskAppForWhatsApp/master/media/screenwin.png "Windows")

## How To Use It

Launch the application and authorize with WhatsApp on your phone by scanning the QR Code.

To start DeskApp for WhatsApp at boot (OS X):

+ Go to **System Preferences** and **Users & Groups**
+ Drag DeskAppForWhatsApp into the **Login Items** list

## Note
This project does not attempt to reverse engineer the WhatsApp API or attempt to reimplement any part of the WhatsApp client's communications with the WhatsApp servers.  
  
Any communication between the user and WhatsApp servers is handled by WhatsApp Web itself; this is merely a native wrapper for WhatsApp Web, more akin to a browser than any WhatsApp software.

## Known Issues
Qt 5.5 currently does not support HiDPI properly.
Thus UI Elements may be shown too small on certain platforms (e.g. Linux) when in HiDPI
mode.
This will be fixed once this project moves on to Qt 5.6.

## Build
+ Get a recent version of Qt (5.5+)  

### Mac & Windows
+ Use either QtCreator or create an XCode or Visual Studio Project with CMake or QMake.  
```
mkdir build && cd build  
cmake ../ -G Xcode
```

### Linux
+ Get the most recent [Qt Version](http://www.qt.io/download/)
+ I advise to use `qmake` for now, as there have been a few minor problems with the cmake script.  
```
cd ./src  
qmake -config release  
make  
./DeskAppForWhatsApp
```

## License
Copyright (c), 2015 Authors of the source code of this project

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.html>.
