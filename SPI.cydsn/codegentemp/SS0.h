/*******************************************************************************
* File Name: SS0.h  
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

#if !defined(CY_PINS_SS0_H) /* Pins SS0_H */
#define CY_PINS_SS0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SS0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SS0__PORT == 15 && ((SS0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SS0_Write(uint8 value);
void    SS0_SetDriveMode(uint8 mode);
uint8   SS0_ReadDataReg(void);
uint8   SS0_Read(void);
void    SS0_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SS0_SetDriveMode() function.
     *  @{
     */
        #define SS0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SS0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SS0_DM_RES_UP          PIN_DM_RES_UP
        #define SS0_DM_RES_DWN         PIN_DM_RES_DWN
        #define SS0_DM_OD_LO           PIN_DM_OD_LO
        #define SS0_DM_OD_HI           PIN_DM_OD_HI
        #define SS0_DM_STRONG          PIN_DM_STRONG
        #define SS0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SS0_MASK               SS0__MASK
#define SS0_SHIFT              SS0__SHIFT
#define SS0_WIDTH              1u

/* Interrupt constants */
#if defined(SS0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS0_SetInterruptMode() function.
     *  @{
     */
        #define SS0_INTR_NONE      (uint16)(0x0000u)
        #define SS0_INTR_RISING    (uint16)(0x0001u)
        #define SS0_INTR_FALLING   (uint16)(0x0002u)
        #define SS0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SS0_INTR_MASK      (0x01u) 
#endif /* (SS0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SS0_PS                     (* (reg8 *) SS0__PS)
/* Data Register */
#define SS0_DR                     (* (reg8 *) SS0__DR)
/* Port Number */
#define SS0_PRT_NUM                (* (reg8 *) SS0__PRT) 
/* Connect to Analog Globals */                                                  
#define SS0_AG                     (* (reg8 *) SS0__AG)                       
/* Analog MUX bux enable */
#define SS0_AMUX                   (* (reg8 *) SS0__AMUX) 
/* Bidirectional Enable */                                                        
#define SS0_BIE                    (* (reg8 *) SS0__BIE)
/* Bit-mask for Aliased Register Access */
#define SS0_BIT_MASK               (* (reg8 *) SS0__BIT_MASK)
/* Bypass Enable */
#define SS0_BYP                    (* (reg8 *) SS0__BYP)
/* Port wide control signals */                                                   
#define SS0_CTL                    (* (reg8 *) SS0__CTL)
/* Drive Modes */
#define SS0_DM0                    (* (reg8 *) SS0__DM0) 
#define SS0_DM1                    (* (reg8 *) SS0__DM1)
#define SS0_DM2                    (* (reg8 *) SS0__DM2) 
/* Input Buffer Disable Override */
#define SS0_INP_DIS                (* (reg8 *) SS0__INP_DIS)
/* LCD Common or Segment Drive */
#define SS0_LCD_COM_SEG            (* (reg8 *) SS0__LCD_COM_SEG)
/* Enable Segment LCD */
#define SS0_LCD_EN                 (* (reg8 *) SS0__LCD_EN)
/* Slew Rate Control */
#define SS0_SLW                    (* (reg8 *) SS0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SS0_PRTDSI__CAPS_SEL       (* (reg8 *) SS0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SS0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SS0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SS0_PRTDSI__OE_SEL0        (* (reg8 *) SS0__PRTDSI__OE_SEL0) 
#define SS0_PRTDSI__OE_SEL1        (* (reg8 *) SS0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SS0_PRTDSI__OUT_SEL0       (* (reg8 *) SS0__PRTDSI__OUT_SEL0) 
#define SS0_PRTDSI__OUT_SEL1       (* (reg8 *) SS0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SS0_PRTDSI__SYNC_OUT       (* (reg8 *) SS0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SS0__SIO_CFG)
    #define SS0_SIO_HYST_EN        (* (reg8 *) SS0__SIO_HYST_EN)
    #define SS0_SIO_REG_HIFREQ     (* (reg8 *) SS0__SIO_REG_HIFREQ)
    #define SS0_SIO_CFG            (* (reg8 *) SS0__SIO_CFG)
    #define SS0_SIO_DIFF           (* (reg8 *) SS0__SIO_DIFF)
#endif /* (SS0__SIO_CFG) */

/* Interrupt Registers */
#if defined(SS0__INTSTAT)
    #define SS0_INTSTAT            (* (reg8 *) SS0__INTSTAT)
    #define SS0_SNAP               (* (reg8 *) SS0__SNAP)
    
	#define SS0_0_INTTYPE_REG 		(* (reg8 *) SS0__0__INTTYPE)
#endif /* (SS0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SS0_H */


/* [] END OF FILE */
