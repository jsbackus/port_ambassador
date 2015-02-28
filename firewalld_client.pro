QT -= gui
QT += dbus
win32:CONFIG += console

HEADERS += src/Firewall.h
HEADERS += src/Firewall_debug.h

SOURCES += src/main.cpp
SOURCES += src/Firewall.cpp
SOURCES += src/Firewall_debug.cpp

//unix:DESTDIR	= ./bin
unix:OBJECTS_DIR = ./compiled_objects
unix:MOC_DIR = ./compiled_objects
//unix:LIBS	+= -lGL -lGLU -lX11 -lXmu -lXi -lm

TARGET		= firewalld_client
