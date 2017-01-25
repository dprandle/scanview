TARGET = scanview
TEMPLATE = app
QT += core gui network widgets
CONFIG += debug_and_release
INCLUDEPATH += $$PWD/include
UI_DIR = $$PWD/ui
DESTDIR  = $$PWD/bin/$$ARCH

unix {
QMAKE_CXXFLAGS += -pipe -std=c++11
ARCH = x64
}

win32 {
message("Windows OS detected")
ARCH = x86
}

Release:MOC_DIR = $$PWD/build/$$ARCH/Release/moc
Release:OBJECTS_DIR = $$PWD/build/$$ARCH/Release/obj
Debug:MOC_DIR = $$PWD/build/$$ARCH/Debug/moc
Debug:OBJECTS_DIR = $$PWD/build/$$ARCH/Debug/obj

build_pass:CONFIG(debug, debug|release)
{
    TARGET = $$join(TARGET,,,d)
}

HEADERS += \
    include/scanview.h \
    include/mapview.h \
    include/preferences_dialog.h \
    include/sensor_controls.h \
    include/console_view.h

SOURCES += \
    src/scanview.cpp \
    src/mapview.cpp \
    src/main.cpp \
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
