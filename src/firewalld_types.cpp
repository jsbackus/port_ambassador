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

#include "firewalld_types.h"

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

void RegisterFirewallDTypes() {
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
}
