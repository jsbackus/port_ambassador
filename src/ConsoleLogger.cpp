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

#include <iostream>

#include "ConsoleLogger.h"

using namespace std;

void ConsoleLogger::ErrorMsg( const QString& msg ) {
  wcout << L"[Error] " << msg.toUtf8().constData() << endl;
}

void ConsoleLogger::WarningMsg( const QString& msg ) {
  wcout << L"[Warning] " << msg.toUtf8().constData() << endl;
}

void ConsoleLogger::DebugMsg( const int level, const QString& msg ) {
  if( level < _threshold ) {
    wcout << L"[Debug] " << msg.toUtf8().constData() << endl;
  }
}
