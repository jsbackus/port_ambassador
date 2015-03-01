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

/*! \file Firewall_debug.cpp
 *  \brief Implementations of debug functions related to the Firewall class.
 */
#include <QtCore/QDebug>

#include "Firewall.h"

void DumpService( Firewall& wall, QString service ) {

  ServiceSettings reply = wall.GetService( service );

  qDebug() << "  Version: " << reply.version;
  qDebug() << "  Name: " << reply.name;
  qDebug() << "  Description: " << reply.description;

  qDebug() << "  Ports: ";
  foreach(PortProtoStruct proto, reply.ports) {
    qDebug() << "    " << proto.port << " -> " << proto.protocol;
  }

  qDebug() << "  Modules: ";
  foreach(QString module, reply.modules) {
    qDebug() << "    " << module;
  }

  qDebug() << "  Destinations: ";
  foreach(QString key, reply.destinations.keys() ) {
    qDebug() << "    " << reply.destinations[ key ];
  }

}

void DumpZone( Firewall& wall, QString zone ) {

  ZoneSettings reply = wall.GetZone( zone );

  qDebug() << "  Version: " << reply.version;
  qDebug() << "  Name: " << reply.name;
  qDebug() << "  Description: " << reply.description;
  qDebug() << "  Target: " << reply.target;

  qDebug() << "  Services: ";
  foreach(QString service, reply.services) {
    qDebug() << "    " << service;
  }

  qDebug() << "  Ports: ";
  foreach(PortProtoStruct proto, reply.ports) {
    qDebug() << "    " << proto.port << " -> " << proto.protocol;
  }

  qDebug() << "  ICMP Blocks: ";
  foreach(QString block, reply.icmp_blocks) {
    qDebug() << "    " << block;
  }

  qDebug() << "  Masquerade: " << reply.masquerade;

  qDebug() << "  Forwards: ";
  foreach(ForwardStruct forward, reply.forwards) {
    qDebug() << "    " << forward.port << "/" << forward.protocol << " -> " 
	     << forward.to_address << ":" << forward.to_port;
  }

  qDebug() << "  Interfaces: ";
  foreach(QString iface, reply.ifaces) {
    qDebug() << "    " << iface;
  }

  qDebug() << "  Sources: ";
  foreach(QString src, reply.sources) {
    qDebug() << "    " << src;
  }

  qDebug() << "  Rules: ";
  foreach(QString rule, reply.rules) {
    qDebug() << "    " << rule;
  }

}

void DumpIcmpType( Firewall& wall, QString icmpType ) {

  IcmpTypeSettings reply = wall.GetIcmpType( icmpType );

  qDebug() << "  Version: " << reply.version;
  qDebug() << "  Name: " << reply.name;
  qDebug() << "  Description: " << reply.description;

  qDebug() << "  Destinations: ";
  foreach(QString destination, reply.destinations) {
    qDebug() << "    " << destination;
  }
}
