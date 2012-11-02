TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

QMAKE_LIBS += -lgomp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
