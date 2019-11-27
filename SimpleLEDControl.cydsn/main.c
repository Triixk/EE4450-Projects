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

int main(void)
{
    int count = 0;
    bool currSW;
    bool preSW;
    int timer = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        currSW = Status_nSW_Read();
        
        if ((preSW == 1) && (currSW == 0)){
            if (count == 0)
                timer = 100;
            count = count + 1;
        }
        preSW = currSW;
        if (count == 3)
            LED_Write(1);
        
        if (timer > 0)
            timer--;
        
        CyDelay(10);
    }
}

/* [] END OF FILE */
