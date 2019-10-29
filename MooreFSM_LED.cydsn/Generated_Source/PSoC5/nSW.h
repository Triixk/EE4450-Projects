/*******************************************************************************
* File Name: nSW.h  
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

#if !defined(CY_PINS_nSW_H) /* Pins nSW_H */
#define CY_PINS_nSW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "nSW_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 nSW__PORT == 15 && ((nSW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    nSW_Write(uint8 value);
void    nSW_SetDriveMode(uint8 mode);
uint8   nSW_ReadDataReg(void);
uint8   nSW_Read(void);
void    nSW_SetInterruptMode(uint16 position, uint16 mode);
uint8   nSW_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the nSW_SetDriveMode() function.
     *  @{
     */
        #define nSW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define nSW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define nSW_DM_RES_UP          PIN_DM_RES_UP
        #define nSW_DM_RES_DWN         PIN_DM_RES_DWN
        #define nSW_DM_OD_LO           PIN_DM_OD_LO
        #define nSW_DM_OD_HI           PIN_DM_OD_HI
        #define nSW_DM_STRONG          PIN_DM_STRONG
        #define nSW_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define nSW_MASK               nSW__MASK
#define nSW_SHIFT              nSW__SHIFT
#define nSW_WIDTH              1u

/* Interrupt constants */
#if defined(nSW__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in nSW_SetInterruptMode() function.
     *  @{
     */
        #define nSW_INTR_NONE      (uint16)(0x0000u)
        #define nSW_INTR_RISING    (uint16)(0x0001u)
        #define nSW_INTR_FALLING   (uint16)(0x0002u)
        #define nSW_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define nSW_INTR_MASK      (0x01u) 
#endif /* (nSW__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define nSW_PS                     (* (reg8 *) nSW__PS)
/* Data Register */
#define nSW_DR                     (* (reg8 *) nSW__DR)
/* Port Number */
#define nSW_PRT_NUM                (* (reg8 *) nSW__PRT) 
/* Connect to Analog Globals */                                                  
#define nSW_AG                     (* (reg8 *) nSW__AG)                       
/* Analog MUX bux enable */
#define nSW_AMUX                   (* (reg8 *) nSW__AMUX) 
/* Bidirectional Enable */                                                        
#define nSW_BIE                    (* (reg8 *) nSW__BIE)
/* Bit-mask for Aliased Register Access */
#define nSW_BIT_MASK               (* (reg8 *) nSW__BIT_MASK)
/* Bypass Enable */
#define nSW_BYP                    (* (reg8 *) nSW__BYP)
/* Port wide control signals */                                                   
#define nSW_CTL                    (* (reg8 *) nSW__CTL)
/* Drive Modes */
#define nSW_DM0                    (* (reg8 *) nSW__DM0) 
#define nSW_DM1                    (* (reg8 *) nSW__DM1)
#define nSW_DM2                    (* (reg8 *) nSW__DM2) 
/* Input Buffer Disable Override */
#define nSW_INP_DIS                (* (reg8 *) nSW__INP_DIS)
/* LCD Common or Segment Drive */
#define nSW_LCD_COM_SEG            (* (reg8 *) nSW__LCD_COM_SEG)
/* Enable Segment LCD */
#define nSW_LCD_EN                 (* (reg8 *) nSW__LCD_EN)
/* Slew Rate Control */
#define nSW_SLW                    (* (reg8 *) nSW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define nSW_PRTDSI__CAPS_SEL       (* (reg8 *) nSW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define nSW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) nSW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define nSW_PRTDSI__OE_SEL0        (* (reg8 *) nSW__PRTDSI__OE_SEL0) 
#define nSW_PRTDSI__OE_SEL1        (* (reg8 *) nSW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define nSW_PRTDSI__OUT_SEL0       (* (reg8 *) nSW__PRTDSI__OUT_SEL0) 
#define nSW_PRTDSI__OUT_SEL1       (* (reg8 *) nSW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define nSW_PRTDSI__SYNC_OUT       (* (reg8 *) nSW__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(nSW__SIO_CFG)
    #define nSW_SIO_HYST_EN        (* (reg8 *) nSW__SIO_HYST_EN)
    #define nSW_SIO_REG_HIFREQ     (* (reg8 *) nSW__SIO_REG_HIFREQ)
    #define nSW_SIO_CFG            (* (reg8 *) nSW__SIO_CFG)
    #define nSW_SIO_DIFF           (* (reg8 *) nSW__SIO_DIFF)
#endif /* (nSW__SIO_CFG) */

/* Interrupt Registers */
#if defined(nSW__INTSTAT)
    #define nSW_INTSTAT            (* (reg8 *) nSW__INTSTAT)
    #define nSW_SNAP               (* (reg8 *) nSW__SNAP)
    
	#define nSW_0_INTTYPE_REG 		(* (reg8 *) nSW__0__INTTYPE)
#endif /* (nSW__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_nSW_H */


/* [] END OF FILE */
