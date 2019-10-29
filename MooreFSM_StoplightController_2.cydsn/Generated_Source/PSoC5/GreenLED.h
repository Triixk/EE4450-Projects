/*******************************************************************************
* File Name: GreenLED.h  
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

#if !defined(CY_PINS_GreenLED_H) /* Pins GreenLED_H */
#define CY_PINS_GreenLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "GreenLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 GreenLED__PORT == 15 && ((GreenLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    GreenLED_Write(uint8 value);
void    GreenLED_SetDriveMode(uint8 mode);
uint8   GreenLED_ReadDataReg(void);
uint8   GreenLED_Read(void);
void    GreenLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   GreenLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the GreenLED_SetDriveMode() function.
     *  @{
     */
        #define GreenLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define GreenLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define GreenLED_DM_RES_UP          PIN_DM_RES_UP
        #define GreenLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define GreenLED_DM_OD_LO           PIN_DM_OD_LO
        #define GreenLED_DM_OD_HI           PIN_DM_OD_HI
        #define GreenLED_DM_STRONG          PIN_DM_STRONG
        #define GreenLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define GreenLED_MASK               GreenLED__MASK
#define GreenLED_SHIFT              GreenLED__SHIFT
#define GreenLED_WIDTH              1u

/* Interrupt constants */
#if defined(GreenLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GreenLED_SetInterruptMode() function.
     *  @{
     */
        #define GreenLED_INTR_NONE      (uint16)(0x0000u)
        #define GreenLED_INTR_RISING    (uint16)(0x0001u)
        #define GreenLED_INTR_FALLING   (uint16)(0x0002u)
        #define GreenLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define GreenLED_INTR_MASK      (0x01u) 
#endif /* (GreenLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GreenLED_PS                     (* (reg8 *) GreenLED__PS)
/* Data Register */
#define GreenLED_DR                     (* (reg8 *) GreenLED__DR)
/* Port Number */
#define GreenLED_PRT_NUM                (* (reg8 *) GreenLED__PRT) 
/* Connect to Analog Globals */                                                  
#define GreenLED_AG                     (* (reg8 *) GreenLED__AG)                       
/* Analog MUX bux enable */
#define GreenLED_AMUX                   (* (reg8 *) GreenLED__AMUX) 
/* Bidirectional Enable */                                                        
#define GreenLED_BIE                    (* (reg8 *) GreenLED__BIE)
/* Bit-mask for Aliased Register Access */
#define GreenLED_BIT_MASK               (* (reg8 *) GreenLED__BIT_MASK)
/* Bypass Enable */
#define GreenLED_BYP                    (* (reg8 *) GreenLED__BYP)
/* Port wide control signals */                                                   
#define GreenLED_CTL                    (* (reg8 *) GreenLED__CTL)
/* Drive Modes */
#define GreenLED_DM0                    (* (reg8 *) GreenLED__DM0) 
#define GreenLED_DM1                    (* (reg8 *) GreenLED__DM1)
#define GreenLED_DM2                    (* (reg8 *) GreenLED__DM2) 
/* Input Buffer Disable Override */
#define GreenLED_INP_DIS                (* (reg8 *) GreenLED__INP_DIS)
/* LCD Common or Segment Drive */
#define GreenLED_LCD_COM_SEG            (* (reg8 *) GreenLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define GreenLED_LCD_EN                 (* (reg8 *) GreenLED__LCD_EN)
/* Slew Rate Control */
#define GreenLED_SLW                    (* (reg8 *) GreenLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define GreenLED_PRTDSI__CAPS_SEL       (* (reg8 *) GreenLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define GreenLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) GreenLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define GreenLED_PRTDSI__OE_SEL0        (* (reg8 *) GreenLED__PRTDSI__OE_SEL0) 
#define GreenLED_PRTDSI__OE_SEL1        (* (reg8 *) GreenLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define GreenLED_PRTDSI__OUT_SEL0       (* (reg8 *) GreenLED__PRTDSI__OUT_SEL0) 
#define GreenLED_PRTDSI__OUT_SEL1       (* (reg8 *) GreenLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define GreenLED_PRTDSI__SYNC_OUT       (* (reg8 *) GreenLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(GreenLED__SIO_CFG)
    #define GreenLED_SIO_HYST_EN        (* (reg8 *) GreenLED__SIO_HYST_EN)
    #define GreenLED_SIO_REG_HIFREQ     (* (reg8 *) GreenLED__SIO_REG_HIFREQ)
    #define GreenLED_SIO_CFG            (* (reg8 *) GreenLED__SIO_CFG)
    #define GreenLED_SIO_DIFF           (* (reg8 *) GreenLED__SIO_DIFF)
#endif /* (GreenLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(GreenLED__INTSTAT)
    #define GreenLED_INTSTAT            (* (reg8 *) GreenLED__INTSTAT)
    #define GreenLED_SNAP               (* (reg8 *) GreenLED__SNAP)
    
	#define GreenLED_0_INTTYPE_REG 		(* (reg8 *) GreenLED__0__INTTYPE)
#endif /* (GreenLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_GreenLED_H */


/* [] END OF FILE */
