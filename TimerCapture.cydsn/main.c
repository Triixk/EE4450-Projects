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
    uint32_t    capture1, capture2;
    bool        isFirstCaptured = false;
    uint8_t     timerStatus;
    float       tin; // msec
    char        str[40];
    uint32_t    delay = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("Timer Capture");
    PWM_Start();
    Timer_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        timerStatus = Timer_ReadStatusRegister();
        if (timerStatus & 0x02){ // Timer_STATUS_CAPTURE
            if ( !isFirstCaptured ){
                capture1 = Timer_ReadCapture();
                isFirstCaptured = true;
            } else {
                capture2 = Timer_ReadCapture();
                isFirstCaptured = false;
                tin = (capture1 - capture2) / 1000000.0;
                if (delay >= 100000){
                    sprintf(str, "Tin = %.2f msec ", tin);
                    LCD_Position(0,0);
                    LCD_PrintString(str);
                    delay=0;
                }
            }
        } 
        CyDelayUs(10);
    }
}

/* [] END OF FILE */
