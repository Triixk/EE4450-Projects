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
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    //int toogle = 0;
    bool preState;
    bool curState;
    
    //Initial value for preState
    preState = 1;
    
    for(;;)
    {
        /* Place your application code here. */
        /*
        if (nSW_Read()){
            LED_Write(0);
        }
        else
            LED_Write(1);

        if (nSW_Read() == 0){
            toogle = !toogle;
            LED_Write(toogle);
            while(nSW_Read() == 0);
        }

        while(nSW_Read() == 0){
            toogle = !toogle;
            LED_Write(toogle);
            CyDelay(100);
        }
        */
        
        //Read current switch state
        curState = nSW_Read();
        
        //Detect when switch pushed
        if ( (preState == 1) && (curState == 0))
            LED_Write(!LED_Read());
        
        //Update the curState to preState
        preState = curState;
        
    }
}

/* [] END OF FILE */
