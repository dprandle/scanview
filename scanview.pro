#-------------------------------------------------
#
# Project created by QtCreator 2015-07-27T16:24:02
#
#-------------------------------------------------

include(platform.pri)
TARGET = scanview
TEMPLATE = app

QT += core gui network widgets
CONFIG += debug_and_release

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/../ctrlmod/include
UI_DIR = $$PWD/ui
DESTDIR  = $$PWD/bin/$$PLATFORM

Release:MOC_DIR = $$PWD/build/$$PLATFORM/Release/moc
Release:OBJECTS_DIR = $$PWD/build/$$PLATFORM/Release/obj

Debug:MOC_DIR = $$PWD/build/$$PLATFORM/Debug/moc
Debug:OBJECTS_DIR = $$PWD/build/$$PLATFORM/Debug/obj

SOURCES += \
    $$PWD/src/*.c* \
    $$PWD/../ctrlmod/src/edrplidar_packets.cpp \

HEADERS += \
    $$PWD/include/*.h* \
    $$PWD/../ctrlmod/include/edrplidar_packets.h \

FORMS += \
    $$PWD/ui/*.ui* \

build_pass:CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
