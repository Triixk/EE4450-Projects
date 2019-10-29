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

#define ADDR_DS3231 0x68
#define ADDR_DS1307 0x68
#define _I2C_WRITE  0
#define _I2C_Read   1

#define DS1307_REG_CONTROL 0x07

#define DS3231_REG_SECONDS 0x00
#define DS3231_REG_CONTROL 0x0E
#define DS3231_REG_STATUS 0x0F

#define SUNDAY 1
#define MONDAY 2
#define TUESDAY 3
#define WEDNESDAY 4
#define THURSDAY 5
#define FRIDAY 6
#define SATURDAY 7

bool Read_I2C(uint8_t addr, uint8_t reg, uint8_t length, uint8_t *buf);
bool Write_I2C(uint8_t addr, uint8_t reg, uint8_t length, uint8_t *buf);

#define BCD2DEC(bcd) ( (bcd>>4)*10 + (bcd & 0x0F) )

//smartguy4198@hotmail.com

int main(void)
{
    uint8_t buf[7];
    int delay;
    uint8_t mm,dd,h,m,s,dow;
    uint16_t yyyy;
    bool     ampm;
    char str[40];
    char    *day[]={"SUN","MON","TUE","WED","THR","FRI","SAT"};
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    LCD_ClearDisplay();
    
    I2C_Start();
    /*
    //Skip this if if you got DS1307
    if ( Read_I2C(ADDR_DS3231,DS3231_REG_CONTROL,1,buf)){
        if (buf[0] & 0x80){
            buf[0] &= 0x80; // Clear /EOSC(bit7) to 0
            Write_I2C(ADDR_DS3231,DS3231_REG_CONTROL,1,buf);
        }
    }
    */
    LCD_PrintString("Update Data?");
    delay = 2;
    
    while(delay--){
        if(!nSW_Read()){
            buf[0] = 0x30;          // 30sec
            buf[1] = 0x29;          // 29min
            buf[2] = 0x60 | 0x02;   // 2pm: 12-Hour format (bit6=1), PM(bit5=1)
            buf[3] = THURSDAY;
            buf[4] = 0x08;          // Date:    08
            buf[5] = 0x10;          // Month:   10
            buf[6] = 0x19;          // Year :   2019
            if (Write_I2C(ADDR_DS1307,0x00,7,buf)){
                LCD_ClearDisplay();
                LCD_PrintString("Date Updated!");
                CyDelay(1000);      //Delay for 1sec
            }
            break;            
        }
        CyDelay(100);   //Delay for 100ms
    }
    for(;;)
    {
        /* Place your application code here. */
        // Read the date/time from DS1307
        if (Read_I2C(ADDR_DS1307,0x00,7,buf)){
            //Check bit6 12/24 hour format
            if (buf[2] & 0x40){
                //12-Hour format
                ampm = buf[2] & 0x20;   //bit5: /AM.PM
                s    = BCD2DEC(buf[0] & 0x7F);
                m    = BCD2DEC(buf[1] & 0x7F);
                h    = BCD2DEC(buf[2] & 0x1F);
                dow  = BCD2DEC(buf[3] & 0x07);
                dd   = BCD2DEC(buf[4] & 0x1F);
                mm   = BCD2DEC(buf[5] & 0x1F);
                yyyy = BCD2DEC(buf[6] & 0x1F)+2000;
                if (ampm == 0)
                    sprintf(str,"%2d:%2d/%2d AM",h,m,s);
                else
                    sprintf(str,"%2d:%2d/%2d PM",h,m,s);
                LCD_Position(1,0);
                LCD_PrintString(str);
            }else{
                //24-Hourt format
                s    = BCD2DEC(buf[0] & 0x7F);
                m    = BCD2DEC(buf[1] & 0x7F);
                h    = BCD2DEC(buf[2] & 0x3F);
                dow  = BCD2DEC(buf[3] & 0x07);
                dd   = BCD2DEC(buf[4] & 0x1F);
                mm   = BCD2DEC(buf[5] & 0x1F);
                yyyy = BCD2DEC(buf[6] & 0x1F)+2000;
                sprintf(str,"%2d:%2d/%2d PM",h,m,s);
                LCD_Position(1,0);
                LCD_PrintString(str);
            }
            sprintf(str,"%4d/%2d/%2d %s",yyyy,mm,dd,day[dow-1]);
            LCD_Position(0,0);
            LCD_PrintString(str);
            
            
        }
    }
}

bool Read_I2C(uint8_t addr, uint8_t reg, uint8_t length, uint8_t *buf){
    uint8_t err;
    int i;
    
    err = I2C_MasterSendStart(addr,_I2C_WRITE);    //Write first
    if (err != I2C_MSTR_NO_ERROR){
        I2C_MasterSendStop();
        return false;
    }
    err = I2C_MasterWriteByte(reg);
    if (err != I2C_MSTR_NO_ERROR){
        I2C_MasterSendStop();
        return false;
    }
    err = I2C_MasterSendRestart(addr,_I2C_Read);
    if (err != I2C_MSTR_NO_ERROR){
        I2C_MasterSendStop();
        return false;
    }
    
    for (i = 0; i < length; i++){
        if (i == (length-1) )
            buf[i] = I2C_MasterReadByte(I2C_NAK_DATA);
        else
            buf[i] = I2C_MasterReadByte(I2C_ACK_DATA);
      
    }
    I2C_MasterSendStop();
    return true;
}
bool Write_I2C(uint8_t addr, uint8_t reg, uint8_t length, uint8_t *buf){
    uint8_t err;
    int i;
    
    err = I2C_MasterSendStart(addr,_I2C_WRITE);    //Write first
    if (err != I2C_MSTR_NO_ERROR){
        I2C_MasterSendStop();
        return false;
    }
    
    err = I2C_MasterWriteByte(reg);
    if (err != I2C_MSTR_NO_ERROR){
        I2C_MasterSendStop();
        return false;
    }
    
    for (i = 0; i < length; i++){
        I2C_MasterWriteByte(buf[i]);
    }
    I2C_MasterSendStop();
    return true;
}

/* [] END OF FILE */
