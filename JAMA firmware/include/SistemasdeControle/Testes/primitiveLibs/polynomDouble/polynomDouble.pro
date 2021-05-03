#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T16:02:35
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_polynomdoubletest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_polynomdoubletest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../headers/primitiveLibs/LinAlg/identifiers.h \
    ../../../headers/primitiveLibs/LinAlg/linalg.h \
    ../../../headers/primitiveLibs/LinAlg/matrix.h \
    ../../../headers/primitiveLibs/polynom.h \
    ../../../src/primitiveLibs/LinAlg/linalg.hpp \
    ../../../src/primitiveLibs/LinAlg/matrix.hpp \
    ../../../src/primitiveLibs/polynom.hpp
