/*
 *    PortAmbassador is a GUI tool for configuring the a Linux firewall.
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

#ifndef __CONSOLELOGGER_H__
#define __CONSOLELOGGER_H__

#include <QObject>
#include <QString>

/*! \brief Simple class that will log the arguments to its slots to the console.
 */
class ConsoleLogger : public QObject {
  Q_OBJECT

 public:
  void SetThreshold( int threshold );
  int GetThreshold();
  
  public slots:
    void ErrorMsg( const QString& msg );
    void WarningMsg( const QString& msg );
    void DebugMsg( const int level, const QString& msg );
    
 private:
    int _threshold;
};

#endif
