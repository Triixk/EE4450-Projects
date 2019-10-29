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

CY_ISR(myISR_Timer){
    LED_Write(!LED_Read());
    Timer_ReadStatusRegister(); //Clear INT signal
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ISR_Timer_StartEx(myISR_Timer);
    Timer_Start();
    
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
