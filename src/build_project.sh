#!/bin/bash

./clean.sh
cp -rf ./lib/Sparkle.framework ~/Library/Frameworks
~/Qt/5.5/clang_64/bin/qmake .
make
~/Qt/5.5/clang_64/bin/macdeployqt DeskAppForWhatsApp.app -verbose=2
cp -Rf ./lib/Sparkle.framework DeskAppForWhatsApp.app/Contents/Frameworks
~/Qt/5.5/clang_64/bin/macdeployqt DeskAppForWhatsApp.app -dmg -verbose=2 
