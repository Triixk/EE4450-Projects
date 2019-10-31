/*******************************************************************************
* File Name: SS1.h  
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

#if !defined(CY_PINS_SS1_H) /* Pins SS1_H */
#define CY_PINS_SS1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SS1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SS1__PORT == 15 && ((SS1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SS1_Write(uint8 value);
void    SS1_SetDriveMode(uint8 mode);
uint8   SS1_ReadDataReg(void);
uint8   SS1_Read(void);
void    SS1_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SS1_SetDriveMode() function.
     *  @{
     */
        #define SS1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SS1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SS1_DM_RES_UP          PIN_DM_RES_UP
        #define SS1_DM_RES_DWN         PIN_DM_RES_DWN
        #define SS1_DM_OD_LO           PIN_DM_OD_LO
        #define SS1_DM_OD_HI           PIN_DM_OD_HI
        #define SS1_DM_STRONG          PIN_DM_STRONG
        #define SS1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SS1_MASK               SS1__MASK
#define SS1_SHIFT              SS1__SHIFT
#define SS1_WIDTH              1u

/* Interrupt constants */
#if defined(SS1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS1_SetInterruptMode() function.
     *  @{
     */
        #define SS1_INTR_NONE      (uint16)(0x0000u)
        #define SS1_INTR_RISING    (uint16)(0x0001u)
        #define SS1_INTR_FALLING   (uint16)(0x0002u)
        #define SS1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SS1_INTR_MASK      (0x01u) 
#endif /* (SS1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SS1_PS                     (* (reg8 *) SS1__PS)
/* Data Register */
#define SS1_DR                     (* (reg8 *) SS1__DR)
/* Port Number */
#define SS1_PRT_NUM                (* (reg8 *) SS1__PRT) 
/* Connect to Analog Globals */                                                  
#define SS1_AG                     (* (reg8 *) SS1__AG)                       
/* Analog MUX bux enable */
#define SS1_AMUX                   (* (reg8 *) SS1__AMUX) 
/* Bidirectional Enable */                                                        
#define SS1_BIE                    (* (reg8 *) SS1__BIE)
/* Bit-mask for Aliased Register Access */
#define SS1_BIT_MASK               (* (reg8 *) SS1__BIT_MASK)
/* Bypass Enable */
#define SS1_BYP                    (* (reg8 *) SS1__BYP)
/* Port wide control signals */                                                   
#define SS1_CTL                    (* (reg8 *) SS1__CTL)
/* Drive Modes */
#define SS1_DM0                    (* (reg8 *) SS1__DM0) 
#define SS1_DM1                    (* (reg8 *) SS1__DM1)
#define SS1_DM2                    (* (reg8 *) SS1__DM2) 
/* Input Buffer Disable Override */
#define SS1_INP_DIS                (* (reg8 *) SS1__INP_DIS)
/* LCD Common or Segment Drive */
#define SS1_LCD_COM_SEG            (* (reg8 *) SS1__LCD_COM_SEG)
/* Enable Segment LCD */
#define SS1_LCD_EN                 (* (reg8 *) SS1__LCD_EN)
/* Slew Rate Control */
#define SS1_SLW                    (* (reg8 *) SS1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SS1_PRTDSI__CAPS_SEL       (* (reg8 *) SS1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SS1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SS1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SS1_PRTDSI__OE_SEL0        (* (reg8 *) SS1__PRTDSI__OE_SEL0) 
#define SS1_PRTDSI__OE_SEL1        (* (reg8 *) SS1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SS1_PRTDSI__OUT_SEL0       (* (reg8 *) SS1__PRTDSI__OUT_SEL0) 
#define SS1_PRTDSI__OUT_SEL1       (* (reg8 *) SS1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SS1_PRTDSI__SYNC_OUT       (* (reg8 *) SS1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SS1__SIO_CFG)
    #define SS1_SIO_HYST_EN        (* (reg8 *) SS1__SIO_HYST_EN)
    #define SS1_SIO_REG_HIFREQ     (* (reg8 *) SS1__SIO_REG_HIFREQ)
    #define SS1_SIO_CFG            (* (reg8 *) SS1__SIO_CFG)
    #define SS1_SIO_DIFF           (* (reg8 *) SS1__SIO_DIFF)
#endif /* (SS1__SIO_CFG) */

/* Interrupt Registers */
#if defined(SS1__INTSTAT)
    #define SS1_INTSTAT            (* (reg8 *) SS1__INTSTAT)
    #define SS1_SNAP               (* (reg8 *) SS1__SNAP)
    
	#define SS1_0_INTTYPE_REG 		(* (reg8 *) SS1__0__INTTYPE)
#endif /* (SS1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SS1_H */


/* [] END OF FILE */
