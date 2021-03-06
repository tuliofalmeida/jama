#-------------------------------------------------
#
# Project created by QtCreator 2017-05-01T12:42:53
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_predictivetesttest
CONFIG   += console
CONFIG   -= app_bundle

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


SOURCES += tst_predictivetesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../headers/advancedModelLibs/droneModel/limbModel.h \
    ../../../headers/primitiveLibs/LinAlg/identifiers.h \
    ../../../headers/primitiveLibs/LinAlg/linalg.h \
    ../../../headers/primitiveLibs/LinAlg/matrix.h \
    ../../../headers/primitiveLibs/polynom.h \
    ../../../src/advancedModelLibs/droneModel/limbModel.hpp \
    ../../../src/primitiveLibs/LinAlg/linalg.hpp \
    ../../../src/primitiveLibs/LinAlg/matrix.hpp \
    ../../../src/primitiveLibs/polynom.hpp \
    ../../../headers/advancedApplication/datarecognition/classification.h \
    ../../../headers/advancedApplication/datarecognition/movingmask.h \
    ../../../headers/advancedControlLibs/droneControl/dronecontrol.h \
    ../../../headers/advancedLinALg/PCA.h \
    ../../../headers/advancedModelLibs/droneModel/dronemodel.h \
    ../../../headers/controlLibs/modelpredictivecontrol.h \
    ../../../headers/controlLibs/pid.h \
    ../../../headers/graphicLibs/plot.h \
    ../../../headers/modelLibs/activefunction.h \
    ../../../headers/modelLibs/armax.h \
    ../../../headers/modelLibs/arx.h \
    ../../../headers/modelLibs/conversions.h \
    ../../../headers/modelLibs/fir.h \
    ../../../headers/modelLibs/integrativemodel.h \
    ../../../headers/modelLibs/ma.h \
    ../../../headers/modelLibs/model.h \
    ../../../headers/modelLibs/neuron.h \
    ../../../headers/modelLibs/neuron.hpp \
    ../../../headers/modelLibs/nfir.h \
    ../../../headers/modelLibs/predictionmodel.h \
    ../../../headers/modelLibs/rna.h \
    ../../../headers/modelLibs/rna.hpp \
    ../../../headers/modelLibs/simfunction.h \
    ../../../headers/modelLibs/statespace.h \
    ../../../headers/modelLibs/transferfunction.h \
    ../../../headers/optimizationLibs/leastsquare.h \
    ../../../headers/optimizationLibs/optimization.h \
    ../../../headers/optimizationLibs/pso.h \
    ../../../headers/optimizationLibs/recursiveleastsquare.h \
    ../../../headers/optimizationLibs/relay.h \
    ../../../headers/primitiveLibs/LinAlg/matrixrestriction.h \
    ../../../headers/primitiveLibs/LinAlg/matrixrestriction.hpp \
    ../../../headers/restrictedOptimization/activeset.h \
    ../../../headers/restrictedOptimization/activeset.hpp \
    ../../../headers/restrictedOptimization/generalisedrestrictednewton.h \
    ../../../headers/restrictedOptimization/linprog.h \
    ../../../headers/restrictedOptimization/polyhedron.h \
    ../../../headers/restrictedOptimization/polyhedron.hpp \
    ../../../headers/restrictedOptimization/quadprog.h \
    ../../../headers/restrictedOptimization/recursiveactiveset.h \
    ../../../headers/restrictedOptimization/simplex.h \
    ../../../headers/simulationLibs/sim.h \
    ../../../headers/zeroFunctionLib/bisseccao.h \
    ../../../headers/zeroFunctionLib/fzero.h \
    ../../../headers/zeroFunctionLib/newton.h \
    ../../../headers/zeroFunctionLib/secant.h \
    ../../../headers/zeroFunctionLib/steffensen.h \
    ../../../src/advancedApplication/datarecognition/classification.hpp \
    ../../../src/advancedApplication/datarecognition/movingmask.hpp \
    ../../../src/advancedControlLibs/droneControl/dronecontrol.hpp \
    ../../../src/advancedLinALg/PCA.hpp \
    ../../../src/advancedModelLibs/droneModel/dronemodel.hpp \
    ../../../src/controlLibs/modelpredictivecontrol.hpp \
    ../../../src/controlLibs/pid.hpp \
    ../../../src/modelLibs/armax.hpp \
    ../../../src/modelLibs/arx.hpp \
    ../../../src/modelLibs/conversions.hpp \
    ../../../src/modelLibs/fir.hpp \
    ../../../src/modelLibs/integrativemodel.hpp \
    ../../../src/modelLibs/ma.hpp \
    ../../../src/modelLibs/model.hpp \
    ../../../src/modelLibs/nfir.hpp \
    ../../../src/modelLibs/predictionmodel.hpp \
    ../../../src/modelLibs/simfunction.hpp \
    ../../../src/modelLibs/statespace.hpp \
    ../../../src/modelLibs/transferfunction.hpp \
    ../../../src/optimizationLibs/leastsquare.hpp \
    ../../../src/optimizationLibs/optimization.hpp \
    ../../../src/optimizationLibs/pso.hpp \
    ../../../src/optimizationLibs/recursiveleastsquare.hpp \
    ../../../src/optimizationLibs/relay.hpp \
    ../../../src/primitiveLibs/LinAlg/matrixrestriction.hpp \
    ../../../src/restrictedOptimization/activeset.hpp \
    ../../../src/restrictedOptimization/generalisedrestrictednewton.hpp \
    ../../../src/restrictedOptimization/linprog.hpp \
    ../../../src/restrictedOptimization/polyhedron.hpp \
    ../../../src/restrictedOptimization/quadprog.hpp \
    ../../../src/restrictedOptimization/recursiveactiveset.hpp \
    ../../../src/restrictedOptimization/simplex.hpp \
    ../../../src/simulationLibs/sim.hpp \
    ../../../src/zeroFunctionLib/bisseccao.hpp \
    ../../../src/zeroFunctionLib/fzero.hpp \
    ../../../src/zeroFunctionLib/newton.hpp \
    ../../../src/zeroFunctionLib/secant.hpp \
    ../../../src/zeroFunctionLib/steffensen.hpp
