/*
 *    PortAmbassador is a GUI tool for configuring a Linux firewall.
 *    (c) 2015 Jeff Backus <jeff.backus@gmail.com>
 *
 *    This file is part of PortAmbassador.
 *
 *    PortAmbassador is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    PortAmbassador is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with PortAmbassador.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    Home Page:
 *    https://github.com/jsbackus/port_ambassador
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include "Firewall.h"
#include "Firewall_debug.h"
#include "ConsoleLogger.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  if (!QDBusConnection::systemBus().isConnected()) {
    fprintf(stderr, "Cannot connect to the D-Bus system bus.\n"
	    "To start it, run:\n"
	    "\teval `dbus-launch --auto-syntax`\n");
    return 1;
  }

  Firewall wall;
  ConsoleLogger logger;
  logger.SetThreshold(10);

  // Connect Firewall's message signals to ConsoleLogger's respective slots.
  QObject::connect( &wall, SIGNAL( OnError(const QString&) ),
		    &logger, SLOT( ErrorMsg(const QString&) ) );

  QObject::connect( &wall, SIGNAL( OnWarn(const QString&) ),
		    &logger, SLOT( WarningMsg(const QString&) ) );

  QObject::connect( &wall, SIGNAL( OnDebug(const int, const QString&) ),
		    &logger, SLOT( DebugMsg(const int, const QString&) ) );

  qDebug() << "Ports:";
  foreach( PortProtoStruct val, wall.GetPorts( "public" )) {
    qDebug() << "  " << val.port << " (" << val.protocol << ")";
  }

  qDebug() << "Services:";
  //  foreach( QString val, wall.GetServices( "public" )) {
  foreach( QString val, wall.GetServices( )) {
    qDebug() << "  " << val << ":";
    DumpService( wall, val );
  }

  qDebug() << "Zones:";
  foreach( QString val, wall.GetZones() ) {
    qDebug() << "  " << val << ":";
    DumpZone( wall, val );
  }

  qDebug() << "ICMP Types:";
  foreach( QString val, wall.GetIcmpTypes() ) {
    qDebug() << "  " << val << ":";
    DumpIcmpType( wall, val );
  }

  wall.SetDefaultZone( "external" );
  
  // Enter main event loop until user hits CTRL+C
  while(1) {
    app.processEvents();
  }

  return 0;
}
