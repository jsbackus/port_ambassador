QT -= gui
QT += dbus
win32:CONFIG += console

HEADERS += src/Firewall.h

SOURCES += src/main.cpp
SOURCES += src/Firewall.cpp

//unix:DESTDIR	= ./bin
unix:OBJECTS_DIR = ./compiled_objects
unix:MOC_DIR = ./compiled_objects
//unix:LIBS	+= -lGL -lGLU -lX11 -lXmu -lXi -lm

TARGET		= firewalld_client
