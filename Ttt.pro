#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T17:43:57
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Ttt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui



INCLUDEPATH += C:\\opencv\\build\\include

LIBS += -LC:\\opencv\\build\\lib\\Debug \
-lopencv_core2410d \
-lopencv_imgproc2410d \
-lopencv_highgui2410d \
-lopencv_ml2410d \
-lopencv_video2410d \
-lopencv_features2d2410d \
-lopencv_calib3d2410d \
-lopencv_objdetect2410d \
-lopencv_contrib2410d \
-lopencv_legacy2410d \
-lopencv_flann2410d

