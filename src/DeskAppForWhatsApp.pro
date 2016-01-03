HEADERS       = window.h \
                platforms/windows/winUtils.hpp \
                platforms/linux/posixUtils.hpp \
                platforms.hpp \
                qwhatspageview.h \
                whatsappview.h \
                utilities.hpp \
                platforms/baseutils.h \
                platforms/darwin/macUtils.h
SOURCES       = main.cpp \
                window.cpp \
                qwhatspageview.cpp \
               whatsappview.cpp
RESOURCES     = \
                deskapp.qrc

QT += widgets
QT += network
QT += webenginewidgets
QT += webchannel

# install
target.path = binary/
INSTALLS += target
CONFIG += c++11
macx {
QMAKE_INFO_PLIST = Info.plist
QMAKE_LFLAGS += -F ~/Library/Frameworks
LIBS += -framework ApplicationServices
LIBS += -framework AppKit
LIBS += -framework Foundation
LIBS += -framework Sparkle
QMAKE_MAC_SDK = macosx10.11
OBJECTIVE_SOURCES += \
    platforms/darwin/macUtils.mm
}
#QMAKE_CXXFLAGS += /wd4996
ICON = DeskApp.icns
macx {
APP_BINARY_FILES.files = Info.plist
APP_BINARY_FILES.path = Contents/Resources
QMAKE_BUNDLE_DATA += APP_BINARY_FILES
}
