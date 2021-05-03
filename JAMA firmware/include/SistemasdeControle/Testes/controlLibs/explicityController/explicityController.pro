QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_explicitycontroller.cpp

HEADERS += \
    ../../../headers/controlLibs/EGPC.h \
    ../../../headers/controlLibs/explicityController.h \
    ../../../headers/controlLibs/modelpredictivecontrol.h \
    ../../../headers/controlLibs/mp_pi.h \
    ../../../headers/controlLibs/mp_pid.h \
    ../../../headers/controlLibs/mp_state_feedback_controller.h \
    ../../../headers/controlLibs/pid.h \
    ../../../headers/controlLibs/pidTuning.h \
    ../../../headers/modelLibs/arx.h \
    ../../../headers/modelLibs/polynomial.h \
    ../../../src/controlLibs/EGPC.hpp \
    ../../../src/controlLibs/explicityController.hpp \
    ../../../src/controlLibs/modelpredictivecontrol.hpp \
    ../../../src/controlLibs/mp_pi.hpp \
    ../../../src/controlLibs/mp_pid.hpp \
    ../../../src/controlLibs/mp_state_feedback_controller.hpp \
    ../../../src/controlLibs/pid.hpp \
    ../../../src/controlLibs/pidTuning.hpp \
    ../../../src/modelLibs/arx.hpp \
    ../../../src/modelLibs/polynomial.hpp
