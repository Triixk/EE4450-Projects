/*******************************************************************************
* File Name: Din.h  
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

#if !defined(CY_PINS_Din_H) /* Pins Din_H */
#define CY_PINS_Din_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Din_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Din__PORT == 15 && ((Din__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Din_Write(uint8 value);
void    Din_SetDriveMode(uint8 mode);
uint8   Din_ReadDataReg(void);
uint8   Din_Read(void);
void    Din_SetInterruptMode(uint16 position, uint16 mode);
uint8   Din_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Din_SetDriveMode() function.
     *  @{
     */
        #define Din_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Din_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Din_DM_RES_UP          PIN_DM_RES_UP
        #define Din_DM_RES_DWN         PIN_DM_RES_DWN
        #define Din_DM_OD_LO           PIN_DM_OD_LO
        #define Din_DM_OD_HI           PIN_DM_OD_HI
        #define Din_DM_STRONG          PIN_DM_STRONG
        #define Din_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Din_MASK               Din__MASK
#define Din_SHIFT              Din__SHIFT
#define Din_WIDTH              1u

/* Interrupt constants */
#if defined(Din__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Din_SetInterruptMode() function.
     *  @{
     */
        #define Din_INTR_NONE      (uint16)(0x0000u)
        #define Din_INTR_RISING    (uint16)(0x0001u)
        #define Din_INTR_FALLING   (uint16)(0x0002u)
        #define Din_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Din_INTR_MASK      (0x01u) 
#endif /* (Din__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Din_PS                     (* (reg8 *) Din__PS)
/* Data Register */
#define Din_DR                     (* (reg8 *) Din__DR)
/* Port Number */
#define Din_PRT_NUM                (* (reg8 *) Din__PRT) 
/* Connect to Analog Globals */                                                  
#define Din_AG                     (* (reg8 *) Din__AG)                       
/* Analog MUX bux enable */
#define Din_AMUX                   (* (reg8 *) Din__AMUX) 
/* Bidirectional Enable */                                                        
#define Din_BIE                    (* (reg8 *) Din__BIE)
/* Bit-mask for Aliased Register Access */
#define Din_BIT_MASK               (* (reg8 *) Din__BIT_MASK)
/* Bypass Enable */
#define Din_BYP                    (* (reg8 *) Din__BYP)
/* Port wide control signals */                                                   
#define Din_CTL                    (* (reg8 *) Din__CTL)
/* Drive Modes */
#define Din_DM0                    (* (reg8 *) Din__DM0) 
#define Din_DM1                    (* (reg8 *) Din__DM1)
#define Din_DM2                    (* (reg8 *) Din__DM2) 
/* Input Buffer Disable Override */
#define Din_INP_DIS                (* (reg8 *) Din__INP_DIS)
/* LCD Common or Segment Drive */
#define Din_LCD_COM_SEG            (* (reg8 *) Din__LCD_COM_SEG)
/* Enable Segment LCD */
#define Din_LCD_EN                 (* (reg8 *) Din__LCD_EN)
/* Slew Rate Control */
#define Din_SLW                    (* (reg8 *) Din__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Din_PRTDSI__CAPS_SEL       (* (reg8 *) Din__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Din_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Din__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Din_PRTDSI__OE_SEL0        (* (reg8 *) Din__PRTDSI__OE_SEL0) 
#define Din_PRTDSI__OE_SEL1        (* (reg8 *) Din__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Din_PRTDSI__OUT_SEL0       (* (reg8 *) Din__PRTDSI__OUT_SEL0) 
#define Din_PRTDSI__OUT_SEL1       (* (reg8 *) Din__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Din_PRTDSI__SYNC_OUT       (* (reg8 *) Din__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Din__SIO_CFG)
    #define Din_SIO_HYST_EN        (* (reg8 *) Din__SIO_HYST_EN)
    #define Din_SIO_REG_HIFREQ     (* (reg8 *) Din__SIO_REG_HIFREQ)
    #define Din_SIO_CFG            (* (reg8 *) Din__SIO_CFG)
    #define Din_SIO_DIFF           (* (reg8 *) Din__SIO_DIFF)
#endif /* (Din__SIO_CFG) */

/* Interrupt Registers */
#if defined(Din__INTSTAT)
    #define Din_INTSTAT            (* (reg8 *) Din__INTSTAT)
    #define Din_SNAP               (* (reg8 *) Din__SNAP)
    
	#define Din_0_INTTYPE_REG 		(* (reg8 *) Din__0__INTTYPE)
#endif /* (Din__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Din_H */


/* [] END OF FILE */
