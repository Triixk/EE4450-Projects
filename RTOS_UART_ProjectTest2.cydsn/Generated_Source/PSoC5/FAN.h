/*******************************************************************************
* File Name: FAN.h  
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

#if !defined(CY_PINS_FAN_H) /* Pins FAN_H */
#define CY_PINS_FAN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FAN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FAN__PORT == 15 && ((FAN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FAN_Write(uint8 value);
void    FAN_SetDriveMode(uint8 mode);
uint8   FAN_ReadDataReg(void);
uint8   FAN_Read(void);
void    FAN_SetInterruptMode(uint16 position, uint16 mode);
uint8   FAN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FAN_SetDriveMode() function.
     *  @{
     */
        #define FAN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FAN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FAN_DM_RES_UP          PIN_DM_RES_UP
        #define FAN_DM_RES_DWN         PIN_DM_RES_DWN
        #define FAN_DM_OD_LO           PIN_DM_OD_LO
        #define FAN_DM_OD_HI           PIN_DM_OD_HI
        #define FAN_DM_STRONG          PIN_DM_STRONG
        #define FAN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FAN_MASK               FAN__MASK
#define FAN_SHIFT              FAN__SHIFT
#define FAN_WIDTH              1u

/* Interrupt constants */
#if defined(FAN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FAN_SetInterruptMode() function.
     *  @{
     */
        #define FAN_INTR_NONE      (uint16)(0x0000u)
        #define FAN_INTR_RISING    (uint16)(0x0001u)
        #define FAN_INTR_FALLING   (uint16)(0x0002u)
        #define FAN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FAN_INTR_MASK      (0x01u) 
#endif /* (FAN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FAN_PS                     (* (reg8 *) FAN__PS)
/* Data Register */
#define FAN_DR                     (* (reg8 *) FAN__DR)
/* Port Number */
#define FAN_PRT_NUM                (* (reg8 *) FAN__PRT) 
/* Connect to Analog Globals */                                                  
#define FAN_AG                     (* (reg8 *) FAN__AG)                       
/* Analog MUX bux enable */
#define FAN_AMUX                   (* (reg8 *) FAN__AMUX) 
/* Bidirectional Enable */                                                        
#define FAN_BIE                    (* (reg8 *) FAN__BIE)
/* Bit-mask for Aliased Register Access */
#define FAN_BIT_MASK               (* (reg8 *) FAN__BIT_MASK)
/* Bypass Enable */
#define FAN_BYP                    (* (reg8 *) FAN__BYP)
/* Port wide control signals */                                                   
#define FAN_CTL                    (* (reg8 *) FAN__CTL)
/* Drive Modes */
#define FAN_DM0                    (* (reg8 *) FAN__DM0) 
#define FAN_DM1                    (* (reg8 *) FAN__DM1)
#define FAN_DM2                    (* (reg8 *) FAN__DM2) 
/* Input Buffer Disable Override */
#define FAN_INP_DIS                (* (reg8 *) FAN__INP_DIS)
/* LCD Common or Segment Drive */
#define FAN_LCD_COM_SEG            (* (reg8 *) FAN__LCD_COM_SEG)
/* Enable Segment LCD */
#define FAN_LCD_EN                 (* (reg8 *) FAN__LCD_EN)
/* Slew Rate Control */
#define FAN_SLW                    (* (reg8 *) FAN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FAN_PRTDSI__CAPS_SEL       (* (reg8 *) FAN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FAN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FAN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FAN_PRTDSI__OE_SEL0        (* (reg8 *) FAN__PRTDSI__OE_SEL0) 
#define FAN_PRTDSI__OE_SEL1        (* (reg8 *) FAN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FAN_PRTDSI__OUT_SEL0       (* (reg8 *) FAN__PRTDSI__OUT_SEL0) 
#define FAN_PRTDSI__OUT_SEL1       (* (reg8 *) FAN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FAN_PRTDSI__SYNC_OUT       (* (reg8 *) FAN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FAN__SIO_CFG)
    #define FAN_SIO_HYST_EN        (* (reg8 *) FAN__SIO_HYST_EN)
    #define FAN_SIO_REG_HIFREQ     (* (reg8 *) FAN__SIO_REG_HIFREQ)
    #define FAN_SIO_CFG            (* (reg8 *) FAN__SIO_CFG)
    #define FAN_SIO_DIFF           (* (reg8 *) FAN__SIO_DIFF)
#endif /* (FAN__SIO_CFG) */

/* Interrupt Registers */
#if defined(FAN__INTSTAT)
    #define FAN_INTSTAT            (* (reg8 *) FAN__INTSTAT)
    #define FAN_SNAP               (* (reg8 *) FAN__SNAP)
    
	#define FAN_0_INTTYPE_REG 		(* (reg8 *) FAN__0__INTTYPE)
#endif /* (FAN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FAN_H */


/* [] END OF FILE */
