TARGET = scanview
TEMPLATE = app
QT += core gui network widgets
CONFIG += debug_and_release
ARCH = x64
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/../ctrlmod/include
UI_DIR = $$PWD/ui
DESTDIR  = $$PWD/bin/$$ARCH

unix {
QMAKE_CXXFLAGS += -pipe -std=c++11
}

win32 {
message("Windows OS detected")
system(\"$$PWD/config.bat\" \"$$PWD\")
}

Release:MOC_DIR = $$PWD/build/$$ARCH/Release/moc
Release:OBJECTS_DIR = $$PWD/build/$$ARCH/Release/obj
Debug:MOC_DIR = $$PWD/build/$$ARCH/Debug/moc
Debug:OBJECTS_DIR = $$PWD/build/$$ARCH/Debug/obj

build_pass:CONFIG(debug, debug|release)
{
    TARGET = $$join(TARGET,,,d)
}

LIBS += -L$$PWD/deps/libssh/lib/$$ARCH
LIBS += -L$$PWD/deps/libssh/bin/$$ARCH
LIBS += -lssh

HEADERS += \
    include/scanview.h \
    include/mapview.h \
    ../ctrlmod/include/edrplidar_packets.h \
    include/preferences_dialog.h \
    include/sensor_controls.h \
    include/console_view.h

SOURCES += \
    src/scanview.cpp \
    src/mapview.cpp \
    src/main.cpp \
    ../ctrlmod/src/edrplidar_packets.cpp \
    src/preferences_dialog.cpp \
    src/sensor_controls.cpp \
    src/console_view.cpp

FORMS += \
    ui/scanview.ui \
    ui/preferences_dialog.ui \
    ui/sensor_controls.ui \
    ui/console_view.ui

RESOURCES += \
    scanview_icons.qrc
