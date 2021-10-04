######################################################################
# Automatically generated by qmake (3.1) Sun Oct 3 22:47:04 2021
######################################################################

TEMPLATE = app
TARGET = vfds
INCLUDEPATH += .

QT += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/BackgroundData.h \
           src/CTReader.h \
#           src/Filter.h \
           src/Fracture.h \
           src/ImageDataClass.h \
           src/ImageProcessor.h \
#           src/mainwindow.h \
           src/PartData.h \
           src/Split.h \
           src/Voxel.h \
           test/catch.hpp
SOURCES += src/BackgroundData.cpp \
           src/CTReader.cpp \
           src/Driver.cpp \
#           src/Filter.cpp \
           src/Fracture.cpp \
           src/ImageDataClass.cpp \
           src/ImageProcessor.cpp \
#           src/main.cpp \
#           src/mainwindow.cpp \
#           src/misc.cpp \
           src/PartData.cpp \
           src/Split.cpp \
           src/Voxel.cpp \
#           test/speedTestDriver.cpp \
#           test/SplitMergeTesting.cpp \
#           test/unit_test.cpp
            src/Filter.cpp
