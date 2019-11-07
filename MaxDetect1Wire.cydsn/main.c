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
    S_ERROR = -1,
    S_INIT,
    S_START,
    S_WAIT_FOR_SENSOR,
    S_RESPONSE,
    S_READY_TO_SEND_DATA,
    S_DATA_START,
    S_DATA_GOT,
    S_DONE
} STATES;

bool MaxDetect_read(int *temperatureC, int *humidity){
    STATES state = S_INIT;
    uint8_t buf[5]; // 40-bit buffer
    int bitReceived = 0;
    int byteReceived = 0;
    int timer = 0;
    
    while ( (state != S_DONE) && (state != S_ERROR)){
        switch (state){
            case S_INIT:
                OneWire_Write(1);
                CyDelay(200);       // Delay for 200ms
                state = S_START;
                break;
            case S_START:
                OneWire_Write(0);
                CyDelay(10);        // Delay for 10ms
                OneWire_Write(1);
                timer = 40;
                state = S_WAIT_FOR_SENSOR;
                break;
            case S_WAIT_FOR_SENSOR:
                if (timer > 0){
                    if (OneWire_Read()==0){
                        state = S_RESPONSE;
                        timer = 80;
                        break;
                    }
                }else{
                    state = S_ERROR;
                }
                break;
            case S_RESPONSE:
                break;
            case S_READY_TO_SEND_DATA:
                break;
            case S_DATA_START:
                break;
            case S_DATA_GOT:
                break;
            case S_DONE:
                break;
            case S_ERROR:
                break;
        }
        if (timer > 0) timer--;
        CyDelayUs(1);   // Delay 1 us
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
