/*******************************************************************************
* File Name: LCD.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  LED Driver Component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_LED_Driver_LCD_H)
#define CY_LED_Driver_LCD_H


/***************************************
*   Conditional Compilation Parameters
***************************************/
#define LCD_BRIGHTNESS_EN                (0u)
#define LCD_COM_DRIVE                    (0u)
#define LCD_SEG_DRIVE                    (1u)
#define LCD_NUM_COM                      (4u)
#define LCD_NUM_SEG                      (8u)
#define LCD_TWO_NUM_COM                  ((uint8)((uint8)LCD_NUM_COM << 1u))

/* Error message for removed commons control register through optimization */
#ifdef LCD_Com_Driver_Sync_ctrl_reg__REMOVED
    #error LED_Driver_v1_10 requires all the signals from the commons terminal to be connected to pins.
#endif /* LCD_Com_Driver_Sync_ctrl_reg__REMOVED */

/* Error message for removed segments control registers through optimization */
#if defined LCD_Seg_Driver_L_Sync_ctrl_reg__REMOVED || \
defined LCD_Seg_Driver_M_Sync_ctrl_reg__REMOVED || \
defined LCD_Seg_Driver_H_Sync_ctrl_reg__REMOVED
    #error LED_Driver_v1_10 requires all the signals from the segments terminal to be connected to pins.
#endif /* LCD_Seg_Driver_L_Sync_ctrl_reg__REMOVED */


/***************************************
*   Header files
***************************************/
#include <LCD_Com_Driver.h>
#include <LCD_Seg_Driver_L.h>
#if (LCD_NUM_SEG > 8u)
    #include <LCD_Seg_Driver_M.h>
#endif /* Segment_M control register */
#if (LCD_NUM_SEG > 16u)
    #include <LCD_Seg_Driver_H.h>
#endif /* Segment_H control register */

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#ifndef CY_PSOC5A
    #error Component LED_Driver_v1_10 requires cy_boot v3.0 or later
#endif /* CY_PSOC5A */


/***************************************
*        Structure Definitions
***************************************/
typedef struct
{
    uint8 ledEnableState;
    /* Backup the segment values when going to sleep. (Stop() clears the buffers) */
    uint8 segLBackup[LCD_NUM_COM];
    #if (LCD_NUM_SEG > 8u) 
        uint8 segMBackup[LCD_NUM_COM];
    #endif /* (LCD_NUM_SEG > 8u) */
    #if (LCD_NUM_SEG > 16u) 
        uint8 segHBackup[LCD_NUM_COM];
    #endif /* (LCD_NUM_SEG > 16u) */
}LCD_backupStruct;


/***************************************
*        Function Prototypes
***************************************/
void LCD_Init(void)                       ;
void LCD_Enable(void)                     ;
void LCD_Start(void)                      ;
void LCD_Stop(void)                       ;
void LCD_SetDisplayRAM(uint8 value, uint8 position) 
                                                        ;
void LCD_SetRC(uint8 row, uint8 column)    ;
void LCD_ClearRC(uint8 row, uint8 column)  ;
void LCD_ToggleRC(uint8 row, uint8 column) ;
uint8 LCD_GetRC(uint8 row, uint8 column)   ;
void LCD_ClearDisplay(uint8 position)      ;
void LCD_ClearDisplayAll(void)             ;
void LCD_Write7SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        ;
void LCD_Write7SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        ;
void LCD_WriteString7Seg(char8 const character[], uint8 position)
                                                        ;
void LCD_PutChar7Seg(char8 character , uint8 position)
                                                        ;
void LCD_Write7SegDigitDec(uint8 digit, uint8 position)
                                                        ;
void LCD_Write7SegDigitHex(uint8 digit, uint8 position)
                                                        ;
void LCD_Write14SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        ;
void LCD_Write14SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        ;
void LCD_WriteString14Seg(char8 const character[], uint8 position)
                                                        ;
void LCD_PutChar14Seg(char8 character , uint8 position)
                                                        ;
void LCD_Write14SegDigitDec(uint8 digit, uint8 position)
                                                        ;
void LCD_Write14SegDigitHex(uint8 digit, uint8 position)
                                                        ;
void LCD_Write16SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        ;
void LCD_Write16SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        ;
void LCD_WriteString16Seg(char8 const character[], uint8 position)
                                                        ;
void LCD_PutChar16Seg(char8 character , uint8 position)
                                                        ;
void LCD_Write16SegDigitDec(uint8 digit, uint8 position)
                                                        ;
void LCD_Write16SegDigitHex(uint8 digit, uint8 position)
                                                        ;
void LCD_PutDecimalPoint(uint8 dp, uint8 position)
                                                        ;
uint8 LCD_GetDecimalPoint(uint8 position)  ;
uint8 LCD_EncodeNumber7Seg(uint8 number)   ;
uint8 LCD_EncodeChar7Seg(char8 input)      ;
uint16 LCD_EncodeNumber14Seg(uint8 number) ;
uint16 LCD_EncodeChar14Seg(char8 input)    ;
uint16 LCD_EncodeNumber16Seg(uint8 number) ;
uint16 LCD_EncodeChar16Seg(char8 input)    ;
void LCD_SetBrightness(uint8 bright, uint8 position)
                                                        ;
uint8 LCD_GetBrightness(uint8 position)    ;
void LCD_Sleep(void)                       ;
void LCD_Wakeup(void)                      ;


/***************************************
*           Global Variables
***************************************/
extern uint8 LCD_initVar;
extern uint8 LCD_enableVar;

