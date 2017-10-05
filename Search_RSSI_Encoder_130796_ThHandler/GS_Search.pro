#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T11:53:52
#
#-------------------------------------------------
CONFIG += widgets serialport
QT       += core gui serialport

TARGET = GS_Search
TEMPLATE = app

TEMPLATE = app

DESTDIR = bin
#UI_DIR = ui
QMAKE_CXXFLAGS += -std=c++0x
CONFIG(debug, debug|release)
{
        TARGET = GS_Search
        OBJECTS_DIR = debug
        MOC_DIR = debug
}

CONFIG(release, debug|release)
{
        TARGET = GS_Search
        OBJECTS_DIR = release
        MOC_DIR = release
}

SOURCES += src/qcustomplot.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/hled.cpp \
    src/Worker.cpp \
    src/CustomPlotZoom.cpp \
    src/Worker_Serial.cpp \
    Rotator/tleconversion.cpp \
    Rotator/transformmatrix.cpp \
    Rotator/matrix_algebra.cpp \
    Rotator/SGP4/sgp4unit.cpp \
    Rotator/SGP4/sgp4io.cpp \
    Rotator/SGP4/sgp4ext.cpp

HEADERS  += inc/qcustomplot.h \
    inc/mainwindow.h \
    inc/hled.h \
    inc/serial_message.h \
    inc/Worker.h \
    inc/CustomPlotZoom.h \
    inc/Worker_Serial.h \
    inc/serial_message_tx.h \
    Rotator/tleconversion.h \
    Rotator/matrix_algebra.h \
    Rotator/transformmatrix.h \
    Rotator/SGP4/sgp4unit.h \
    Rotator/SGP4/sgp4io.h \
    Rotator/SGP4/sgp4ext.h


FORMS    += mainwindow.ui
INCLUDEPATH += inc/
#INCLUDEPATH += $$PWD/

OTHER_FILES += \
    Reminder.txt \
    Res/ajax-loader.gif

RESOURCES += \
    Resource.qrc
