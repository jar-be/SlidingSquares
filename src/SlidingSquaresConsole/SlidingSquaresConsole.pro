TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SlidingSquaresLib/release/ -lSlidingSquaresLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SlidingSquaresLib/debug/ -lSlidingSquaresLib
else:unix:!macx: LIBS += -L$$OUT_PWD/../SlidingSquaresLib/ -lSlidingSquaresLib

INCLUDEPATH += $$PWD/../SlidingSquaresLib
DEPENDPATH += $$PWD/../SlidingSquaresLib