/* Buffers used to hold the display(segment) values to be transferred to the control registers */
extern uint8 LCD_segLBuffer[LCD_NUM_COM];
#if (LCD_NUM_SEG > 8u) 
    extern uint8 LCD_segMBuffer[LCD_NUM_COM];
#endif /* (LCD_NUM_SEG > 8u) */
#if (LCD_NUM_SEG > 16u) 
    extern uint8 LCD_segHBuffer[LCD_NUM_COM];
#endif /* (LCD_NUM_SEG > 16u) */


/***************************************
*           API Constants
***************************************/

/* Related to conditional compilation */
#define LCD_HIGH                   (0x01u)
#define LCD_ENABLED                (0x01u)

/* Number of DMA channels */
#if (LCD_BRIGHTNESS_EN == LCD_ENABLED)
    #define LCD_CHANNEL_LIMIT      (0x03u)
#else
    #define LCD_CHANNEL_LIMIT      (0x02u)
#endif /* (LCD_BRIGHTNESS_EN == LCD_ENABLED) */

/* Defines related to sign extraction for number displays */
#define LCD_SIGNED                 (0x01u)
#define LCD_UNSIGNED               (0x00u)
#define LCD_ZERO_NEG               ((int32)0x00000000)

/* Brightness control defines */
#define LCD_INIT_BRIGHT            (0xFFu)

/* Segment display defines */
#if(LCD_SEG_DRIVE == LCD_HIGH)
    #define LCD_CLEAR              (0x00u)
    #define LCD_CLEAR_16           ((uint16)0x0000u)
    #define LCD_ZERO_7CHAR         (0x3Fu)
    #define LCD_ZERO_14CHAR        ((uint16)0x243Fu)
    #define LCD_ZERO_16CHAR        ((uint16)0x90FFu)
#else
    #define LCD_CLEAR              (0xFFu)
    #define LCD_CLEAR_16           ((uint16)0xFFFFu)
    #define LCD_ZERO_7CHAR         (0xC0u)
    #define LCD_ZERO_14CHAR        ((uint16)0xDBC0u)
    #define LCD_ZERO_16CHAR        ((uint16)0x6F00u)
#endif /* (LCD_SEG_DRIVE == LCD_HIGH) */

/* Shifts and 4-bit operation mask */
#define LCD_SHIFT_NIBBLE           (0x04u)
#define LCD_NIBBLE_MASK            (0x0Fu)
#define LCD_SHIFT_BYTE             (0x08u)

/* ASCII table access defines */
#define LCD_SEG_ASCII_OFFSET       (0x02u)
#define LCD_SEG_ASCII_LIM_HI       (0x08u)
#define LCD_SEG_ASCII_LIM_LO       (0x01u)

/* Decimal point defines */
#define LCD_DEC_POINT              (0x07u)
#define LCD_DEC_POINT_MASK         (0x01u)
#if(LCD_SEG_DRIVE == LCD_HIGH)
    #define LCD_DEC_POINT_VALUE    (0x80u)
#else
    #define LCD_DEC_POINT_VALUE    (0x7Fu)
#endif /* (LCD_SEG_DRIVE == LCD_HIGH) */

/* 7-seg position to register mapping defines */
#define LCD_SEG_REG_LOW            (0x00u)
#define LCD_SEG_REG_MID            (0x01u)
#define LCD_SEG_REG_HIGH           (0x02u)

/* Segment display alignment defines */
#define LCD_RIGHT_ALIGN            (0x00u)
#define LCD_LEFT_ALIGN             (0x01u)
#define LCD_ZERO_PAD               (0x02u)


/***************************************
*           Registers
***************************************/
#define LCD_CONTROL_REG_BASE       (CYDEV_PERIPH_BASE)
#define LCD_SRAM_BASE              (CYDEV_SRAM_BASE)

#define LCD_COM_CONTROL_PTR        (LCD_Com_Driver_Control_PTR)
#define LCD_SEG_L_CONTROL_PTR      (LCD_Seg_Driver_L_Control_PTR)

#if (LCD_NUM_SEG > 8u)
    #define LCD_SEG_M_CONTROL_PTR  (LCD_Seg_Driver_M_Control_PTR)
#endif /* (LCD_NUM_SEG > 8u) */
#if (LCD_NUM_SEG > 16u)
    #define LCD_SEG_H_CONTROL_PTR  (LCD_Seg_Driver_H_Control_PTR)
#endif /* (LCD_NUM_SEG > 16u) */


/***************************************
*           UDB PWM Registers
***************************************/
/* Control register */
#define LCD_CONTROL_REG            (*(reg8 *) LCD_bLED_PWM_CtlReg__CONTROL_REG)
#define LCD_CONTROL_PTR            ( (reg8 *) LCD_bLED_PWM_CtlReg__CONTROL_REG)

/* Counter register */
#define LCD_COUNTER_REG            (*(reg8 *) LCD_bLED_PWM_PwmDP_u0__A1_REG)
#define LCD_COUNTER_PTR            ((reg8 *) LCD_bLED_PWM_PwmDP_u0__A1_REG)
/* Compare value buffer */
#define LCD_COMPARE_REG            (*(reg8 *) LCD_bLED_PWM_PwmDP_u0__D0_REG)
#define LCD_COMPARE_PTR            ((reg8 *) LCD_bLED_PWM_PwmDP_u0__D0_REG)


/***************************************
*          Register Constants
***************************************/
/* Control Register Enable/Disable. Also use for LCD_enableVar */
#define LCD_CTRL_ENABLE            (0x01u)
#define LCD_CTRL_DISABLE           (0x00u)

#endif /* CY_LED_Driver_LCD_H Header File */


/* [] END OF FILE */
