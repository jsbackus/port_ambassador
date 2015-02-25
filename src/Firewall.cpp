#include <QtCore/QDebug>
#include <QDBusMetaType>

#include "Firewall.h"

QDBusArgument &operator<<(QDBusArgument &argument, const PortProtoStruct &mystruct) {
  argument.beginStructure();
  argument << mystruct.port;
  argument << mystruct.protocol;
  argument.endStructure();
  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, PortProtoStruct &mystruct) {
  argument.beginStructure();
  argument >> mystruct.port;
  argument >> mystruct.protocol;
  argument.endStructure();
  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const ForwardStruct &mystruct) {
  argument.beginStructure();
  argument << mystruct.port;
  argument << mystruct.protocol;

  argument << mystruct.to_port;
  argument << mystruct.to_address;
  argument.endStructure();
  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, ForwardStruct &mystruct) {
  argument.beginStructure();
  argument >> mystruct.port;
  argument >> mystruct.protocol;

  argument >> mystruct.to_port;
  argument >> mystruct.to_address;
  argument.endStructure();
  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const ZoneSettings &mystruct) {
  argument.beginStructure();
  argument << mystruct.version;
  argument << mystruct.name;
  argument << mystruct.description;
  argument << mystruct.UNUSED;
  argument << mystruct.target;
  argument << mystruct.services;
  argument << mystruct.ports;
  argument << mystruct.icmp_blocks;
  argument << mystruct.masquerade;
  argument << mystruct.forwards;
  argument << mystruct.ifaces;
  argument << mystruct.sources;
  argument << mystruct.rules;
  argument.endStructure();
  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, ZoneSettings &mystruct) {
  argument.beginStructure();
  argument >> mystruct.version;
  argument >> mystruct.name;
  argument >> mystruct.description;
  argument >> mystruct.UNUSED;
  argument >> mystruct.target;
  argument >> mystruct.services;
  argument >> mystruct.ports;
  argument >> mystruct.icmp_blocks;
  argument >> mystruct.masquerade;
  argument >> mystruct.forwards;
  argument >> mystruct.ifaces;
  argument >> mystruct.sources;
  argument >> mystruct.rules;
  argument.endStructure();
  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const ServiceSettings &mystruct) {
  argument.beginStructure();
  argument << mystruct.version;
  argument << mystruct.name;
  argument << mystruct.description;
  argument << mystruct.ports;
  argument << mystruct.modules;
  argument << mystruct.destinations;
  argument.endStructure();
  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, ServiceSettings &mystruct) {
  argument.beginStructure();
  argument >> mystruct.version;
  argument >> mystruct.name;
  argument >> mystruct.description;
  argument >> mystruct.ports;
  argument >> mystruct.modules;
  argument >> mystruct.destinations;
  argument.endStructure();
  return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const IcmpTypeSettings &mystruct) {
  argument.beginStructure();
  argument << mystruct.version;
  argument << mystruct.name;
  argument << mystruct.description;
  argument << mystruct.destinations;
  argument.endStructure();
  return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, IcmpTypeSettings &mystruct) {
  argument.beginStructure();
  argument >> mystruct.version;
  argument >> mystruct.name;
  argument >> mystruct.description;
  argument >> mystruct.destinations;
  argument.endStructure();
  return argument;
}

Firewall::Firewall() {
  qDBusRegisterMetaType< PortProtoStruct >();
  qDBusRegisterMetaType< QList<PortProtoStruct> >();

  qDBusRegisterMetaType< ForwardStruct >();
  qDBusRegisterMetaType< QList<ForwardStruct> >();

  qDBusRegisterMetaType< ServiceSettings >();
  qDBusRegisterMetaType< QList<ServiceSettings> >();

  qDBusRegisterMetaType< ZoneSettings >();
  qDBusRegisterMetaType< QList<ZoneSettings> >();

  qDBusRegisterMetaType< IcmpTypeSettings >();
  qDBusRegisterMetaType< QList<IcmpTypeSettings> >();

  qDBusRegisterMetaType< QList<QStringList> >();

  QDBusConnection bus = QDBusConnection::systemBus();
  _pBaseIface = new QDBusInterface("org.fedoraproject.FirewallD1", 
				   "/org/fedoraproject/FirewallD1",
				   "org.fedoraproject.FirewallD1", bus);
  _pConfigIface = new QDBusInterface("org.fedoraproject.FirewallD1", 
				     "/org/fedoraproject/FirewallD1",
				     "org.fedoraproject.FirewallD1.config", bus);
  _pZoneIface = new QDBusInterface("org.fedoraproject.FirewallD1", 
				   "/org/fedoraproject/FirewallD1",
				   "org.fedoraproject.FirewallD1.zone", bus);

  // Connect signals
  // ** TODO **
  
}

Firewall::~Firewall() {
  if( _pBaseIface != NULL ) {
    delete _pBaseIface;
    _pBaseIface = NULL;
  }

  if( _pConfigIface != NULL ) {
    delete _pConfigIface;
    _pConfigIface = NULL;
  }

  if( _pZoneIface != NULL ) {
    delete _pZoneIface;
    _pZoneIface = NULL;
  }
}

void Firewall::Reload() {
  _pBaseIface->call( "reload" );
}

