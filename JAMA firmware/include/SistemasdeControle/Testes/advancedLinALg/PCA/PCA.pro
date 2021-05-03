QT += testlib
QT += gui
QT += widgets
QT += printsupport

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += C:/gurobi901/win64
INCLUDEPATH += C:/gurobi901/win64/include
INCLUDEPATH += C:/gurobi901/win64/src/cpp
INCLUDEPATH += C:/gurobi901/win64/bin
INCLUDEPATH += D:/Projetos/git/

LIBS += -L C:/gurobi901/win64/lib -lgurobi_c++mdd2019 -lgurobi_c++mtd2019 -lgurobi90

TEMPLATE = app

SOURCES +=  tst_pca.cpp \
    ../../../headers/graphicLibs/QCustomPlot/qcustomplot.cpp \
    C:/gurobi901/win64/src/cpp/Batch.cpp \
    C:/gurobi901/win64/src/cpp/Callback.cpp \
    C:/gurobi901/win64/src/cpp/Column.cpp \
    C:/gurobi901/win64/src/cpp/Constr.cpp \
    C:/gurobi901/win64/src/cpp/Env.cpp \
    C:/gurobi901/win64/src/cpp/Exception.cpp \
    C:/gurobi901/win64/src/cpp/GenConstr.cpp \
    C:/gurobi901/win64/src/cpp/LinExpr.cpp \
    C:/gurobi901/win64/src/cpp/Model.cpp \
    C:/gurobi901/win64/src/cpp/QConstr.cpp \
    C:/gurobi901/win64/src/cpp/QuadExpr.cpp \
    C:/gurobi901/win64/src/cpp/SOS.cpp \
    C:/gurobi901/win64/src/cpp/TempConstr.cpp \
    C:/gurobi901/win64/src/cpp/Var.cpp \
    C:/gurobi901/win64/src/cpp/attrprivate.cpp


HEADERS += \
    ../../../headers/advancedLinALg/PCA.h \
    ../../../headers/graphicLibs/QCustomPlot/qcustomplot.h \
    ../../../headers/graphicLibs/plot.h \
    ../../../headers/modelLibs/arx.h \
    ../../../headers/modelLibs/conversions.h \
    ../../../headers/modelLibs/model.h \
    ../../../headers/modelLibs/statespace.h \
    ../../../headers/modelLibs/transferfunction.h \
    ../../../headers/primitiveLibs/LinAlg/linalg.h \
    ../../../headers/primitiveLibs/LinAlg/matrix.h \
    ../../../headers/primitiveLibs/polynom.h \
    ../../../headers/restrictedOptimization/gurobioptimization.h\
    ../../../src/advancedLinALg/PCA.hpp \
    ../../../src/modelLibs/arx.hpp \
    ../../../src/modelLibs/conversions.hpp \
    ../../../src/modelLibs/model.hpp \
    ../../../src/modelLibs/statespace.hpp \
    ../../../src/modelLibs/transferfunction.hpp \
    ../../../src/primitiveLibs/LinAlg/linalg.hpp \
    ../../../src/primitiveLibs/LinAlg/matrix.hpp \
    ../../../src/primitiveLibs/polynom.hpp \
    ../../../src/restrictedOptimization/gurobioptimization.hpp \
    C:/gurobi901/win64/include/gurobi_c++.h \
    C:/gurobi901/win64/include/gurobi_c.h \
    C:/gurobi901/win64/src/cpp/Batch.h \
    C:/gurobi901/win64/src/cpp/Callback.h \
    C:/gurobi901/win64/src/cpp/Column.h \
    C:/gurobi901/win64/src/cpp/Common.h \
    C:/gurobi901/win64/src/cpp/Constr.h \
    C:/gurobi901/win64/src/cpp/Env.h \
    C:/gurobi901/win64/src/cpp/Exception.h \
    C:/gurobi901/win64/src/cpp/Expr.h \
    C:/gurobi901/win64/src/cpp/GenConstr.h \
    C:/gurobi901/win64/src/cpp/LinExpr.h \
    C:/gurobi901/win64/src/cpp/Model.h \
    C:/gurobi901/win64/src/cpp/QConstr.h \
    C:/gurobi901/win64/src/cpp/QuadExpr.h \
    C:/gurobi901/win64/src/cpp/SOS.h \
    C:/gurobi901/win64/src/cpp/TempConstr.h \
    C:/gurobi901/win64/src/cpp/Var.h \
    C:/gurobi901/win64/src/cpp/attrprivate.h \
    C:/gurobi901/win64/src/cpp/parprivate.h \
    C:/gurobi901/win64/src/cpp/public.h
