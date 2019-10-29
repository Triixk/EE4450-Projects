/*******************************************************************************
* File Name: RedLED.h  
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

#if !defined(CY_PINS_RedLED_H) /* Pins RedLED_H */
#define CY_PINS_RedLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RedLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RedLED__PORT == 15 && ((RedLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RedLED_Write(uint8 value);
void    RedLED_SetDriveMode(uint8 mode);
uint8   RedLED_ReadDataReg(void);
uint8   RedLED_Read(void);
void    RedLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   RedLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RedLED_SetDriveMode() function.
     *  @{
     */
        #define RedLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RedLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RedLED_DM_RES_UP          PIN_DM_RES_UP
        #define RedLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define RedLED_DM_OD_LO           PIN_DM_OD_LO
        #define RedLED_DM_OD_HI           PIN_DM_OD_HI
        #define RedLED_DM_STRONG          PIN_DM_STRONG
        #define RedLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RedLED_MASK               RedLED__MASK
#define RedLED_SHIFT              RedLED__SHIFT
#define RedLED_WIDTH              1u

/* Interrupt constants */
#if defined(RedLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RedLED_SetInterruptMode() function.
     *  @{
     */
        #define RedLED_INTR_NONE      (uint16)(0x0000u)
        #define RedLED_INTR_RISING    (uint16)(0x0001u)
        #define RedLED_INTR_FALLING   (uint16)(0x0002u)
        #define RedLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RedLED_INTR_MASK      (0x01u) 
#endif /* (RedLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RedLED_PS                     (* (reg8 *) RedLED__PS)
/* Data Register */
#define RedLED_DR                     (* (reg8 *) RedLED__DR)
/* Port Number */
#define RedLED_PRT_NUM                (* (reg8 *) RedLED__PRT) 
/* Connect to Analog Globals */                                                  
#define RedLED_AG                     (* (reg8 *) RedLED__AG)                       
/* Analog MUX bux enable */
#define RedLED_AMUX                   (* (reg8 *) RedLED__AMUX) 
/* Bidirectional Enable */                                                        
#define RedLED_BIE                    (* (reg8 *) RedLED__BIE)
/* Bit-mask for Aliased Register Access */
#define RedLED_BIT_MASK               (* (reg8 *) RedLED__BIT_MASK)
/* Bypass Enable */
#define RedLED_BYP                    (* (reg8 *) RedLED__BYP)
/* Port wide control signals */                                                   
#define RedLED_CTL                    (* (reg8 *) RedLED__CTL)
/* Drive Modes */
#define RedLED_DM0                    (* (reg8 *) RedLED__DM0) 
#define RedLED_DM1                    (* (reg8 *) RedLED__DM1)
#define RedLED_DM2                    (* (reg8 *) RedLED__DM2) 
/* Input Buffer Disable Override */
#define RedLED_INP_DIS                (* (reg8 *) RedLED__INP_DIS)
/* LCD Common or Segment Drive */
#define RedLED_LCD_COM_SEG            (* (reg8 *) RedLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define RedLED_LCD_EN                 (* (reg8 *) RedLED__LCD_EN)
/* Slew Rate Control */
#define RedLED_SLW                    (* (reg8 *) RedLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RedLED_PRTDSI__CAPS_SEL       (* (reg8 *) RedLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RedLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RedLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RedLED_PRTDSI__OE_SEL0        (* (reg8 *) RedLED__PRTDSI__OE_SEL0) 
#define RedLED_PRTDSI__OE_SEL1        (* (reg8 *) RedLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RedLED_PRTDSI__OUT_SEL0       (* (reg8 *) RedLED__PRTDSI__OUT_SEL0) 
#define RedLED_PRTDSI__OUT_SEL1       (* (reg8 *) RedLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RedLED_PRTDSI__SYNC_OUT       (* (reg8 *) RedLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RedLED__SIO_CFG)
    #define RedLED_SIO_HYST_EN        (* (reg8 *) RedLED__SIO_HYST_EN)
    #define RedLED_SIO_REG_HIFREQ     (* (reg8 *) RedLED__SIO_REG_HIFREQ)
    #define RedLED_SIO_CFG            (* (reg8 *) RedLED__SIO_CFG)
    #define RedLED_SIO_DIFF           (* (reg8 *) RedLED__SIO_DIFF)
#endif /* (RedLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(RedLED__INTSTAT)
    #define RedLED_INTSTAT            (* (reg8 *) RedLED__INTSTAT)
    #define RedLED_SNAP               (* (reg8 *) RedLED__SNAP)
    
	#define RedLED_0_INTTYPE_REG 		(* (reg8 *) RedLED__0__INTTYPE)
#endif /* (RedLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RedLED_H */


/* [] END OF FILE */
