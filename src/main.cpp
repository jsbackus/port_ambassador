#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include "Firewall.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  if (!QDBusConnection::systemBus().isConnected()) {
    fprintf(stderr, "Cannot connect to the D-Bus system bus.\n"
	    "To start it, run:\n"
	    "\teval `dbus-launch --auto-syntax`\n");
    return 1;
  }

  Firewall wall;

  qDebug() << "Ports:";
  foreach( PortProtoStruct val, wall.GetPorts( "public" )) {
    qDebug() << "  " << val.port << " (" << val.protocol << ")";
  }

  qDebug() << "Services:";
  //  foreach( QString val, wall.GetServices( "public" )) {
  foreach( QString val, wall.GetServices( )) {
    qDebug() << "  " << val << ":";
    wall.DumpService( val );
  }

  qDebug() << "Zones:";
  foreach( QString val, wall.GetZones() ) {
    qDebug() << "  " << val << ":";
    wall.DumpZone( val );
  }

  qDebug() << "ICMP Types:";
  foreach( QString val, wall.GetIcmpTypes() ) {
    qDebug() << "  " << val << ":";
    wall.DumpIcmpType( val );
  }

  return 0;
}
