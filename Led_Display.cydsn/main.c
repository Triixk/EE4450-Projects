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
    uint16_t    count = 0;
    bool preState;
    bool curState;
    
    //Initial value for preState
    preState = 1;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
 
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Init();
    LED_Enable();
    LED_Write7SegNumberDec(count, 0, 4, LED_RIGHT_ALIGN);
 
    for(;;)
    {
        /* Place your application code here. */
        if (!nSW_Read()){
        }
        //Read current switch state
        curState = nSW_Read();
        
        //Detect when switch pushed
        if ( (preState == 1) && (curState == 0)){
            count++;
            LED_Write7SegNumberDec(count, 0, 4, LED_RIGHT_ALIGN); // Display a number from com0 for 4 digits
            CyDelay(100);
        }
        //Update the curState to preState
        preState = curState;
    }
}

/* [] END OF FILE */
