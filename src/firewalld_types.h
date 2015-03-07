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

#ifndef __FIREWALLD_TYPES_H__
#define __FIREWALLD_TYPES_H__

#include <QtCore/QStringList>
#include <QtDBus/QtDBus>

/*! \brief Structure representing a port and protocol record.
 */
struct PortProtoStruct {
  QString port;
  QString protocol;
};
#ifdef PFFT
/*! \brief Structure representing a passthrough record
 */
struct PassthroughStruct {
  QString ipv;
  QStringList arguments;
};

/*! \brief Structure representing a rules record
 */
struct RulesStruct {
  QString ipv;
  QString table;
  QString chain;
  int priority;
  QStringList arguments;
};

/*! \brief Structure representing a chain record
 */
struct ChainStruct {
  QString ipv;
  QString table;
  QString chain;
};
#endif
/*! \brief Structure representing a port forwarding record.
 */
struct ForwardStruct {
  QString port;
  QString protocol;

  QString to_port;
  QString to_address;
};

/*! \brief Structure representing a network service record.
 */
struct ServiceSettings {
  QString version;
  QString name;
  QString description;
  QList< PortProtoStruct > ports;
  QStringList modules;
  QMap< QString, QString > destinations;
};

/*! \brief Structure representing a firewall zone record.
 */
struct ZoneSettings {
  QString version;
  QString name;
  QString description;
  bool UNUSED;
  QString target;
  QStringList services;
  QList< PortProtoStruct > ports;
  QStringList icmp_blocks;
  bool masquerade;
  QList< ForwardStruct> forwards;
  QStringList ifaces;
  QStringList sources;
  QStringList rules;
};

/*! \brief Structure representing a network service record.
 */
struct IcmpTypeSettings {
  QString version;
  QString name;
  QString description;
  QStringList destinations;
};

Q_DECLARE_METATYPE(PortProtoStruct)
Q_DECLARE_METATYPE(QList< PortProtoStruct >)

Q_DECLARE_METATYPE(ForwardStruct)
Q_DECLARE_METATYPE(QList< ForwardStruct >)

Q_DECLARE_METATYPE(ServiceSettings)
Q_DECLARE_METATYPE(QList< ServiceSettings >)

Q_DECLARE_METATYPE(ZoneSettings)
Q_DECLARE_METATYPE(QList< ZoneSettings >)

Q_DECLARE_METATYPE(IcmpTypeSettings)
Q_DECLARE_METATYPE(QList< IcmpTypeSettings >)

extern QDBusArgument &operator<<(QDBusArgument &argument, 
				 const PortProtoStruct &mystruct);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, 
				       PortProtoStruct &mystruct);

extern QDBusArgument &operator<<(QDBusArgument &argument, 
				 const ForwardStruct &mystruct);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, 
				       ForwardStruct &mystruct);

extern QDBusArgument &operator<<(QDBusArgument &argument, 
				 const ZoneSettings &mystruct);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, 
				       ZoneSettings &mystruct);

extern QDBusArgument &operator<<(QDBusArgument &argument, 
				 const ServiceSettings &mystruct);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, 
				       ServiceSettings &mystruct);

extern QDBusArgument &operator<<(QDBusArgument &argument, 
				 const IcmpTypeSettings &mystruct);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, 
				       IcmpTypeSettings &mystruct);

extern void RegisterFirewallDTypes();

#endif
