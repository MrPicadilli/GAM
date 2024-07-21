#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T10:55:17
#
#-------------------------------------------------
QT += core gui opengl openglwidgets
#QT       += core gui opengl
#UpgradeQt6: QT += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mesh_Computational_Geometry
TEMPLATE = app

SOURCES += main.cpp\
    geometricworld.cpp \
        mainwindow.cpp \
    gldisplaywidget.cpp \
    mesh.cpp

HEADERS  += mainwindow.h \
    geometricworld.h \
    gldisplaywidget.h \
    mesh.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\Users\dietf\boost_1_82_0\boost_1_82_0

#---- Comment the following line on MacOS
#---- Uncomment it on Windows and Linux
#LIBS = -lGLU

#---- Uncomment the following line on Windows
#---- Comment it on Linux and MacOS
LIBS += -lglu32
LIBS += -lOpengl32

