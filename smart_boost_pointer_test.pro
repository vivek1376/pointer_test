TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


# custom values, manually added
QMAKE_CXXFLAGS += -Og
