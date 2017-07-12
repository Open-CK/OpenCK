#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T04:40:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/datawindow.cpp \
    src/parse/parsed.cpp \
    src/parse/parser.cpp \
    src/define/recordparent.cpp \
    src/define/tes4record.cpp \
    src/define/hedrfield.cpp \
    src/define/fieldparent.cpp

HEADERS += \
    include/ui/mainwindow.h \
    include/ui/datawindow.h \
    include/parse/parser.h \
    include/parse/parsed.h \
    include/define/recordparent.h \
    include/define/tes4record.h \
    include/define/tes4record.h \
    include/define/fieldparent.h \
    src/define/hedrfield.h \
    include/define/hedrfield.h

FORMS += \
    ui/mainwindow.ui \
    ui/datawindow.ui

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += \
        include/ui \
        include/parse \
	include/define \
