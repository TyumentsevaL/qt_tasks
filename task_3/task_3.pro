DESTDIR = $$PWD/../build

SOURCES += \
        abstractdirectorystrategy.cpp \
        abstractstatholder.cpp \
        groupfilestrategy.cpp \
        listfilestrategy.cpp \
        main.cpp

HEADERS += \
    abstractdirectorystrategy.h \
    abstractstatholder.h \
    groupfilestrategy.h \
    listfilestrategy.h

BUILD_MODE = "GUI"

equals(BUILD_MODE, "GUI") {
    QT += core gui widgets charts

    CONFIG += c++11
    CONFIG -= console

    DEFINES += GUI_VERSION

    SOURCES += \
        directorystatsmainwindow.cpp \
        filestatmodel.cpp \
        chartupdater.cpp

    HEADERS += \
        directorystatsmainwindow.h \
        filestatmodel.h \
        chartupdater.h

    FORMS += \
        directorystatsmainwindow.ui
} else {
    QT -= gui

    CONFIG += c++11 console
    CONFIG -= app_bundle
}
