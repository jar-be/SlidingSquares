CONFIG -= qt

TEMPLATE = lib
DEFINES += SLIDINGSQUARESLIB_LIBRARY

CONFIG += c++17

SOURCES += \
    cboard.cpp \
    crandomshuffler.cpp \
    crandshufflerwithmemory.cpp \
    cshuffler.cpp \
    csquare.cpp \
    slidingsquareslib.cpp

HEADERS += \
    SlidingSquaresLib_global.h \
    cboard.h \
    crandomshuffler.h \
    crandshufflerwithmemory.h \
    cshuffler.h \
    csquare.h \
    slidingsquareslib.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
