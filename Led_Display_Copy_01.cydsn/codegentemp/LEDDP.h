/*******************************************************************************
* File Name: LEDDP.h  
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

#if !defined(CY_PINS_LEDDP_H) /* Pins LEDDP_H */
#define CY_PINS_LEDDP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDDP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDDP__PORT == 15 && ((LEDDP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDDP_Write(uint8 value);
void    LEDDP_SetDriveMode(uint8 mode);
uint8   LEDDP_ReadDataReg(void);
uint8   LEDDP_Read(void);
void    LEDDP_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDDP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDDP_SetDriveMode() function.
     *  @{
     */
        #define LEDDP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDDP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDDP_DM_RES_UP          PIN_DM_RES_UP
        #define LEDDP_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDDP_DM_OD_LO           PIN_DM_OD_LO
        #define LEDDP_DM_OD_HI           PIN_DM_OD_HI
        #define LEDDP_DM_STRONG          PIN_DM_STRONG
        #define LEDDP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDDP_MASK               LEDDP__MASK
#define LEDDP_SHIFT              LEDDP__SHIFT
#define LEDDP_WIDTH              1u

/* Interrupt constants */
#if defined(LEDDP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDDP_SetInterruptMode() function.
     *  @{
     */
        #define LEDDP_INTR_NONE      (uint16)(0x0000u)
        #define LEDDP_INTR_RISING    (uint16)(0x0001u)
        #define LEDDP_INTR_FALLING   (uint16)(0x0002u)
        #define LEDDP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDDP_INTR_MASK      (0x01u) 
#endif /* (LEDDP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDDP_PS                     (* (reg8 *) LEDDP__PS)
/* Data Register */
#define LEDDP_DR                     (* (reg8 *) LEDDP__DR)
/* Port Number */
#define LEDDP_PRT_NUM                (* (reg8 *) LEDDP__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDDP_AG                     (* (reg8 *) LEDDP__AG)                       
/* Analog MUX bux enable */
#define LEDDP_AMUX                   (* (reg8 *) LEDDP__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDDP_BIE                    (* (reg8 *) LEDDP__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDDP_BIT_MASK               (* (reg8 *) LEDDP__BIT_MASK)
/* Bypass Enable */
#define LEDDP_BYP                    (* (reg8 *) LEDDP__BYP)
/* Port wide control signals */                                                   
#define LEDDP_CTL                    (* (reg8 *) LEDDP__CTL)
/* Drive Modes */
#define LEDDP_DM0                    (* (reg8 *) LEDDP__DM0) 
#define LEDDP_DM1                    (* (reg8 *) LEDDP__DM1)
#define LEDDP_DM2                    (* (reg8 *) LEDDP__DM2) 
/* Input Buffer Disable Override */
#define LEDDP_INP_DIS                (* (reg8 *) LEDDP__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDDP_LCD_COM_SEG            (* (reg8 *) LEDDP__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDDP_LCD_EN                 (* (reg8 *) LEDDP__LCD_EN)
/* Slew Rate Control */
#define LEDDP_SLW                    (* (reg8 *) LEDDP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDDP_PRTDSI__CAPS_SEL       (* (reg8 *) LEDDP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDDP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDDP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDDP_PRTDSI__OE_SEL0        (* (reg8 *) LEDDP__PRTDSI__OE_SEL0) 
#define LEDDP_PRTDSI__OE_SEL1        (* (reg8 *) LEDDP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDDP_PRTDSI__OUT_SEL0       (* (reg8 *) LEDDP__PRTDSI__OUT_SEL0) 
#define LEDDP_PRTDSI__OUT_SEL1       (* (reg8 *) LEDDP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDDP_PRTDSI__SYNC_OUT       (* (reg8 *) LEDDP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDDP__SIO_CFG)
    #define LEDDP_SIO_HYST_EN        (* (reg8 *) LEDDP__SIO_HYST_EN)
    #define LEDDP_SIO_REG_HIFREQ     (* (reg8 *) LEDDP__SIO_REG_HIFREQ)
    #define LEDDP_SIO_CFG            (* (reg8 *) LEDDP__SIO_CFG)
    #define LEDDP_SIO_DIFF           (* (reg8 *) LEDDP__SIO_DIFF)
#endif /* (LEDDP__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDDP__INTSTAT)
    #define LEDDP_INTSTAT            (* (reg8 *) LEDDP__INTSTAT)
    #define LEDDP_SNAP               (* (reg8 *) LEDDP__SNAP)
    
	#define LEDDP_0_INTTYPE_REG 		(* (reg8 *) LEDDP__0__INTTYPE)
#endif /* (LEDDP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDDP_H */


/* [] END OF FILE */
