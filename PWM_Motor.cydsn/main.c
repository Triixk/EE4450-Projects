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

#define CMP0    19099
#define CMP180  17899

int main(void)
{
    int cmp = CMP0;
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_Start();
    
    
    for(;;)
    {
        /* Place your application code here. */
        PWM_WriteCompare(cmp);
        cmp -= 100;
        if (cmp < CMP180){
            cmp = CMP0;
        }
        CyDelay(100);
    } 
}

/* [] END OF FILE */
