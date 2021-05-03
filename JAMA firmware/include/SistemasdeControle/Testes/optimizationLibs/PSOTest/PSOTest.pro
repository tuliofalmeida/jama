QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_psotest.cpp

HEADERS += \
    ../../../headers/advancedModelLibs/droneModel/limbModel.h \
    ../../../headers/modelLibs/model.h \
    ../../../headers/optimizationLibs/optimization.h \
    ../../../headers/optimizationLibs/pso.h \
    ../../../headers/primitiveLibs/LinAlg/linalg.h \
    ../../../headers/primitiveLibs/LinAlg/matrix.h \
    ../../../src/advancedModelLibs/droneModel/limbModel.hpp \
    ../../../src/modelLibs/model.hpp \
    ../../../src/optimizationLibs/pso.hpp \
    ../../../src/primitiveLibs/LinAlg/linalg.hpp \
    ../../../src/primitiveLibs/LinAlg/matrix.hpp \
    testeJacobiano.h
