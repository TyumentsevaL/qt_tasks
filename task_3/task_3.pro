QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = $$PWD/../build

SOURCES += \
        abstractdirectorystrategy.cpp \
        groupfilestrategy.cpp \
        listfilestrategy.cpp \
        main.cpp

HEADERS += \
    abstractdirectorystrategy.h \
    groupfilestrategy.h \
    listfilestrategy.h
