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

    
    CyGlobalIntEnable; /* Enable global interrupts. */
 
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Init();
    LCD_Enable();
    LCD_Write7SegNumberDec(0, 0, 4, LCD_ZERO_PAD);
    
    uint32_t    count32 = 123456;
    LCD_Write7SegNumberDec(count32, 0, 4, LCD_RIGHT_ALIGN);
    
    for(;;)
    {
        
       
        
    
    }
}


/* [] END OF FILE */
