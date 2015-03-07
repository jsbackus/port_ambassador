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

#include <QDBusMetaType>

#include "Firewall.h"

Firewall::Firewall() {
  RegisterFirewallDTypes();
  
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
  bus.connect("org.fedoraproject.FirewallD1", "/org/fedoraproject/FirewallD1",
	      "org.fedoraproject.FirewallD1", "DefaultZoneChanged", this, 
	      SLOT(GetDefaultZoneChanged(QString)));

  bus.connect("org.fedoraproject.FirewallD1", "/org/fedoraproject/FirewallD1",
	      "org.fedoraproject.FirewallD1", "PanicModeDisabled", this, 
	      SLOT(GetPanicModeDisabled()));

  bus.connect("org.fedoraproject.FirewallD1", "/org/fedoraproject/FirewallD1",
	      "org.fedoraproject.FirewallD1", "PanicModeEnabled", this, 
	      SLOT(GetPanicModeEnabled()));

  bus.connect("org.fedoraproject.FirewallD1", "/org/fedoraproject/FirewallD1",
	      "org.fedoraproject.FirewallD1", "Reloaded", this, 
	      SLOT(Reloaded()));
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
  QDBusReply< QString > reply = _pBaseIface->call( "reload" );
  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }
}

void Firewall::SaveSettings() {
  QDBusReply< QString > reply = _pBaseIface->call( "runtimeToPermanent" );  
  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }
}

QList< PortProtoStruct > Firewall::GetPorts( QString zone ) {
  QDBusReply< QList<QStringList> > reply = 
    _pZoneIface->call( "getPorts", zone );

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
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
  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }
  return reply.value();
}

ServiceSettings Firewall::GetService( QString service ) {

  QDBusReply< ServiceSettings > reply = 
    _pBaseIface->call("getServiceSettings", service);

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

  return reply.value();
}

QStringList Firewall::GetZones() {
  QDBusReply< QStringList > reply = _pZoneIface->call( "getZones" );
  
  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

  return reply.value();
}

QString Firewall::GetDefaultZone() {
  QDBusReply< QString > reply = _pBaseIface->call( "getDefaultZone" );
  
  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

  return reply.value();
}

void Firewall::SetDefaultZone( QString zone ) {
  QDBusReply< QString > reply = _pBaseIface->call( "setDefaultZone", zone );

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }
}

ZoneSettings Firewall::GetZone(QString zone ) {

  QDBusReply< ZoneSettings > reply = 
    _pBaseIface->call("getZoneSettings", zone);

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

  // QDBusReply will return a valid but empty object.
  return reply.value();
}

QStringList Firewall::GetIcmpTypes() {
  QDBusReply< QStringList > reply = _pBaseIface->call( "listIcmpTypes" );
  
  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }
  return reply.value();
}

IcmpTypeSettings Firewall::GetIcmpType( QString icmpType ) {

  QDBusReply< IcmpTypeSettings > reply = 
    _pBaseIface->call("getIcmpTypeSettings", icmpType);

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

  // QDBusReply will return a valid but empty object.
  return reply.value();
}

bool Firewall::IsInPanicMode() {
  QDBusReply< bool > reply = 
    _pBaseIface->call("queryPanicMode");

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

  return reply.value();
}

void Firewall::SetPanicMode( bool enable ) {

  QDBusReply< QString > reply;
  if( enable ) {
    reply = _pBaseIface->call( "enablePanicMode" );
  } else {
    reply = _pBaseIface->call( "disablePanicMode" );
  }

  if(!reply.isValid()) {
    emit OnError( QString("Firewall Error: ") + reply.error().message() );
  }

}

void Firewall::GetPanicModeEnabled() {
  emit OnDebug( 5, "Panic Mode Enabled" );
  emit PanicModeChanged( true );
}

void Firewall::GetPanicModeDisabled() {
  emit OnDebug( 5, "Panic Mode Disabled" );
  emit PanicModeChanged( false );
}

void Firewall::GetReloaded() {
  emit OnDebug( 5, "Firewall Reloaded" );
  emit Reloaded();
}

void Firewall::GetDefaultZoneChanged( QString zone ) {
  emit OnDebug( 5, QString("Default Zone Changed to '") + zone + QString("'") );
  emit DefaultZoneChanged( zone );
}
