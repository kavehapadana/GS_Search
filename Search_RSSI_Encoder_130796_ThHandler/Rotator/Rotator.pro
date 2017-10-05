#-------------------------------------------------
#
# Project created by QtCreator 2013-05-31T10:27:01
#
#-------------------------------------------------

QT       += core gui serialport network webkit
CONFIG   += serialport

TARGET = SerialPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SGP4/sgp4unit.cpp \
    SGP4/sgp4io.cpp \
    SGP4/sgp4ext.cpp \
    transformmatrix.cpp \
    tleconversion.cpp \
    matrix_algebra.cpp \
    qcustomplot.cpp \
    console.cpp \
    rotatorwidget.cpp \
    dopplerentity.cpp


HEADERS  += mainwindow.h \
    SGP4/sgp4unit.h \
    SGP4/sgp4io.h \
    SGP4/sgp4ext.h \
    transformmatrix.h \
    tleconversion.h \
    matrix_algebra.h \
    qcustomplot.h \
    console.h \
    rotatorwidget.h \
    dopplerentity.h


FORMS    += \
    mainwindow.ui \
    rotatorwidget.ui
