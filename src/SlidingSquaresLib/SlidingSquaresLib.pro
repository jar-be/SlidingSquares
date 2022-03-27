CONFIG -= qt

TEMPLATE = lib
DEFINES += SLIDINGSQUARESLIB_LIBRARY

CONFIG += c++17

SOURCES += \
    slidingsquareslib.cpp

HEADERS += \
    SlidingSquaresLib_global.h \
    slidingsquareslib.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
