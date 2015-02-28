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

ServiceSettings Firewall::GetService( QString service ) {

  QDBusReply< ServiceSettings > reply = 
    _pBaseIface->call("getServiceSettings", service);

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  // QDBusReply will return a valid but empty object.
  return reply.value();
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

ZoneSettings Firewall::GetZone(QString zone ) {

  QDBusReply< ZoneSettings > reply = 
    _pBaseIface->call("getZoneSettings", zone);

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }

  // QDBusReply will return a valid but empty object.
  return reply.value();
}

QStringList Firewall::GetIcmpTypes() {
  QDBusReply< QStringList > reply = _pBaseIface->call( "listIcmpTypes" );
  
  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }
  return reply.value();
}

IcmpTypeSettings Firewall::GetIcmpType( QString icmpType ) {

  QDBusReply< IcmpTypeSettings > reply = 
    _pBaseIface->call("getIcmpTypeSettings", icmpType);

  if (!reply.isValid()) {
    qDebug() << "Error:" << reply.error().message();
    exit(1);
  }

  // QDBusReply will return a valid but empty object.
  return reply.value();
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
