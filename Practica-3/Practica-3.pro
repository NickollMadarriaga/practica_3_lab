TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Encriptacion.cpp \
        LZ78.cpp \
        RLE.cpp \
        main.cpp

HEADERS += \
    ENCRIPTACIÓN.h \
    Encriptacion.h \
    LZ78.h \
    RLE.h
