#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T20:55:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editor.cpp \
    editorview.cpp \
    editorscene.cpp

HEADERS  += mainwindow.h \
    editor.h \
    editorview.h \
    editorscene.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../../clientServer/assets/img/Buttons/worm.png

RESOURCES += \
    resources.qrc
