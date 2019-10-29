/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/*
	Copyright 2001, 2002 Georges Menie (www.menie.org)
	stdarg version contributed by Christian Ettinger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
	putchar is the only external dependency for this file,
	if you have a working putchar, leave it commented out.
	If not, uncomment the define below and
	replace outbyte(c) by your own function call.

#define putchar(c) outbyte(c)
*/
#include "device.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"

// defination for PSoC 4: CY_PSOC4
//                PSoC 5: CY_PSOC5
//                PSoC 6: CY_DEVICE_PSOC6ABLE2

    
//-----------------------------------------------------------------------------
void FreeRTOS_Init(){

#ifdef CY_DEVICE_PSOC6ABLE2
    return;
  
#endif
    
#if (CY_PSOC5)    
    // Port layer functions that need to be copied into the vector table.
    extern void xPortPendSVHandler( void );
    extern void xPortSysTickHandler( void );
    extern void vPortSVCHandler( void );
    extern cyisraddress CyRamVectors[];
   
    //	Install the OS Interrupt Handlers.
	CyRamVectors[ 11 ] = ( cyisraddress ) vPortSVCHandler;
	CyRamVectors[ 14 ] = ( cyisraddress ) xPortPendSVHandler;
	CyRamVectors[ 15 ] = ( cyisraddress ) xPortSysTickHandler;
#endif
}
//-----------------------------------------------------------------------------




//------------------------------------------------------------------------------

/* [] END OF FILE */
