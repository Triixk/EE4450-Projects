/*******************************************************************************
* File Name: DIG4.h  
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

#if !defined(CY_PINS_DIG4_H) /* Pins DIG4_H */
#define CY_PINS_DIG4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIG4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIG4__PORT == 15 && ((DIG4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIG4_Write(uint8 value);
void    DIG4_SetDriveMode(uint8 mode);
uint8   DIG4_ReadDataReg(void);
uint8   DIG4_Read(void);
void    DIG4_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIG4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIG4_SetDriveMode() function.
     *  @{
     */
        #define DIG4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIG4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIG4_DM_RES_UP          PIN_DM_RES_UP
        #define DIG4_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIG4_DM_OD_LO           PIN_DM_OD_LO
        #define DIG4_DM_OD_HI           PIN_DM_OD_HI
        #define DIG4_DM_STRONG          PIN_DM_STRONG
        #define DIG4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIG4_MASK               DIG4__MASK
#define DIG4_SHIFT              DIG4__SHIFT
#define DIG4_WIDTH              1u

/* Interrupt constants */
#if defined(DIG4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIG4_SetInterruptMode() function.
     *  @{
     */
        #define DIG4_INTR_NONE      (uint16)(0x0000u)
        #define DIG4_INTR_RISING    (uint16)(0x0001u)
        #define DIG4_INTR_FALLING   (uint16)(0x0002u)
        #define DIG4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIG4_INTR_MASK      (0x01u) 
#endif /* (DIG4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIG4_PS                     (* (reg8 *) DIG4__PS)
/* Data Register */
#define DIG4_DR                     (* (reg8 *) DIG4__DR)
/* Port Number */
#define DIG4_PRT_NUM                (* (reg8 *) DIG4__PRT) 
/* Connect to Analog Globals */                                                  
#define DIG4_AG                     (* (reg8 *) DIG4__AG)                       
/* Analog MUX bux enable */
#define DIG4_AMUX                   (* (reg8 *) DIG4__AMUX) 
/* Bidirectional Enable */                                                        
#define DIG4_BIE                    (* (reg8 *) DIG4__BIE)
/* Bit-mask for Aliased Register Access */
#define DIG4_BIT_MASK               (* (reg8 *) DIG4__BIT_MASK)
/* Bypass Enable */
#define DIG4_BYP                    (* (reg8 *) DIG4__BYP)
/* Port wide control signals */                                                   
#define DIG4_CTL                    (* (reg8 *) DIG4__CTL)
/* Drive Modes */
#define DIG4_DM0                    (* (reg8 *) DIG4__DM0) 
#define DIG4_DM1                    (* (reg8 *) DIG4__DM1)
#define DIG4_DM2                    (* (reg8 *) DIG4__DM2) 
/* Input Buffer Disable Override */
#define DIG4_INP_DIS                (* (reg8 *) DIG4__INP_DIS)
/* LCD Common or Segment Drive */
#define DIG4_LCD_COM_SEG            (* (reg8 *) DIG4__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIG4_LCD_EN                 (* (reg8 *) DIG4__LCD_EN)
/* Slew Rate Control */
#define DIG4_SLW                    (* (reg8 *) DIG4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIG4_PRTDSI__CAPS_SEL       (* (reg8 *) DIG4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIG4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIG4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIG4_PRTDSI__OE_SEL0        (* (reg8 *) DIG4__PRTDSI__OE_SEL0) 
#define DIG4_PRTDSI__OE_SEL1        (* (reg8 *) DIG4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIG4_PRTDSI__OUT_SEL0       (* (reg8 *) DIG4__PRTDSI__OUT_SEL0) 
#define DIG4_PRTDSI__OUT_SEL1       (* (reg8 *) DIG4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIG4_PRTDSI__SYNC_OUT       (* (reg8 *) DIG4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIG4__SIO_CFG)
    #define DIG4_SIO_HYST_EN        (* (reg8 *) DIG4__SIO_HYST_EN)
    #define DIG4_SIO_REG_HIFREQ     (* (reg8 *) DIG4__SIO_REG_HIFREQ)
    #define DIG4_SIO_CFG            (* (reg8 *) DIG4__SIO_CFG)
    #define DIG4_SIO_DIFF           (* (reg8 *) DIG4__SIO_DIFF)
#endif /* (DIG4__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIG4__INTSTAT)
    #define DIG4_INTSTAT            (* (reg8 *) DIG4__INTSTAT)
    #define DIG4_SNAP               (* (reg8 *) DIG4__SNAP)
    
	#define DIG4_0_INTTYPE_REG 		(* (reg8 *) DIG4__0__INTTYPE)
#endif /* (DIG4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIG4_H */


/* [] END OF FILE */
