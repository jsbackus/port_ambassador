/*
 *    SimpleFirewallClient is a GUI tool for configuring the a Linux firewall.
 *    (c) 2015 Jeff Backus <jeff.backus@gmail.com>
 *
 *    This file is part of SimpleFirewallClient.
 *
 *    SimpleFirewallClient is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    SimpleFirewallClient is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SimpleFirewallClient.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    Home Page:
 *    https://github.com/jsbackus/SimpleFirewallClient
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include "Firewall.h"
#include "Firewall_debug.h"

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

  return 0;
}
