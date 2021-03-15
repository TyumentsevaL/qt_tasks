DESTDIR = $$PWD/../build

SOURCES += \
        filewatchermanager.cpp \
        fileinfowatcher.cpp \
        main.cpp

HEADERS += \
    filewatchermanager.h \
    fileinfowatcher.h

BUILD_MODE = "GUI"

equals(BUILD_MODE, "GUI") {
    QT += core gui widgets

    CONFIG += c++11
    CONFIG -= console

    DEFINES += GUI_VERSION

    SOURCES += \
        filewatcherwidget.cpp

    HEADERS += \
        filewatcherwidget.h

    FORMS += \
        filewatcherwidget.ui
} else {
    QT -= gui

    CONFIG += c++11 console
    CONFIG -= app_bundle
}

