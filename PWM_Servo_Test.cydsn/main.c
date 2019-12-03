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
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define CMP0    19599
#define CMP180  17599

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_Start(); 
    
    for(;;)
    {
        /* Place your application code here. */
        CyDelay(500);
        PWM_WriteCompare(CMP180);
        CyDelay(500);
        PWM_WriteCompare(CMP0);
    } 
}

/* [] END OF FILE */
