/*! \file Debug functions related to the Firewall class.
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
