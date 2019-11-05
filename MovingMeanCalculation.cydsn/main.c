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

#define NUM_SAMPLE 10

double MovingMean(const double fNewVal){
    static double   fSample[NUM_SAMPLE];
    static int      fNumSamples = 0;
    static int      iArrIdx     = 0;
    static double   fTotalValue   = 0;
    
    if (fNumSamples < NUM_SAMPLE){
        fSample[fNumSamples] = fNewVal;
        fNumSamples++;
        fTotalValue += fNewVal;
    } else{
        fTotalValue = fTotalValue + fNewVal - fSample[iArrIdx];
        fSample[iArrIdx] = fNewVal;
        iArrIdx++;
        if (iArrIdx  >= NUM_SAMPLE){
            iArrIdx = 0;
        }
        
    }
    
    return fTotalValue / fNumSamples;
}

int main(void)
{
    double  fDistanceCm;
    double  fAvg;
    char    str[40];
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        fDistanceCm = Read_DistanceCm();
        fAvg = MovingMean(fDistanceCm);
        fprintf(str, "Obstacle Distance: %.2f cm \r\n", fAvg);
        UART_PrintString(str);  // Send the message to the PC through the UART
        CyDelay(250);           // Delay for 250 ms
        
    }
}

/* [] END OF FILE */
