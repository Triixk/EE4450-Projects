/*******************************************************************************
* File Name: LEDB.h  
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

#if !defined(CY_PINS_LEDB_H) /* Pins LEDB_H */
#define CY_PINS_LEDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDB__PORT == 15 && ((LEDB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDB_Write(uint8 value);
void    LEDB_SetDriveMode(uint8 mode);
uint8   LEDB_ReadDataReg(void);
uint8   LEDB_Read(void);
void    LEDB_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDB_SetDriveMode() function.
     *  @{
     */
        #define LEDB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDB_DM_RES_UP          PIN_DM_RES_UP
        #define LEDB_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDB_DM_OD_LO           PIN_DM_OD_LO
        #define LEDB_DM_OD_HI           PIN_DM_OD_HI
        #define LEDB_DM_STRONG          PIN_DM_STRONG
        #define LEDB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDB_MASK               LEDB__MASK
#define LEDB_SHIFT              LEDB__SHIFT
#define LEDB_WIDTH              1u

/* Interrupt constants */
#if defined(LEDB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDB_SetInterruptMode() function.
     *  @{
     */
        #define LEDB_INTR_NONE      (uint16)(0x0000u)
        #define LEDB_INTR_RISING    (uint16)(0x0001u)
        #define LEDB_INTR_FALLING   (uint16)(0x0002u)
        #define LEDB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDB_INTR_MASK      (0x01u) 
#endif /* (LEDB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDB_PS                     (* (reg8 *) LEDB__PS)
/* Data Register */
#define LEDB_DR                     (* (reg8 *) LEDB__DR)
/* Port Number */
#define LEDB_PRT_NUM                (* (reg8 *) LEDB__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDB_AG                     (* (reg8 *) LEDB__AG)                       
/* Analog MUX bux enable */
#define LEDB_AMUX                   (* (reg8 *) LEDB__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDB_BIE                    (* (reg8 *) LEDB__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDB_BIT_MASK               (* (reg8 *) LEDB__BIT_MASK)
/* Bypass Enable */
#define LEDB_BYP                    (* (reg8 *) LEDB__BYP)
/* Port wide control signals */                                                   
#define LEDB_CTL                    (* (reg8 *) LEDB__CTL)
/* Drive Modes */
#define LEDB_DM0                    (* (reg8 *) LEDB__DM0) 
#define LEDB_DM1                    (* (reg8 *) LEDB__DM1)
#define LEDB_DM2                    (* (reg8 *) LEDB__DM2) 
/* Input Buffer Disable Override */
#define LEDB_INP_DIS                (* (reg8 *) LEDB__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDB_LCD_COM_SEG            (* (reg8 *) LEDB__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDB_LCD_EN                 (* (reg8 *) LEDB__LCD_EN)
/* Slew Rate Control */
#define LEDB_SLW                    (* (reg8 *) LEDB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDB_PRTDSI__CAPS_SEL       (* (reg8 *) LEDB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDB_PRTDSI__OE_SEL0        (* (reg8 *) LEDB__PRTDSI__OE_SEL0) 
#define LEDB_PRTDSI__OE_SEL1        (* (reg8 *) LEDB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDB_PRTDSI__OUT_SEL0       (* (reg8 *) LEDB__PRTDSI__OUT_SEL0) 
#define LEDB_PRTDSI__OUT_SEL1       (* (reg8 *) LEDB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDB_PRTDSI__SYNC_OUT       (* (reg8 *) LEDB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDB__SIO_CFG)
    #define LEDB_SIO_HYST_EN        (* (reg8 *) LEDB__SIO_HYST_EN)
    #define LEDB_SIO_REG_HIFREQ     (* (reg8 *) LEDB__SIO_REG_HIFREQ)
    #define LEDB_SIO_CFG            (* (reg8 *) LEDB__SIO_CFG)
    #define LEDB_SIO_DIFF           (* (reg8 *) LEDB__SIO_DIFF)
#endif /* (LEDB__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDB__INTSTAT)
    #define LEDB_INTSTAT            (* (reg8 *) LEDB__INTSTAT)
    #define LEDB_SNAP               (* (reg8 *) LEDB__SNAP)
    
	#define LEDB_0_INTTYPE_REG 		(* (reg8 *) LEDB__0__INTTYPE)
#endif /* (LEDB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDB_H */


/* [] END OF FILE */
