CONFIG -= qt

TEMPLATE = lib
DEFINES += SLIDINGSQUARESLIB_LIBRARY

CONFIG += c++17

SOURCES += \
    cboard.cpp \
    cduration.cpp \
    cgame.cpp \
    cgamestats.cpp \
    crandomshuffler.cpp \
    crandshufflerwithmemory.cpp \
    cshuffler.cpp \
    csquare.cpp \
    cstopwatch.cpp \
    slidingsquareslib.cpp

HEADERS += \
    SlidingSquaresLib_global.h \
    cboard.h \
    cduration.h \
    cgame.h \
    cgamestats.h \
    crandomshuffler.h \
    crandshufflerwithmemory.h \
    cshuffler.h \
    csquare.h \
    cstopwatch.h \
    slidingsquareslib.h \
    date/date.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
