/*******************************************************************************
* File Name: DIG1.h  
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

#if !defined(CY_PINS_DIG1_H) /* Pins DIG1_H */
#define CY_PINS_DIG1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIG1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIG1__PORT == 15 && ((DIG1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIG1_Write(uint8 value);
void    DIG1_SetDriveMode(uint8 mode);
uint8   DIG1_ReadDataReg(void);
uint8   DIG1_Read(void);
void    DIG1_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIG1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIG1_SetDriveMode() function.
     *  @{
     */
        #define DIG1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIG1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIG1_DM_RES_UP          PIN_DM_RES_UP
        #define DIG1_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIG1_DM_OD_LO           PIN_DM_OD_LO
        #define DIG1_DM_OD_HI           PIN_DM_OD_HI
        #define DIG1_DM_STRONG          PIN_DM_STRONG
        #define DIG1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIG1_MASK               DIG1__MASK
#define DIG1_SHIFT              DIG1__SHIFT
#define DIG1_WIDTH              1u

/* Interrupt constants */
#if defined(DIG1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIG1_SetInterruptMode() function.
     *  @{
     */
        #define DIG1_INTR_NONE      (uint16)(0x0000u)
        #define DIG1_INTR_RISING    (uint16)(0x0001u)
        #define DIG1_INTR_FALLING   (uint16)(0x0002u)
        #define DIG1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIG1_INTR_MASK      (0x01u) 
#endif /* (DIG1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIG1_PS                     (* (reg8 *) DIG1__PS)
/* Data Register */
#define DIG1_DR                     (* (reg8 *) DIG1__DR)
/* Port Number */
#define DIG1_PRT_NUM                (* (reg8 *) DIG1__PRT) 
/* Connect to Analog Globals */                                                  
#define DIG1_AG                     (* (reg8 *) DIG1__AG)                       
/* Analog MUX bux enable */
#define DIG1_AMUX                   (* (reg8 *) DIG1__AMUX) 
/* Bidirectional Enable */                                                        
#define DIG1_BIE                    (* (reg8 *) DIG1__BIE)
/* Bit-mask for Aliased Register Access */
#define DIG1_BIT_MASK               (* (reg8 *) DIG1__BIT_MASK)
/* Bypass Enable */
#define DIG1_BYP                    (* (reg8 *) DIG1__BYP)
/* Port wide control signals */                                                   
#define DIG1_CTL                    (* (reg8 *) DIG1__CTL)
/* Drive Modes */
#define DIG1_DM0                    (* (reg8 *) DIG1__DM0) 
#define DIG1_DM1                    (* (reg8 *) DIG1__DM1)
#define DIG1_DM2                    (* (reg8 *) DIG1__DM2) 
/* Input Buffer Disable Override */
#define DIG1_INP_DIS                (* (reg8 *) DIG1__INP_DIS)
/* LCD Common or Segment Drive */
#define DIG1_LCD_COM_SEG            (* (reg8 *) DIG1__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIG1_LCD_EN                 (* (reg8 *) DIG1__LCD_EN)
/* Slew Rate Control */
#define DIG1_SLW                    (* (reg8 *) DIG1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIG1_PRTDSI__CAPS_SEL       (* (reg8 *) DIG1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIG1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIG1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIG1_PRTDSI__OE_SEL0        (* (reg8 *) DIG1__PRTDSI__OE_SEL0) 
#define DIG1_PRTDSI__OE_SEL1        (* (reg8 *) DIG1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIG1_PRTDSI__OUT_SEL0       (* (reg8 *) DIG1__PRTDSI__OUT_SEL0) 
#define DIG1_PRTDSI__OUT_SEL1       (* (reg8 *) DIG1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIG1_PRTDSI__SYNC_OUT       (* (reg8 *) DIG1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIG1__SIO_CFG)
    #define DIG1_SIO_HYST_EN        (* (reg8 *) DIG1__SIO_HYST_EN)
    #define DIG1_SIO_REG_HIFREQ     (* (reg8 *) DIG1__SIO_REG_HIFREQ)
    #define DIG1_SIO_CFG            (* (reg8 *) DIG1__SIO_CFG)
    #define DIG1_SIO_DIFF           (* (reg8 *) DIG1__SIO_DIFF)
#endif /* (DIG1__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIG1__INTSTAT)
    #define DIG1_INTSTAT            (* (reg8 *) DIG1__INTSTAT)
    #define DIG1_SNAP               (* (reg8 *) DIG1__SNAP)
    
	#define DIG1_0_INTTYPE_REG 		(* (reg8 *) DIG1__0__INTTYPE)
#endif /* (DIG1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIG1_H */


/* [] END OF FILE */
