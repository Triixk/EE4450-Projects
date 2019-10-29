/*******************************************************************************
* File Name: DIG3.h  
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

#if !defined(CY_PINS_DIG3_H) /* Pins DIG3_H */
#define CY_PINS_DIG3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIG3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIG3__PORT == 15 && ((DIG3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIG3_Write(uint8 value);
void    DIG3_SetDriveMode(uint8 mode);
uint8   DIG3_ReadDataReg(void);
uint8   DIG3_Read(void);
void    DIG3_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIG3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIG3_SetDriveMode() function.
     *  @{
     */
        #define DIG3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIG3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIG3_DM_RES_UP          PIN_DM_RES_UP
        #define DIG3_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIG3_DM_OD_LO           PIN_DM_OD_LO
        #define DIG3_DM_OD_HI           PIN_DM_OD_HI
        #define DIG3_DM_STRONG          PIN_DM_STRONG
        #define DIG3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIG3_MASK               DIG3__MASK
#define DIG3_SHIFT              DIG3__SHIFT
#define DIG3_WIDTH              1u

/* Interrupt constants */
#if defined(DIG3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIG3_SetInterruptMode() function.
     *  @{
     */
        #define DIG3_INTR_NONE      (uint16)(0x0000u)
        #define DIG3_INTR_RISING    (uint16)(0x0001u)
        #define DIG3_INTR_FALLING   (uint16)(0x0002u)
        #define DIG3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIG3_INTR_MASK      (0x01u) 
#endif /* (DIG3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIG3_PS                     (* (reg8 *) DIG3__PS)
/* Data Register */
#define DIG3_DR                     (* (reg8 *) DIG3__DR)
/* Port Number */
#define DIG3_PRT_NUM                (* (reg8 *) DIG3__PRT) 
/* Connect to Analog Globals */                                                  
#define DIG3_AG                     (* (reg8 *) DIG3__AG)                       
/* Analog MUX bux enable */
#define DIG3_AMUX                   (* (reg8 *) DIG3__AMUX) 
/* Bidirectional Enable */                                                        
#define DIG3_BIE                    (* (reg8 *) DIG3__BIE)
/* Bit-mask for Aliased Register Access */
#define DIG3_BIT_MASK               (* (reg8 *) DIG3__BIT_MASK)
/* Bypass Enable */
#define DIG3_BYP                    (* (reg8 *) DIG3__BYP)
/* Port wide control signals */                                                   
#define DIG3_CTL                    (* (reg8 *) DIG3__CTL)
/* Drive Modes */
#define DIG3_DM0                    (* (reg8 *) DIG3__DM0) 
#define DIG3_DM1                    (* (reg8 *) DIG3__DM1)
#define DIG3_DM2                    (* (reg8 *) DIG3__DM2) 
/* Input Buffer Disable Override */
#define DIG3_INP_DIS                (* (reg8 *) DIG3__INP_DIS)
/* LCD Common or Segment Drive */
#define DIG3_LCD_COM_SEG            (* (reg8 *) DIG3__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIG3_LCD_EN                 (* (reg8 *) DIG3__LCD_EN)
/* Slew Rate Control */
#define DIG3_SLW                    (* (reg8 *) DIG3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIG3_PRTDSI__CAPS_SEL       (* (reg8 *) DIG3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIG3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIG3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIG3_PRTDSI__OE_SEL0        (* (reg8 *) DIG3__PRTDSI__OE_SEL0) 
#define DIG3_PRTDSI__OE_SEL1        (* (reg8 *) DIG3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIG3_PRTDSI__OUT_SEL0       (* (reg8 *) DIG3__PRTDSI__OUT_SEL0) 
#define DIG3_PRTDSI__OUT_SEL1       (* (reg8 *) DIG3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIG3_PRTDSI__SYNC_OUT       (* (reg8 *) DIG3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIG3__SIO_CFG)
    #define DIG3_SIO_HYST_EN        (* (reg8 *) DIG3__SIO_HYST_EN)
    #define DIG3_SIO_REG_HIFREQ     (* (reg8 *) DIG3__SIO_REG_HIFREQ)
    #define DIG3_SIO_CFG            (* (reg8 *) DIG3__SIO_CFG)
    #define DIG3_SIO_DIFF           (* (reg8 *) DIG3__SIO_DIFF)
#endif /* (DIG3__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIG3__INTSTAT)
    #define DIG3_INTSTAT            (* (reg8 *) DIG3__INTSTAT)
    #define DIG3_SNAP               (* (reg8 *) DIG3__SNAP)
    
	#define DIG3_0_INTTYPE_REG 		(* (reg8 *) DIG3__0__INTTYPE)
#endif /* (DIG3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIG3_H */


/* [] END OF FILE */
