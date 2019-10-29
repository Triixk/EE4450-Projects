/*******************************************************************************
* File Name: LEDE.h  
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

#if !defined(CY_PINS_LEDE_H) /* Pins LEDE_H */
#define CY_PINS_LEDE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDE__PORT == 15 && ((LEDE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDE_Write(uint8 value);
void    LEDE_SetDriveMode(uint8 mode);
uint8   LEDE_ReadDataReg(void);
uint8   LEDE_Read(void);
void    LEDE_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDE_SetDriveMode() function.
     *  @{
     */
        #define LEDE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDE_DM_RES_UP          PIN_DM_RES_UP
        #define LEDE_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDE_DM_OD_LO           PIN_DM_OD_LO
        #define LEDE_DM_OD_HI           PIN_DM_OD_HI
        #define LEDE_DM_STRONG          PIN_DM_STRONG
        #define LEDE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDE_MASK               LEDE__MASK
#define LEDE_SHIFT              LEDE__SHIFT
#define LEDE_WIDTH              1u

/* Interrupt constants */
#if defined(LEDE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDE_SetInterruptMode() function.
     *  @{
     */
        #define LEDE_INTR_NONE      (uint16)(0x0000u)
        #define LEDE_INTR_RISING    (uint16)(0x0001u)
        #define LEDE_INTR_FALLING   (uint16)(0x0002u)
        #define LEDE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDE_INTR_MASK      (0x01u) 
#endif /* (LEDE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDE_PS                     (* (reg8 *) LEDE__PS)
/* Data Register */
#define LEDE_DR                     (* (reg8 *) LEDE__DR)
/* Port Number */
#define LEDE_PRT_NUM                (* (reg8 *) LEDE__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDE_AG                     (* (reg8 *) LEDE__AG)                       
/* Analog MUX bux enable */
#define LEDE_AMUX                   (* (reg8 *) LEDE__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDE_BIE                    (* (reg8 *) LEDE__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDE_BIT_MASK               (* (reg8 *) LEDE__BIT_MASK)
/* Bypass Enable */
#define LEDE_BYP                    (* (reg8 *) LEDE__BYP)
/* Port wide control signals */                                                   
#define LEDE_CTL                    (* (reg8 *) LEDE__CTL)
/* Drive Modes */
#define LEDE_DM0                    (* (reg8 *) LEDE__DM0) 
#define LEDE_DM1                    (* (reg8 *) LEDE__DM1)
#define LEDE_DM2                    (* (reg8 *) LEDE__DM2) 
/* Input Buffer Disable Override */
#define LEDE_INP_DIS                (* (reg8 *) LEDE__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDE_LCD_COM_SEG            (* (reg8 *) LEDE__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDE_LCD_EN                 (* (reg8 *) LEDE__LCD_EN)
/* Slew Rate Control */
#define LEDE_SLW                    (* (reg8 *) LEDE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDE_PRTDSI__CAPS_SEL       (* (reg8 *) LEDE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDE_PRTDSI__OE_SEL0        (* (reg8 *) LEDE__PRTDSI__OE_SEL0) 
#define LEDE_PRTDSI__OE_SEL1        (* (reg8 *) LEDE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDE_PRTDSI__OUT_SEL0       (* (reg8 *) LEDE__PRTDSI__OUT_SEL0) 
#define LEDE_PRTDSI__OUT_SEL1       (* (reg8 *) LEDE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDE_PRTDSI__SYNC_OUT       (* (reg8 *) LEDE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDE__SIO_CFG)
    #define LEDE_SIO_HYST_EN        (* (reg8 *) LEDE__SIO_HYST_EN)
    #define LEDE_SIO_REG_HIFREQ     (* (reg8 *) LEDE__SIO_REG_HIFREQ)
    #define LEDE_SIO_CFG            (* (reg8 *) LEDE__SIO_CFG)
    #define LEDE_SIO_DIFF           (* (reg8 *) LEDE__SIO_DIFF)
#endif /* (LEDE__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDE__INTSTAT)
    #define LEDE_INTSTAT            (* (reg8 *) LEDE__INTSTAT)
    #define LEDE_SNAP               (* (reg8 *) LEDE__SNAP)
    
	#define LEDE_0_INTTYPE_REG 		(* (reg8 *) LEDE__0__INTTYPE)
#endif /* (LEDE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDE_H */


/* [] END OF FILE */
