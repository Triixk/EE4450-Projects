/*******************************************************************************
* File Name: SERVO.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SERVO_H) /* Pins SERVO_H */
#define CY_PINS_SERVO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SERVO_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SERVO__PORT == 15 && ((SERVO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SERVO_Write(uint8 value);
void    SERVO_SetDriveMode(uint8 mode);
uint8   SERVO_ReadDataReg(void);
uint8   SERVO_Read(void);
void    SERVO_SetInterruptMode(uint16 position, uint16 mode);
uint8   SERVO_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SERVO_SetDriveMode() function.
     *  @{
     */
        #define SERVO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SERVO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SERVO_DM_RES_UP          PIN_DM_RES_UP
        #define SERVO_DM_RES_DWN         PIN_DM_RES_DWN
        #define SERVO_DM_OD_LO           PIN_DM_OD_LO
        #define SERVO_DM_OD_HI           PIN_DM_OD_HI
        #define SERVO_DM_STRONG          PIN_DM_STRONG
        #define SERVO_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SERVO_MASK               SERVO__MASK
#define SERVO_SHIFT              SERVO__SHIFT
#define SERVO_WIDTH              1u

/* Interrupt constants */
#if defined(SERVO__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SERVO_SetInterruptMode() function.
     *  @{
     */
        #define SERVO_INTR_NONE      (uint16)(0x0000u)
        #define SERVO_INTR_RISING    (uint16)(0x0001u)
        #define SERVO_INTR_FALLING   (uint16)(0x0002u)
        #define SERVO_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SERVO_INTR_MASK      (0x01u) 
#endif /* (SERVO__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SERVO_PS                     (* (reg8 *) SERVO__PS)
/* Data Register */
#define SERVO_DR                     (* (reg8 *) SERVO__DR)
/* Port Number */
#define SERVO_PRT_NUM                (* (reg8 *) SERVO__PRT) 
/* Connect to Analog Globals */                                                  
#define SERVO_AG                     (* (reg8 *) SERVO__AG)                       
/* Analog MUX bux enable */
#define SERVO_AMUX                   (* (reg8 *) SERVO__AMUX) 
/* Bidirectional Enable */                                                        
#define SERVO_BIE                    (* (reg8 *) SERVO__BIE)
/* Bit-mask for Aliased Register Access */
#define SERVO_BIT_MASK               (* (reg8 *) SERVO__BIT_MASK)
/* Bypass Enable */
#define SERVO_BYP                    (* (reg8 *) SERVO__BYP)
/* Port wide control signals */                                                   
#define SERVO_CTL                    (* (reg8 *) SERVO__CTL)
/* Drive Modes */
#define SERVO_DM0                    (* (reg8 *) SERVO__DM0) 
#define SERVO_DM1                    (* (reg8 *) SERVO__DM1)
#define SERVO_DM2                    (* (reg8 *) SERVO__DM2) 
/* Input Buffer Disable Override */
#define SERVO_INP_DIS                (* (reg8 *) SERVO__INP_DIS)
/* LCD Common or Segment Drive */
#define SERVO_LCD_COM_SEG            (* (reg8 *) SERVO__LCD_COM_SEG)
/* Enable Segment LCD */
#define SERVO_LCD_EN                 (* (reg8 *) SERVO__LCD_EN)
/* Slew Rate Control */
#define SERVO_SLW                    (* (reg8 *) SERVO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SERVO_PRTDSI__CAPS_SEL       (* (reg8 *) SERVO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SERVO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SERVO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SERVO_PRTDSI__OE_SEL0        (* (reg8 *) SERVO__PRTDSI__OE_SEL0) 
#define SERVO_PRTDSI__OE_SEL1        (* (reg8 *) SERVO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SERVO_PRTDSI__OUT_SEL0       (* (reg8 *) SERVO__PRTDSI__OUT_SEL0) 
#define SERVO_PRTDSI__OUT_SEL1       (* (reg8 *) SERVO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SERVO_PRTDSI__SYNC_OUT       (* (reg8 *) SERVO__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SERVO__SIO_CFG)
    #define SERVO_SIO_HYST_EN        (* (reg8 *) SERVO__SIO_HYST_EN)
    #define SERVO_SIO_REG_HIFREQ     (* (reg8 *) SERVO__SIO_REG_HIFREQ)
    #define SERVO_SIO_CFG            (* (reg8 *) SERVO__SIO_CFG)
    #define SERVO_SIO_DIFF           (* (reg8 *) SERVO__SIO_DIFF)
#endif /* (SERVO__SIO_CFG) */

/* Interrupt Registers */
#if defined(SERVO__INTSTAT)
    #define SERVO_INTSTAT            (* (reg8 *) SERVO__INTSTAT)
    #define SERVO_SNAP               (* (reg8 *) SERVO__SNAP)
    
	#define SERVO_0_INTTYPE_REG 		(* (reg8 *) SERVO__0__INTTYPE)
#endif /* (SERVO__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SERVO_H */


/* [] END OF FILE */
