QT -= gui
QT += dbus
win32:CONFIG += console

SOURCES += src/main.cpp
SOURCES += src/Firewall.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/dbus/listnames
INSTALLS += target
