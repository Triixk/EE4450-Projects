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
    char ch;
    UART_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        ch = UART_GetChar();
        if ( ch == '0'){
            LED_Write(0);
            UART_PutString("LED OFF \r\n");
        } 
        else if ( ch == '1'){
            LED_Write(1);
            UART_PutString("LED ON \r\n");
            
        }
    }
}

/* [] END OF FILE */