void Firewall::SaveSettings() {
  _pBaseIface->call( "runtimeToPermanent" );  
}

QList< PortProtoStruct > Firewall::GetPorts( QString zone ) {
  QDBusReply< QList<QStringList> > reply = 
    _pZoneIface->call( "getPorts", zone );

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }

  QList<PortProtoStruct> retVal;
      
  foreach (QStringList val, reply.value()) {
    PortProtoStruct tmp;
    tmp.port = val.at(0);
    tmp.protocol = val.at(1);
    retVal.append(tmp);
  }

  return retVal;
}

QStringList Firewall::GetServices( QString zone ) {
  QDBusReply< QStringList > reply;

  if( 0 < zone.length() ) {
    reply = _pZoneIface->call( "getServices", zone );
  } else {
    reply = _pBaseIface->call( "listServices" );
  }
  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  return reply.value();
}

void Firewall::DumpService( QString service ) {

  QDBusReply< ServiceSettings > reply = 
    _pBaseIface->call("getServiceSettings", service);

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  qDebug() << "  Version: " << reply.value().version;
  qDebug() << "  Name: " << reply.value().name;
  qDebug() << "  Description: " << reply.value().description;

  qDebug() << "  Ports: ";
  foreach(PortProtoStruct proto, reply.value().ports) {
    qDebug() << "    " << proto.port << " -> " << proto.protocol;
  }

  qDebug() << "  Modules: ";
  foreach(QString module, reply.value().modules) {
    qDebug() << "    " << module;
  }

  qDebug() << "  Destinations: ";
  foreach(QString key, reply.value().destinations.keys() ) {
    qDebug() << "    " << reply.value().destinations[ key ];
  }

}

QStringList Firewall::GetZones() {
  QDBusReply< QStringList > reply = _pZoneIface->call( "getZones" );
  
  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  return reply.value();
}

QString Firewall::GetDefaultZone() {
  QDBusReply< QString > reply = _pBaseIface->call( "getDefaultZone" );
  
  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  return reply.value();
}

void Firewall::SetDefaultZone( QString zone ) {
  _pBaseIface->call( "setDefaultZone", zone );
}

void Firewall::DumpZone(QString zone ) {

  QDBusReply< ZoneSettings > reply = 
    _pBaseIface->call("getZoneSettings", zone);

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  qDebug() << "  Version: " << reply.value().version;
  qDebug() << "  Name: " << reply.value().name;
  qDebug() << "  Description: " << reply.value().description;
  qDebug() << "  Target: " << reply.value().target;

  qDebug() << "  Services: ";
  foreach(QString service, reply.value().services) {
    qDebug() << "    " << service;
  }

  qDebug() << "  Ports: ";
  foreach(PortProtoStruct proto, reply.value().ports) {
    qDebug() << "    " << proto.port << " -> " << proto.protocol;
  }

  qDebug() << "  ICMP Blocks: ";
  foreach(QString block, reply.value().icmp_blocks) {
    qDebug() << "    " << block;
  }

  qDebug() << "  Masquerade: " << reply.value().masquerade;

  qDebug() << "  Forwards: ";
  foreach(ForwardStruct forward, reply.value().forwards) {
    qDebug() << "    " << forward.port << "/" << forward.protocol << " -> " 
	     << forward.to_address << ":" << forward.to_port;
  }

  qDebug() << "  Interfaces: ";
  foreach(QString iface, reply.value().ifaces) {
    qDebug() << "    " << iface;
  }

  qDebug() << "  Sources: ";
  foreach(QString src, reply.value().sources) {
    qDebug() << "    " << src;
  }

  qDebug() << "  Rules: ";
  foreach(QString rule, reply.value().rules) {
    qDebug() << "    " << rule;
  }

}

QStringList Firewall::GetIcmpTypes() {
  QDBusReply< QStringList > reply = _pBaseIface->call( "listIcmpTypes" );
  
  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  return reply.value();
}

void Firewall::DumpIcmpType(QString icmpType ) {

  QDBusReply< IcmpTypeSettings > reply = 
    _pBaseIface->call("getIcmpTypeSettings", icmpType);

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  qDebug() << "  Version: " << reply.value().version;
  qDebug() << "  Name: " << reply.value().name;
  qDebug() << "  Description: " << reply.value().description;

  qDebug() << "  Destinations: ";
  foreach(QString destination, reply.value().destinations) {
    qDebug() << "    " << destination;
  }
}

bool Firewall::IsInPanicMode() {
  QDBusReply< bool > reply = 
    _pBaseIface->call("queryPanicMode");

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }

  return reply.value();
}

void Firewall::SetPanicMode( bool enable ) {

  if( enable ) {
    _pBaseIface->call( "enablePanicMode" );
  } else {
    _pBaseIface->call( "disablePanicMode" );
  }
}

void Firewall::GetPanicModeEnabled() {
  emit PanicModeChanged( true );
}

void Firewall::GetPanicModeDisabled() {
  emit PanicModeChanged( false );
}

void Firewall::GetReloaded() {
  emit Reloaded();
}

void Firewall::GetDefaultZoneChanged( QString zone ) {
  emit DefaultZoneChanged( zone );
}
