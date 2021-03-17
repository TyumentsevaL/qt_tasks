QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = $$PWD/../build

SOURCES += \
        abstractdirectorystrategy.cpp \
        listfilestrategy.cpp \
        main.cpp

HEADERS += \
    abstractdirectorystrategy.h \
    listfilestrategy.h
