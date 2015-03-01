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

/* qdbus examples:
sudo qdbus --system --literal org.fedoraproject.FirewallD1 /org/fedoraproject/FirewallD1 org.fedoraproject.FirewallD1.zone.getZones
sudo qdbus --system --literal org.fedoraproject.FirewallD1 /org/fedoraproject/FirewallD1 org.fedoraproject.FirewallD1.getZoneSettings public

Old solution to permissions issues:
https://lists.fedoraproject.org/pipermail/users/2011-January/389884.html

Update with info from:
http://blog.christophersmart.com/tag/rules/

Add the following to a file in /etc/polkit-1/rules.d:
polkit.addRule(function(action, subject) {
if (action.id == "org.fedoraproject.FirewallD1.config.info" &&
subject.isInGroup("wheel") && subject.active) {
return polkit.Result.YES;
}
});

*/

#ifndef __FIREWALL_H__
#define __FIREWALL_H__

#include <QtCore/QStringList>
#include <QtDBus/QtDBus>

/*! \brief Structure representing a port and protocol record.
 */
struct PortProtoStruct {
  QString port;
  QString protocol;
};

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

/*! \brief Class representing the state of the firewall, including information 
  on zones and services.
 */
class Firewall : public QObject {

  Q_OBJECT

 public:

  Firewall();
  ~Firewall();

  /*! \brief Triggers a reload.
   */
  void Reload();

  /*! \brief Makes current settings permanent.
   */
  void SaveSettings();

  /*! \addtogroup Ports
   * @{
   */

  /*! \brief Returns the list of open ports for the specified zone.
   *
   * Does not include ports associated with enabled services.
   */
  QList< PortProtoStruct > GetPorts( QString zone );

  /*! @}
   */

  /*! \addtogroup Services
   * @{
   */

  /*! \brief Returns the names of the enabled services for the specified zone.
   */
  QStringList GetServices( QString zone = QString("") );

  /*! \brief Returns information for the specified service.
   */
  ServiceSettings GetService( QString service );
  
  /*! @}
   */

  /*! \addtogroup Zones
   * @{
   */

  /*! \brief Returns the names of available zones.
   */
  QStringList GetZones( );

  /*! \brief Returns the name of the default zone.
   */
  QString GetDefaultZone( );

  /*! \brief Sets the name of the default zone.
   */
  void SetDefaultZone( QString zone );

  /*! \brief Returns information for the specified zone.
   */
  ZoneSettings GetZone( QString zone );

  /*! @}
   */

  /*! \addtogroup ICMP Types
   * @{
   */

  /*! \brief Returns the names of available ICMP Types.
   */
  QStringList GetIcmpTypes( );

  /*! \brief Returnsinformation for the specified ICMP type.
   */
  IcmpTypeSettings GetIcmpType( QString icmpType );

  /*! @}
   */

  /*! \addtogroup Panic Mode
   * @{
   */

  /*! \brief Returns true if panic mode is enabled.
   */
  bool IsInPanicMode( );

  /*! \brief Enables or disables panic mode.
   */
  void SetPanicMode( bool enable );

  /*! @}
   */

 public slots:
  /*! \brief Slot to connect to FirewallD's PanicModeEnabled signal
   */
  void GetPanicModeEnabled();
  /*! \brief Slot to connect to FirewallD's PanicModeDisabled signal
   */
  void GetPanicModeDisabled();
  /*! \brief Slot to connect to FirewallD's Reloaded signal
   */
  void GetReloaded();
  /*! \brief Slot to connect to FirewallD's DefaultZoneChanged signal
   */
  void GetDefaultZoneChanged( QString zone );

 signals:
  /*! \brief Emitted whenever an error occurs.
   *
   * \param msg Error message describing the problem.
   */
  void OnError( const QString& msg );

  /*! \brief Emitted warning messages
   *
   * \param msg Warning message describing the issue.
   */
  void OnWarn( const QString& msg );

  /*! \brief Emitted debug messages and corresponding level.
   *
   * \param level Debug message level.
   * \param msg Debug message.
   */
  void OnDebug( const int level, const QString& msg );

  /*! \brief Emitted whenever the default zone changes.
   *
   * \param zone The name of the new default zone.
   */
  void DefaultZoneChanged( const QString& zone );

  /*! \brief Emitted whenever the state of panic mode changes.
   *
   * \param state The new state of panic mode.
   */
  void PanicModeChanged( const bool state );

  /*! \brief Emitted whenever the firewall is reloaded.
   */
  void Reloaded();
  
 private:
  QDBusInterface* _pBaseIface;
  QDBusInterface* _pConfigIface;
  QDBusInterface* _pZoneIface;

};

#endif
