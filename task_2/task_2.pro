QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = $$PWD/../build

SOURCES += \
        classunit.cpp \
        main.cpp \
        methodunit.cpp \
        unit.cpp

HEADERS += \
    classunit.h \
    methodunit.h \
    unit.h
