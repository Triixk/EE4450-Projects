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
    uint8_t counter = 0;
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("Hello world");
    
    LCD_Position(0,0);
    LCD_PutChar('a');
    CyDelay(2000);
    for (;;){
        /* Place your application code here. */
        LCD_PrintNumber(counter);
        counter++;
        CyDelay(500);
    }
}


/* [] END OF FILE */
