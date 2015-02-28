/*! \file Implementation of debug functions related to the Firewall class.
 */
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
