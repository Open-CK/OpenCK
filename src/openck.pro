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

# C++11/14 Support
CONFIG += c++14


SOURCES += \
    main.cpp \
    version.cpp \
    ui/mainwindow.cpp \
    ui/datawindow.cpp \
    data/form.cpp \
    data/tes4form.cpp \
    io/parser.cpp \
    ui/renderwindow.cpp \
    models/filemodel.cpp \
    models/formmodel.cpp \
    io/formfactory.cpp \
    data/gamesettingform.cpp \
    data/rgbform.cpp \
    data/texturesetform.cpp \
    data/globalvariableform.cpp \
    data/classform.cpp

HEADERS += \
    version.h \
    ui/mainwindow.h \
    ui/datawindow.h \
    data/form.h \
    data/tes4form.h \
    io/parser.h \
    ui/renderwindow.h \
    models/filemodel.h \
    models/formmodel.h \
    io/formfactory.h \
    data/gamesettingform.h \
    data/rgbform.h \
    io/reader.h \
    data/texturesetform.h \
    data/subrecords/objectboundsfield.h \
    data/globalvariableform.h \
    data/classform.h \
    data/formcomponents.h

FORMS += \
    ui/mainwindow.ui \
    ui/datawindow.ui \
    ui/renderwindow.ui \

RESOURCES += \
    ../res/resources.qrc

INCLUDEPATH += \
    ui \
    io \
    data \
    data/subrecords \
    models

###############################
## FUNCTIONS
###############################

include(openck.pri)

###############################
## MACROS
###############################

# OpenCK Version
VER = $$getVersion()
# OpenCK Revision
REVISION = $$getRevision()

# OPENCK_VERSION macro
DEFINES += OPENCK_VERSION=\\\"$${VER}\\\"

# OPENCK_REVISION macro
!isEmpty(REVISION) {
    DEFINES += OPENCK_REVISION=\\\"$${REVISION}\\\"
}
