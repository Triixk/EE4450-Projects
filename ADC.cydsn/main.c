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
    uint32_t adc;
    float vin;
    float tmp;
    
    char str[40];
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    PGA_Start();
    ADC_Start();
    LCD_Start();
    LCD_ClearDisplay();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        ADC_StartConvert(); // Trigger ADC vonersion
        
        if (ADC_IsEndConversion(ADC_RETURN_STATUS) != 0){
            adc = ADC_GetResult16();
            vin = ADC_CountsTo_mVolts(adc);
            sprintf(str, "Vin = %.2f ", vin);
            LCD_Position(1,0);
            LCD_PrintString(str);
            // Temperature sensor
            // 10mV/C
            // 250 mV output at 25
            tmp = ();
            
            ADC_StartConvert(); // Trigger ADC vonersion
        }
        CyDelay(500);
        
    }
}

/* [] END OF FILE */
