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



int main()
{
    CyGlobalIntEnable;

    UART_Start();
    UARTB_Start();
    UART_PutString("Start\r\n");
    char ch;
    for(;;)
    {
        ch = UARTB_GetChar();
        if ( ch == 'a')
            UART_PutChar(ch);
        CyDelay(10);
    }
}
 
/* [] END OF FILE */
