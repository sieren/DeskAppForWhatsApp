#!/bin/bash

./clean.sh
~/Qt/5.5/clang_64/bin/qmake .
make
~/Qt/5.5/clang_64/bin/macdeployqt DeskAppForWhatsApp.app -dmg -verbose=2 
