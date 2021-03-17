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

BUILD_MODE = "GUI"

equals(BUILD_MODE, "GUI") {
    QT += core gui widgets

    CONFIG += c++11
    CONFIG -= console

    DEFINES += GUI_VERSION

    SOURCES += \
        directorystatsmainwindow.cpp

    HEADERS += \
        directorystatsmainwindow.h

    FORMS += \
        directorystatsmainwindow.ui
} else {
    QT -= gui

    CONFIG += c++11 console
    CONFIG -= app_bundle
}
