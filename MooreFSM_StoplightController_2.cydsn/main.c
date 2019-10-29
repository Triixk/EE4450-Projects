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

typedef enum STATES{
    S_RED,
    S_GREEN,
    S_YELLOW,
} STATES;

int main(void)
{
    STATES  state = S_RED;
    int     cmdGo, cmdStop; // Command for 
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
    
        cmdGo   = (!nSW_Go_Read()) ? 1 : 0;
        cmdStop = (!nSW_STOP_Read()) ? 1 : 0;
        
        
        switch(cmdGo){
            case 1:
                if( state == S_GREEN){
                    // Turn on Green LED, turn off others
                    

                }else if( state == S_YELLOW){
                    // Turn on Yellow LED, turn off others
                    
                }else if( state == S_RED){
                    state = S_GREEN;
                    
                }
                break;
            case 0:
                if (state == S_RED){
                    // Turn on Red LED, turn off others
                    
                }
                break;
            default:
                break;
        }
        switch(cmdStop){
            case 1:
                if( state == S_RED){
                    // Turn on Red LED, turn off others
                    

                }else if( state == S_GREEN){
                    state = S_YELLOW;
                    timeOut = 20;
                    
                }else if( state == S_YELLOW){
                    // Turn on Yellow LED, turn off others
                    
                }
                break;
            default:
            case 0:
                if (state == S_GREEN){
                    // Turn on Green LED, turn off others
                }
                break;
            
        }
        if (timeOut > 0){
            timeOut--;
            if (timeOut == 0){
                if (state == S_YELLOW){
                    state = S_RED;
                }
            }
        }
        CyDelay(50);
    }
}

/* [] END OF FILE */
