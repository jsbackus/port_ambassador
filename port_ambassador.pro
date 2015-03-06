QT -= gui
QT += dbus
win32:CONFIG += console

HEADERS += src/Firewall.h
HEADERS += src/Firewall_debug.h
HEADERS += src/ConsoleLogger.h

SOURCES += src/main.cpp
SOURCES += src/Firewall.cpp
SOURCES += src/Firewall_debug.cpp
SOURCES += src/ConsoleLogger.cpp

//DBUS_INTERFACES += dbus_interfaces/org.fedoraproject.FirewallD1.xml

//unix:DESTDIR	= ./bin
unix:OBJECTS_DIR = ./compiled_objects
unix:MOC_DIR = ./compiled_objects
//unix:LIBS	+= -lGL -lGLU -lX11 -lXmu -lXi -lm

TARGET		= port_ambassador
