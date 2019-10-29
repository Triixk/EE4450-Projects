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

        //Read current switch state
        curState = nSW_Read();
        
        //Detect when switch pushed
        if ( (preState == 1) && (curState == 0)){
            LEDA_Write(!LEDA_Read());
            LEDB_Write(!LEDB_Read());
            LEDC_Write(!LEDC_Read());
            LEDD_Write(!LEDD_Read());
            LEDE_Write(!LEDE_Read());
            LEDF_Write(!LEDF_Read());
            LEDG_Write(!LEDG_Read());
            LEDDP_Write(!LEDDP_Read());
            DIG1_Write(!DIG1_Read());
        }
        //Update the curState to preState
        preState = curState;
        
    }
}

/* [] END OF FILE */
