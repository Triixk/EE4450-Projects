/*******************************************************************************
* File Name: SS2.h  
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

#if !defined(CY_PINS_SS2_H) /* Pins SS2_H */
#define CY_PINS_SS2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SS2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SS2__PORT == 15 && ((SS2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SS2_Write(uint8 value);
void    SS2_SetDriveMode(uint8 mode);
uint8   SS2_ReadDataReg(void);
uint8   SS2_Read(void);
void    SS2_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SS2_SetDriveMode() function.
     *  @{
     */
        #define SS2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SS2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SS2_DM_RES_UP          PIN_DM_RES_UP
        #define SS2_DM_RES_DWN         PIN_DM_RES_DWN
        #define SS2_DM_OD_LO           PIN_DM_OD_LO
        #define SS2_DM_OD_HI           PIN_DM_OD_HI
        #define SS2_DM_STRONG          PIN_DM_STRONG
        #define SS2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SS2_MASK               SS2__MASK
#define SS2_SHIFT              SS2__SHIFT
#define SS2_WIDTH              1u

/* Interrupt constants */
#if defined(SS2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS2_SetInterruptMode() function.
     *  @{
     */
        #define SS2_INTR_NONE      (uint16)(0x0000u)
        #define SS2_INTR_RISING    (uint16)(0x0001u)
        #define SS2_INTR_FALLING   (uint16)(0x0002u)
        #define SS2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SS2_INTR_MASK      (0x01u) 
#endif /* (SS2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SS2_PS                     (* (reg8 *) SS2__PS)
/* Data Register */
#define SS2_DR                     (* (reg8 *) SS2__DR)
/* Port Number */
#define SS2_PRT_NUM                (* (reg8 *) SS2__PRT) 
/* Connect to Analog Globals */                                                  
#define SS2_AG                     (* (reg8 *) SS2__AG)                       
/* Analog MUX bux enable */
#define SS2_AMUX                   (* (reg8 *) SS2__AMUX) 
/* Bidirectional Enable */                                                        
#define SS2_BIE                    (* (reg8 *) SS2__BIE)
/* Bit-mask for Aliased Register Access */
#define SS2_BIT_MASK               (* (reg8 *) SS2__BIT_MASK)
/* Bypass Enable */
#define SS2_BYP                    (* (reg8 *) SS2__BYP)
/* Port wide control signals */                                                   
#define SS2_CTL                    (* (reg8 *) SS2__CTL)
/* Drive Modes */
#define SS2_DM0                    (* (reg8 *) SS2__DM0) 
#define SS2_DM1                    (* (reg8 *) SS2__DM1)
#define SS2_DM2                    (* (reg8 *) SS2__DM2) 
/* Input Buffer Disable Override */
#define SS2_INP_DIS                (* (reg8 *) SS2__INP_DIS)
/* LCD Common or Segment Drive */
#define SS2_LCD_COM_SEG            (* (reg8 *) SS2__LCD_COM_SEG)
/* Enable Segment LCD */
#define SS2_LCD_EN                 (* (reg8 *) SS2__LCD_EN)
/* Slew Rate Control */
#define SS2_SLW                    (* (reg8 *) SS2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SS2_PRTDSI__CAPS_SEL       (* (reg8 *) SS2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SS2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SS2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SS2_PRTDSI__OE_SEL0        (* (reg8 *) SS2__PRTDSI__OE_SEL0) 
#define SS2_PRTDSI__OE_SEL1        (* (reg8 *) SS2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SS2_PRTDSI__OUT_SEL0       (* (reg8 *) SS2__PRTDSI__OUT_SEL0) 
#define SS2_PRTDSI__OUT_SEL1       (* (reg8 *) SS2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SS2_PRTDSI__SYNC_OUT       (* (reg8 *) SS2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SS2__SIO_CFG)
    #define SS2_SIO_HYST_EN        (* (reg8 *) SS2__SIO_HYST_EN)
    #define SS2_SIO_REG_HIFREQ     (* (reg8 *) SS2__SIO_REG_HIFREQ)
    #define SS2_SIO_CFG            (* (reg8 *) SS2__SIO_CFG)
    #define SS2_SIO_DIFF           (* (reg8 *) SS2__SIO_DIFF)
#endif /* (SS2__SIO_CFG) */

/* Interrupt Registers */
#if defined(SS2__INTSTAT)
    #define SS2_INTSTAT            (* (reg8 *) SS2__INTSTAT)
    #define SS2_SNAP               (* (reg8 *) SS2__SNAP)
    
	#define SS2_0_INTTYPE_REG 		(* (reg8 *) SS2__0__INTTYPE)
#endif /* (SS2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SS2_H */


/* [] END OF FILE */
