/*******************************************************************************
* File Name: LEDA.h  
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

#if !defined(CY_PINS_LEDA_H) /* Pins LEDA_H */
#define CY_PINS_LEDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDA__PORT == 15 && ((LEDA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDA_Write(uint8 value);
void    LEDA_SetDriveMode(uint8 mode);
uint8   LEDA_ReadDataReg(void);
uint8   LEDA_Read(void);
void    LEDA_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDA_SetDriveMode() function.
     *  @{
     */
        #define LEDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDA_DM_RES_UP          PIN_DM_RES_UP
        #define LEDA_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDA_DM_OD_LO           PIN_DM_OD_LO
        #define LEDA_DM_OD_HI           PIN_DM_OD_HI
        #define LEDA_DM_STRONG          PIN_DM_STRONG
        #define LEDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDA_MASK               LEDA__MASK
#define LEDA_SHIFT              LEDA__SHIFT
#define LEDA_WIDTH              1u

/* Interrupt constants */
#if defined(LEDA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDA_SetInterruptMode() function.
     *  @{
     */
        #define LEDA_INTR_NONE      (uint16)(0x0000u)
        #define LEDA_INTR_RISING    (uint16)(0x0001u)
        #define LEDA_INTR_FALLING   (uint16)(0x0002u)
        #define LEDA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDA_INTR_MASK      (0x01u) 
#endif /* (LEDA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDA_PS                     (* (reg8 *) LEDA__PS)
/* Data Register */
#define LEDA_DR                     (* (reg8 *) LEDA__DR)
/* Port Number */
#define LEDA_PRT_NUM                (* (reg8 *) LEDA__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDA_AG                     (* (reg8 *) LEDA__AG)                       
/* Analog MUX bux enable */
#define LEDA_AMUX                   (* (reg8 *) LEDA__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDA_BIE                    (* (reg8 *) LEDA__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDA_BIT_MASK               (* (reg8 *) LEDA__BIT_MASK)
/* Bypass Enable */
#define LEDA_BYP                    (* (reg8 *) LEDA__BYP)
/* Port wide control signals */                                                   
#define LEDA_CTL                    (* (reg8 *) LEDA__CTL)
/* Drive Modes */
#define LEDA_DM0                    (* (reg8 *) LEDA__DM0) 
#define LEDA_DM1                    (* (reg8 *) LEDA__DM1)
#define LEDA_DM2                    (* (reg8 *) LEDA__DM2) 
/* Input Buffer Disable Override */
#define LEDA_INP_DIS                (* (reg8 *) LEDA__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDA_LCD_COM_SEG            (* (reg8 *) LEDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDA_LCD_EN                 (* (reg8 *) LEDA__LCD_EN)
/* Slew Rate Control */
#define LEDA_SLW                    (* (reg8 *) LEDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDA_PRTDSI__CAPS_SEL       (* (reg8 *) LEDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDA_PRTDSI__OE_SEL0        (* (reg8 *) LEDA__PRTDSI__OE_SEL0) 
#define LEDA_PRTDSI__OE_SEL1        (* (reg8 *) LEDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDA_PRTDSI__OUT_SEL0       (* (reg8 *) LEDA__PRTDSI__OUT_SEL0) 
#define LEDA_PRTDSI__OUT_SEL1       (* (reg8 *) LEDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDA_PRTDSI__SYNC_OUT       (* (reg8 *) LEDA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDA__SIO_CFG)
    #define LEDA_SIO_HYST_EN        (* (reg8 *) LEDA__SIO_HYST_EN)
    #define LEDA_SIO_REG_HIFREQ     (* (reg8 *) LEDA__SIO_REG_HIFREQ)
    #define LEDA_SIO_CFG            (* (reg8 *) LEDA__SIO_CFG)
    #define LEDA_SIO_DIFF           (* (reg8 *) LEDA__SIO_DIFF)
#endif /* (LEDA__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDA__INTSTAT)
    #define LEDA_INTSTAT            (* (reg8 *) LEDA__INTSTAT)
    #define LEDA_SNAP               (* (reg8 *) LEDA__SNAP)
    
	#define LEDA_0_INTTYPE_REG 		(* (reg8 *) LEDA__0__INTTYPE)
#endif /* (LEDA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDA_H */


/* [] END OF FILE */
