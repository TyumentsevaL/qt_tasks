QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = $$PWD/../build

SOURCES += \
        filewatchermanager.cpp \
        fileinfowatcher.cpp \
        main.cpp

HEADERS += \
    filewatchermanager.h \
    fileinfowatcher.h
