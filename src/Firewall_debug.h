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

/*! \file Firewall_debug.h
 *  \brief Signatures of debug functions related to the Firewall class.
 */
#ifndef __FIREWALL_DEBUG_H__
#define __FIREWALL_DEBUG_H__

#include "Firewall.h"

/*! \brief Dumps the information for the specified service to the console.
 */
extern void DumpService( Firewall& wall, QString service );
  
/*! \brief Dumps the information for the specified zone to the console.
 */
extern void DumpZone( Firewall& wall, QString zone );

/*! \brief Dumps the information for the specified zone to the console.
 */
extern void DumpIcmpType( Firewall& wall, QString icmpType );

#endif
