/*******************************************************************************
* File Name: SS3.h  
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

#if !defined(CY_PINS_SS3_H) /* Pins SS3_H */
#define CY_PINS_SS3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SS3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SS3__PORT == 15 && ((SS3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SS3_Write(uint8 value);
void    SS3_SetDriveMode(uint8 mode);
uint8   SS3_ReadDataReg(void);
uint8   SS3_Read(void);
void    SS3_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SS3_SetDriveMode() function.
     *  @{
     */
        #define SS3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SS3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SS3_DM_RES_UP          PIN_DM_RES_UP
        #define SS3_DM_RES_DWN         PIN_DM_RES_DWN
        #define SS3_DM_OD_LO           PIN_DM_OD_LO
        #define SS3_DM_OD_HI           PIN_DM_OD_HI
        #define SS3_DM_STRONG          PIN_DM_STRONG
        #define SS3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SS3_MASK               SS3__MASK
#define SS3_SHIFT              SS3__SHIFT
#define SS3_WIDTH              1u

/* Interrupt constants */
#if defined(SS3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS3_SetInterruptMode() function.
     *  @{
     */
        #define SS3_INTR_NONE      (uint16)(0x0000u)
        #define SS3_INTR_RISING    (uint16)(0x0001u)
        #define SS3_INTR_FALLING   (uint16)(0x0002u)
        #define SS3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SS3_INTR_MASK      (0x01u) 
#endif /* (SS3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SS3_PS                     (* (reg8 *) SS3__PS)
/* Data Register */
#define SS3_DR                     (* (reg8 *) SS3__DR)
/* Port Number */
#define SS3_PRT_NUM                (* (reg8 *) SS3__PRT) 
/* Connect to Analog Globals */                                                  
#define SS3_AG                     (* (reg8 *) SS3__AG)                       
/* Analog MUX bux enable */
#define SS3_AMUX                   (* (reg8 *) SS3__AMUX) 
/* Bidirectional Enable */                                                        
#define SS3_BIE                    (* (reg8 *) SS3__BIE)
/* Bit-mask for Aliased Register Access */
#define SS3_BIT_MASK               (* (reg8 *) SS3__BIT_MASK)
/* Bypass Enable */
#define SS3_BYP                    (* (reg8 *) SS3__BYP)
/* Port wide control signals */                                                   
#define SS3_CTL                    (* (reg8 *) SS3__CTL)
/* Drive Modes */
#define SS3_DM0                    (* (reg8 *) SS3__DM0) 
#define SS3_DM1                    (* (reg8 *) SS3__DM1)
#define SS3_DM2                    (* (reg8 *) SS3__DM2) 
/* Input Buffer Disable Override */
#define SS3_INP_DIS                (* (reg8 *) SS3__INP_DIS)
/* LCD Common or Segment Drive */
#define SS3_LCD_COM_SEG            (* (reg8 *) SS3__LCD_COM_SEG)
/* Enable Segment LCD */
#define SS3_LCD_EN                 (* (reg8 *) SS3__LCD_EN)
/* Slew Rate Control */
#define SS3_SLW                    (* (reg8 *) SS3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SS3_PRTDSI__CAPS_SEL       (* (reg8 *) SS3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SS3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SS3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SS3_PRTDSI__OE_SEL0        (* (reg8 *) SS3__PRTDSI__OE_SEL0) 
#define SS3_PRTDSI__OE_SEL1        (* (reg8 *) SS3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SS3_PRTDSI__OUT_SEL0       (* (reg8 *) SS3__PRTDSI__OUT_SEL0) 
#define SS3_PRTDSI__OUT_SEL1       (* (reg8 *) SS3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SS3_PRTDSI__SYNC_OUT       (* (reg8 *) SS3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SS3__SIO_CFG)
    #define SS3_SIO_HYST_EN        (* (reg8 *) SS3__SIO_HYST_EN)
    #define SS3_SIO_REG_HIFREQ     (* (reg8 *) SS3__SIO_REG_HIFREQ)
    #define SS3_SIO_CFG            (* (reg8 *) SS3__SIO_CFG)
    #define SS3_SIO_DIFF           (* (reg8 *) SS3__SIO_DIFF)
#endif /* (SS3__SIO_CFG) */

/* Interrupt Registers */
#if defined(SS3__INTSTAT)
    #define SS3_INTSTAT            (* (reg8 *) SS3__INTSTAT)
    #define SS3_SNAP               (* (reg8 *) SS3__SNAP)
    
	#define SS3_0_INTTYPE_REG 		(* (reg8 *) SS3__0__INTTYPE)
#endif /* (SS3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SS3_H */


/* [] END OF FILE */
