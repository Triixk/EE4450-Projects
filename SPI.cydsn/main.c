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



bool SPI_Write(uint8_t reg, uint8_t *buf, int len);
bool SPI_Read(uint8_t reg, uint8_t *buf, int len);

int main(void)
{
    uint8_t buf[20];
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    SPI_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        // Write data to Slave 2
        SPI_SS_Reg_Write(0x02);
        
        SPI_Write(0b11100, buf, 2); // Write 2 bytes data to Slave 2 at reg 0b11100
        
        // Read data from Slave 1
        SPI_SS_Reg_Write(0x01);
        SPI_Read(0b01100, buf, 4); // Read 4 byte at reg 0b01100 from slave 1
    }
}

//-----------------------------------------------------
bool SPI_Write(uint8_t reg, uint8_t *buf, int len){
  
    while ( !(SPI_ReadTxStatus() & (SPI_STS_TX_FIFO_NOT_FULL)));
    SPI_WriteTxData(reg);
    SPI_PutArray(buf, len);
    return true;
}

//-----------------------------------------------------
bool SPI_Read(uint8_t reg, uint8_t *buf, int len){
    
    
    while ( !(SPI_ReadTxStatus() & (SPI_STS_TX_FIFO_NOT_FULL)));
    SPI_WriteTxData(reg);
    
    for(int i = 0; i < len; i++){
        SPI_WriteTxData(0x0);
        while( !(SPI_ReadRxStatus() & SPI_STS_RX_FIFO_NOT_EMPTY)){};
        *(buf+i) = SPI_ReadRxData();
    }
    return true;
}

/* [] END OF FILE */
