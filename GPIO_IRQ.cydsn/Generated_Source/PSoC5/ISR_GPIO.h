/*******************************************************************************
* File Name: ISR_GPIO.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ISR_GPIO_H)
#define CY_ISR_ISR_GPIO_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_GPIO_Start(void);
void ISR_GPIO_StartEx(cyisraddress address);
void ISR_GPIO_Stop(void);

CY_ISR_PROTO(ISR_GPIO_Interrupt);

void ISR_GPIO_SetVector(cyisraddress address);
cyisraddress ISR_GPIO_GetVector(void);

void ISR_GPIO_SetPriority(uint8 priority);
uint8 ISR_GPIO_GetPriority(void);

void ISR_GPIO_Enable(void);
uint8 ISR_GPIO_GetState(void);
void ISR_GPIO_Disable(void);

void ISR_GPIO_SetPending(void);
void ISR_GPIO_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_GPIO ISR. */
#define ISR_GPIO_INTC_VECTOR            ((reg32 *) ISR_GPIO__INTC_VECT)

/* Address of the ISR_GPIO ISR priority. */
#define ISR_GPIO_INTC_PRIOR             ((reg8 *) ISR_GPIO__INTC_PRIOR_REG)

/* Priority of the ISR_GPIO interrupt. */
#define ISR_GPIO_INTC_PRIOR_NUMBER      ISR_GPIO__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_GPIO interrupt. */
#define ISR_GPIO_INTC_SET_EN            ((reg32 *) ISR_GPIO__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_GPIO interrupt. */
#define ISR_GPIO_INTC_CLR_EN            ((reg32 *) ISR_GPIO__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_GPIO interrupt state to pending. */
#define ISR_GPIO_INTC_SET_PD            ((reg32 *) ISR_GPIO__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_GPIO interrupt. */
#define ISR_GPIO_INTC_CLR_PD            ((reg32 *) ISR_GPIO__INTC_CLR_PD_REG)


#endif /* CY_ISR_ISR_GPIO_H */


/* [] END OF FILE */
