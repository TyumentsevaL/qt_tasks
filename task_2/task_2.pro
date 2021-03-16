QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = $$PWD/../build

SOURCES += \
        cpp_units.cpp \
        csharp_units.cpp \
        main.cpp \
        core_units.cpp

HEADERS += \
    cpp_units.h \
    core_units.h \
    csharp_units.h
