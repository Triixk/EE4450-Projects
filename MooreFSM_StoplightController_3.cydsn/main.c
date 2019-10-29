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

#define GREEN_LIT   0
#define RED_LIT     1
#define YELLOW_LIT  2

typedef struct STATE_TABLE{
    int                 Output;
    struct STATE_TABLE  *GO;
    struct STATE_TABLE  *STOP;
    struct STATE_TABLE  *TIMEOUT;
} STATE_TABLE;

#define S_GREEN     &stable[2]
#define S_YELLOW    &stable[1]
#define S_RED       &stable[0]

int main(void)
{
    STATE_TABLE stable[] = {
        {RED_LIT,    S_GREEN,  S_RED,    S_RED},
        {YELLOW_LIT, S_YELLOW, S_YELLOW, S_RED},
        {GREEN_LIT,  S_GREEN,  S_YELLOW, S_GREEN},
    };
    
    STATE_TABLE *state = &stable[0];
 
    bool     cmdGo, cmdStop; // Command for 
    int     timeOut = 0;   
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    // After power on, turn off all lights
    RedLED_Write(0);
    GreenLED_Write(0);
    YellowLED_Write(0);
    
    for(;;)
    {
        /* Place your application code here. */
    
        cmdGo   = !nSW_Go_Read();
        cmdStop = !nSW_STOP_Read();
        
        if (state->Output == RED_LIT){
            // Turn on Red lit, turn off others
        } else if (state->Output == YELLOW_LIT){
            // Turn on Yello lit, turn off others
        } else if (state->Output == GREEN_LIT){
            // Turn on Green lit, turn off others
        }
        
        if (cmdGo){
            state = state->GO;
        }
        if (cmdStop){
            state = state->STOP;
            
            if (state == S_YELLOW){
                timeOut = 20;
            }
        }
        if (timeOut > 0){
            timeOut--;
            if (timeOut == 0){
                state = state->TIMEOUT;
            }
        }
        CyDelay(50);
    }
}

/* [] END OF FILE */
