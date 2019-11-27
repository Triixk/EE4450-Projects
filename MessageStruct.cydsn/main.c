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

typdef enum SENSORTYPES{
    SEN_TEMPERATURE = 0,
    SEN_HUM,
    SEN_ULTRASONIC
} SENSORTYPES;

typedef struct SENSORDATA{
    SENSORTYPES sensorType;
    
    float       temp;
    uint8_t     hum;
    float       distance;
} SENSORDATA;

int main(void)
{
    SENSORDATA sensorDATA;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        // Read data from temperature sensor
        sensorDATA.sensorType = SEN_TEMPERATURE;
        sensorDATA.temp = Read_Temperature();   // Assume we have a read temp func
        
        xQueueSendToBack(xQhandle, sensorDATA, sizeof(sensorDATA), 0);
    }
    
    // Example: Read data from Queue
    SENSORDATA buf;
    float temp;
    
    xQueueReceive(xQhandle, buf, sizeof(buf), 0);
    if (buf.sensorType == SEN_TEMPERATURE){
        temp = buf.temp;
        sprintf(str, "#TEMP:%.2f\n\r", temp);
        UART_PutString(str);
    }
}

/* [] END OF FILE */
