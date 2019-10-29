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
    S_IDLE,
    S_25,
    S_50,
    S_100
} STATES;

int main(void)
{
    STATES state = S_IDLE;
    bool preSW = 1; // Negative logic input
    bool curSW;
    bool bSWEdge = false;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_Start();
    
    for(;;)
    {
        /* Place your application code here. */
    
        // 1. Read current SW state to curSW
        curSW = nSW_Read();
        
        // 2. Check the falling edge
        if ((preSW == 1) && (curSW == 0)){
            bSWEdge = true;
        } else 
            bSWEdge = false;
        // 3. Update current SW state to prevous state
        preSW = curSW;
        
        switch(state){
            case S_IDLE:
                PWM_WriteCompare(0);    // Set output
                if (bSWEdge){
                    state = S_25;
                }
                break;
            case S_25:
                PWM_WriteCompare(25);    // Set output
                if (bSWEdge){
                    state = S_50;
                }
                break;
            case S_50:
                PWM_WriteCompare(50);    // Set output
                if (bSWEdge){
                    state = S_100;
                }
                break;
            case S_100:
                PWM_WriteCompare(100);    // Set output
                if (bSWEdge){
                    state = S_IDLE;
                }
                break;
        }
        CyDelay(50);
    }
}

/* [] END OF FILE */
