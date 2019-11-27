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


char auth[] = "htWD8znEJsrgIpZZI8atoZixwlOv1_Y7";
	



int main()
{
    CyGlobalIntEnable;
    UART_Start();
    UARTB_Start();
    UART_PutString("Start\r\n");
    /*
    UART_PutString("Test\r\n");
    CyDelay(1000);
    UARTB_PutString("AT+NAME?\r\n");
    CyDelay(1000);
    buf_size = UARTB_GetRxBufferSize();
    sprintf(buf2, "Size: %d", buf_size);
    UART_PutString(buf2);
    
    for(int i = 0; i < buf_size;i++){
        buf[i] = UARTB_GetChar();
    }
    CyDelay(1000);

    UART_PutString(buf);
    */
    char ch;
    for(;;)
    {
        ch = UART_GetChar();
        UART_PutChar(ch);
        UARTB_PutChar(ch);
        CyDelay(10);
    }
}
 
/* [] END OF FILE */
