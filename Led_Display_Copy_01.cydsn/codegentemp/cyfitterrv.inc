;
; File Name: cyfitterrv.inc
; 
; PSoC Creator  4.2
;
; Description:
; 
;
;-------------------------------------------------------------------------------
; Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

    IF :LNOT::DEF:INCLUDED_CYFITTERRV_INC
INCLUDED_CYFITTERRV_INC EQU 1
    GET cydevicerv.inc
    GET cydevicerv_trm.inc

; nSW
nSW__0__INTTYPE EQU CYREG_PICU2_INTTYPE2
nSW__0__MASK EQU 0x04
nSW__0__PC EQU CYREG_PRT2_PC2
nSW__0__PORT EQU 2
nSW__0__SHIFT EQU 2
nSW__AG EQU CYREG_PRT2_AG
nSW__AMUX EQU CYREG_PRT2_AMUX
nSW__BIE EQU CYREG_PRT2_BIE
nSW__BIT_MASK EQU CYREG_PRT2_BIT_MASK
nSW__BYP EQU CYREG_PRT2_BYP
nSW__CTL EQU CYREG_PRT2_CTL
nSW__DM0 EQU CYREG_PRT2_DM0
nSW__DM1 EQU CYREG_PRT2_DM1
nSW__DM2 EQU CYREG_PRT2_DM2
nSW__DR EQU CYREG_PRT2_DR
nSW__INP_DIS EQU CYREG_PRT2_INP_DIS
nSW__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
nSW__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
nSW__LCD_EN EQU CYREG_PRT2_LCD_EN
nSW__MASK EQU 0x04
nSW__PORT EQU 2
nSW__PRT EQU CYREG_PRT2_PRT
nSW__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
nSW__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
nSW__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
nSW__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
nSW__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
nSW__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
nSW__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
nSW__PS EQU CYREG_PRT2_PS
nSW__SHIFT EQU 2
nSW__SLW EQU CYREG_PRT2_SLW

; DIG1
DIG1__0__INTTYPE EQU CYREG_PICU2_INTTYPE3
DIG1__0__MASK EQU 0x08
DIG1__0__PC EQU CYREG_PRT2_PC3
DIG1__0__PORT EQU 2
DIG1__0__SHIFT EQU 3
DIG1__AG EQU CYREG_PRT2_AG
DIG1__AMUX EQU CYREG_PRT2_AMUX
DIG1__BIE EQU CYREG_PRT2_BIE
DIG1__BIT_MASK EQU CYREG_PRT2_BIT_MASK
DIG1__BYP EQU CYREG_PRT2_BYP
DIG1__CTL EQU CYREG_PRT2_CTL
DIG1__DM0 EQU CYREG_PRT2_DM0
DIG1__DM1 EQU CYREG_PRT2_DM1
DIG1__DM2 EQU CYREG_PRT2_DM2
DIG1__DR EQU CYREG_PRT2_DR
DIG1__INP_DIS EQU CYREG_PRT2_INP_DIS
DIG1__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
DIG1__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
DIG1__LCD_EN EQU CYREG_PRT2_LCD_EN
DIG1__MASK EQU 0x08
DIG1__PORT EQU 2
DIG1__PRT EQU CYREG_PRT2_PRT
DIG1__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
DIG1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
DIG1__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
DIG1__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
DIG1__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
DIG1__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
DIG1__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
DIG1__PS EQU CYREG_PRT2_PS
DIG1__SHIFT EQU 3
DIG1__SLW EQU CYREG_PRT2_SLW

; DIG2
DIG2__0__INTTYPE EQU CYREG_PICU2_INTTYPE4
DIG2__0__MASK EQU 0x10
DIG2__0__PC EQU CYREG_PRT2_PC4
DIG2__0__PORT EQU 2
DIG2__0__SHIFT EQU 4
DIG2__AG EQU CYREG_PRT2_AG
DIG2__AMUX EQU CYREG_PRT2_AMUX
DIG2__BIE EQU CYREG_PRT2_BIE
DIG2__BIT_MASK EQU CYREG_PRT2_BIT_MASK
DIG2__BYP EQU CYREG_PRT2_BYP
DIG2__CTL EQU CYREG_PRT2_CTL
DIG2__DM0 EQU CYREG_PRT2_DM0
DIG2__DM1 EQU CYREG_PRT2_DM1
DIG2__DM2 EQU CYREG_PRT2_DM2
DIG2__DR EQU CYREG_PRT2_DR
DIG2__INP_DIS EQU CYREG_PRT2_INP_DIS
DIG2__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
DIG2__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
DIG2__LCD_EN EQU CYREG_PRT2_LCD_EN
DIG2__MASK EQU 0x10
DIG2__PORT EQU 2
DIG2__PRT EQU CYREG_PRT2_PRT
DIG2__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
DIG2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
DIG2__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
DIG2__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
DIG2__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
DIG2__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
DIG2__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
DIG2__PS EQU CYREG_PRT2_PS
DIG2__SHIFT EQU 4
DIG2__SLW EQU CYREG_PRT2_SLW

; DIG3
DIG3__0__INTTYPE EQU CYREG_PICU2_INTTYPE5
DIG3__0__MASK EQU 0x20
DIG3__0__PC EQU CYREG_PRT2_PC5
DIG3__0__PORT EQU 2
DIG3__0__SHIFT EQU 5
DIG3__AG EQU CYREG_PRT2_AG
DIG3__AMUX EQU CYREG_PRT2_AMUX
DIG3__BIE EQU CYREG_PRT2_BIE
DIG3__BIT_MASK EQU CYREG_PRT2_BIT_MASK
DIG3__BYP EQU CYREG_PRT2_BYP
DIG3__CTL EQU CYREG_PRT2_CTL
DIG3__DM0 EQU CYREG_PRT2_DM0
DIG3__DM1 EQU CYREG_PRT2_DM1
DIG3__DM2 EQU CYREG_PRT2_DM2
DIG3__DR EQU CYREG_PRT2_DR
DIG3__INP_DIS EQU CYREG_PRT2_INP_DIS
DIG3__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
DIG3__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
DIG3__LCD_EN EQU CYREG_PRT2_LCD_EN
DIG3__MASK EQU 0x20
DIG3__PORT EQU 2
DIG3__PRT EQU CYREG_PRT2_PRT
DIG3__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
DIG3__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
DIG3__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
DIG3__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
DIG3__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
DIG3__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
DIG3__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
DIG3__PS EQU CYREG_PRT2_PS
DIG3__SHIFT EQU 5
DIG3__SLW EQU CYREG_PRT2_SLW

; DIG4
DIG4__0__INTTYPE EQU CYREG_PICU2_INTTYPE6
DIG4__0__MASK EQU 0x40
DIG4__0__PC EQU CYREG_PRT2_PC6
DIG4__0__PORT EQU 2
DIG4__0__SHIFT EQU 6
DIG4__AG EQU CYREG_PRT2_AG
DIG4__AMUX EQU CYREG_PRT2_AMUX
DIG4__BIE EQU CYREG_PRT2_BIE
DIG4__BIT_MASK EQU CYREG_PRT2_BIT_MASK
DIG4__BYP EQU CYREG_PRT2_BYP
DIG4__CTL EQU CYREG_PRT2_CTL
DIG4__DM0 EQU CYREG_PRT2_DM0
DIG4__DM1 EQU CYREG_PRT2_DM1
DIG4__DM2 EQU CYREG_PRT2_DM2
DIG4__DR EQU CYREG_PRT2_DR
DIG4__INP_DIS EQU CYREG_PRT2_INP_DIS
DIG4__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
DIG4__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
DIG4__LCD_EN EQU CYREG_PRT2_LCD_EN
DIG4__MASK EQU 0x40
DIG4__PORT EQU 2
DIG4__PRT EQU CYREG_PRT2_PRT
DIG4__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
DIG4__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
DIG4__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
DIG4__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
DIG4__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
DIG4__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
DIG4__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
DIG4__PS EQU CYREG_PRT2_PS
DIG4__SHIFT EQU 6
DIG4__SLW EQU CYREG_PRT2_SLW

; LEDA
LEDA__0__INTTYPE EQU CYREG_PICU12_INTTYPE0
LEDA__0__MASK EQU 0x01
LEDA__0__PC EQU CYREG_PRT12_PC0
LEDA__0__PORT EQU 12
LEDA__0__SHIFT EQU 0
LEDA__AG EQU CYREG_PRT12_AG
LEDA__BIE EQU CYREG_PRT12_BIE
LEDA__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDA__BYP EQU CYREG_PRT12_BYP
LEDA__DM0 EQU CYREG_PRT12_DM0
LEDA__DM1 EQU CYREG_PRT12_DM1
LEDA__DM2 EQU CYREG_PRT12_DM2
LEDA__DR EQU CYREG_PRT12_DR
LEDA__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDA__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDA__MASK EQU 0x01
LEDA__PORT EQU 12
LEDA__PRT EQU CYREG_PRT12_PRT
LEDA__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDA__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDA__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDA__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDA__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDA__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDA__PS EQU CYREG_PRT12_PS
LEDA__SHIFT EQU 0
LEDA__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDA__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDA__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDA__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDA__SLW EQU CYREG_PRT12_SLW

; LEDB
LEDB__0__INTTYPE EQU CYREG_PICU12_INTTYPE1
LEDB__0__MASK EQU 0x02
LEDB__0__PC EQU CYREG_PRT12_PC1
LEDB__0__PORT EQU 12
LEDB__0__SHIFT EQU 1
LEDB__AG EQU CYREG_PRT12_AG
LEDB__BIE EQU CYREG_PRT12_BIE
LEDB__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDB__BYP EQU CYREG_PRT12_BYP
LEDB__DM0 EQU CYREG_PRT12_DM0
LEDB__DM1 EQU CYREG_PRT12_DM1
LEDB__DM2 EQU CYREG_PRT12_DM2
LEDB__DR EQU CYREG_PRT12_DR
LEDB__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDB__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDB__MASK EQU 0x02
LEDB__PORT EQU 12
LEDB__PRT EQU CYREG_PRT12_PRT
LEDB__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDB__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDB__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDB__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDB__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDB__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDB__PS EQU CYREG_PRT12_PS
LEDB__SHIFT EQU 1
LEDB__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDB__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDB__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDB__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDB__SLW EQU CYREG_PRT12_SLW

; LEDC
LEDC__0__INTTYPE EQU CYREG_PICU12_INTTYPE2
LEDC__0__MASK EQU 0x04
LEDC__0__PC EQU CYREG_PRT12_PC2
LEDC__0__PORT EQU 12
LEDC__0__SHIFT EQU 2
LEDC__AG EQU CYREG_PRT12_AG
LEDC__BIE EQU CYREG_PRT12_BIE
LEDC__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDC__BYP EQU CYREG_PRT12_BYP
LEDC__DM0 EQU CYREG_PRT12_DM0
LEDC__DM1 EQU CYREG_PRT12_DM1
LEDC__DM2 EQU CYREG_PRT12_DM2
LEDC__DR EQU CYREG_PRT12_DR
LEDC__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDC__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDC__MASK EQU 0x04
LEDC__PORT EQU 12
LEDC__PRT EQU CYREG_PRT12_PRT
LEDC__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDC__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDC__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDC__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDC__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDC__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDC__PS EQU CYREG_PRT12_PS
LEDC__SHIFT EQU 2
LEDC__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDC__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDC__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDC__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDC__SLW EQU CYREG_PRT12_SLW

; LEDD
LEDD__0__INTTYPE EQU CYREG_PICU12_INTTYPE3
LEDD__0__MASK EQU 0x08
LEDD__0__PC EQU CYREG_PRT12_PC3
LEDD__0__PORT EQU 12
LEDD__0__SHIFT EQU 3
LEDD__AG EQU CYREG_PRT12_AG
LEDD__BIE EQU CYREG_PRT12_BIE
LEDD__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDD__BYP EQU CYREG_PRT12_BYP
LEDD__DM0 EQU CYREG_PRT12_DM0
LEDD__DM1 EQU CYREG_PRT12_DM1
LEDD__DM2 EQU CYREG_PRT12_DM2
LEDD__DR EQU CYREG_PRT12_DR
LEDD__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDD__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDD__MASK EQU 0x08
LEDD__PORT EQU 12
LEDD__PRT EQU CYREG_PRT12_PRT
LEDD__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDD__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDD__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDD__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDD__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDD__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDD__PS EQU CYREG_PRT12_PS
LEDD__SHIFT EQU 3
LEDD__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDD__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDD__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDD__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDD__SLW EQU CYREG_PRT12_SLW

; LEDE
LEDE__0__INTTYPE EQU CYREG_PICU12_INTTYPE5
LEDE__0__MASK EQU 0x20
LEDE__0__PC EQU CYREG_PRT12_PC5
LEDE__0__PORT EQU 12
LEDE__0__SHIFT EQU 5
LEDE__AG EQU CYREG_PRT12_AG
LEDE__BIE EQU CYREG_PRT12_BIE
LEDE__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDE__BYP EQU CYREG_PRT12_BYP
LEDE__DM0 EQU CYREG_PRT12_DM0
LEDE__DM1 EQU CYREG_PRT12_DM1
LEDE__DM2 EQU CYREG_PRT12_DM2
LEDE__DR EQU CYREG_PRT12_DR
LEDE__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDE__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDE__MASK EQU 0x20
LEDE__PORT EQU 12
LEDE__PRT EQU CYREG_PRT12_PRT
LEDE__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDE__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDE__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDE__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDE__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDE__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDE__PS EQU CYREG_PRT12_PS
LEDE__SHIFT EQU 5
LEDE__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDE__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDE__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDE__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDE__SLW EQU CYREG_PRT12_SLW

; LEDF
LEDF__0__INTTYPE EQU CYREG_PICU12_INTTYPE6
LEDF__0__MASK EQU 0x40
LEDF__0__PC EQU CYREG_PRT12_PC6
LEDF__0__PORT EQU 12
LEDF__0__SHIFT EQU 6
LEDF__AG EQU CYREG_PRT12_AG
LEDF__BIE EQU CYREG_PRT12_BIE
LEDF__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDF__BYP EQU CYREG_PRT12_BYP
LEDF__DM0 EQU CYREG_PRT12_DM0
LEDF__DM1 EQU CYREG_PRT12_DM1
LEDF__DM2 EQU CYREG_PRT12_DM2
LEDF__DR EQU CYREG_PRT12_DR
LEDF__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDF__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDF__MASK EQU 0x40
LEDF__PORT EQU 12
LEDF__PRT EQU CYREG_PRT12_PRT
LEDF__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDF__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDF__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDF__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDF__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDF__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDF__PS EQU CYREG_PRT12_PS
LEDF__SHIFT EQU 6
LEDF__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDF__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDF__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDF__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDF__SLW EQU CYREG_PRT12_SLW

; LEDG
LEDG__0__INTTYPE EQU CYREG_PICU12_INTTYPE7
LEDG__0__MASK EQU 0x80
LEDG__0__PC EQU CYREG_PRT12_PC7
LEDG__0__PORT EQU 12
LEDG__0__SHIFT EQU 7
LEDG__AG EQU CYREG_PRT12_AG
LEDG__BIE EQU CYREG_PRT12_BIE
LEDG__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDG__BYP EQU CYREG_PRT12_BYP
LEDG__DM0 EQU CYREG_PRT12_DM0
LEDG__DM1 EQU CYREG_PRT12_DM1
LEDG__DM2 EQU CYREG_PRT12_DM2
LEDG__DR EQU CYREG_PRT12_DR
LEDG__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDG__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDG__MASK EQU 0x80
LEDG__PORT EQU 12
LEDG__PRT EQU CYREG_PRT12_PRT
LEDG__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDG__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDG__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDG__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDG__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDG__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDG__PS EQU CYREG_PRT12_PS
LEDG__SHIFT EQU 7
LEDG__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDG__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDG__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDG__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDG__SLW EQU CYREG_PRT12_SLW

; LEDDP
LEDDP__0__INTTYPE EQU CYREG_PICU12_INTTYPE4
LEDDP__0__MASK EQU 0x10
LEDDP__0__PC EQU CYREG_PRT12_PC4
LEDDP__0__PORT EQU 12
LEDDP__0__SHIFT EQU 4
LEDDP__AG EQU CYREG_PRT12_AG
LEDDP__BIE EQU CYREG_PRT12_BIE
LEDDP__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LEDDP__BYP EQU CYREG_PRT12_BYP
LEDDP__DM0 EQU CYREG_PRT12_DM0
LEDDP__DM1 EQU CYREG_PRT12_DM1
LEDDP__DM2 EQU CYREG_PRT12_DM2
LEDDP__DR EQU CYREG_PRT12_DR
LEDDP__INP_DIS EQU CYREG_PRT12_INP_DIS
LEDDP__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
LEDDP__MASK EQU 0x10
LEDDP__PORT EQU 12
LEDDP__PRT EQU CYREG_PRT12_PRT
LEDDP__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LEDDP__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LEDDP__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LEDDP__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LEDDP__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LEDDP__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LEDDP__PS EQU CYREG_PRT12_PS
LEDDP__SHIFT EQU 4
LEDDP__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LEDDP__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LEDDP__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LEDDP__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LEDDP__SLW EQU CYREG_PRT12_SLW

; Miscellaneous
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PSOC4A EQU 21
CYDEV_CHIP_DIE_PSOC5LP EQU 2
CYDEV_CHIP_DIE_PSOC5TM EQU 3
CYDEV_CHIP_DIE_TMA4 EQU 4
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_FM0P EQU 5
CYDEV_CHIP_FAMILY_FM3 EQU 6
CYDEV_CHIP_FAMILY_FM4 EQU 7
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_PSOC6 EQU 4
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E161069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 21
CYDEV_CHIP_MEMBER_4D EQU 16
CYDEV_CHIP_MEMBER_4E EQU 6
CYDEV_CHIP_MEMBER_4F EQU 22
CYDEV_CHIP_MEMBER_4G EQU 4
CYDEV_CHIP_MEMBER_4H EQU 20
CYDEV_CHIP_MEMBER_4I EQU 26
CYDEV_CHIP_MEMBER_4J EQU 17
CYDEV_CHIP_MEMBER_4K EQU 18
CYDEV_CHIP_MEMBER_4L EQU 25
CYDEV_CHIP_MEMBER_4M EQU 24
CYDEV_CHIP_MEMBER_4N EQU 11
CYDEV_CHIP_MEMBER_4O EQU 8
CYDEV_CHIP_MEMBER_4P EQU 23
CYDEV_CHIP_MEMBER_4Q EQU 14
CYDEV_CHIP_MEMBER_4R EQU 9
CYDEV_CHIP_MEMBER_4S EQU 12
CYDEV_CHIP_MEMBER_4T EQU 10
CYDEV_CHIP_MEMBER_4U EQU 5
CYDEV_CHIP_MEMBER_4V EQU 19
CYDEV_CHIP_MEMBER_4W EQU 13
CYDEV_CHIP_MEMBER_4X EQU 7
CYDEV_CHIP_MEMBER_4Y EQU 15
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_5B EQU 2
CYDEV_CHIP_MEMBER_6A EQU 27
CYDEV_CHIP_MEMBER_FM3 EQU 31
CYDEV_CHIP_MEMBER_FM4 EQU 32
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 EQU 28
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 EQU 29
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 EQU 30
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES1 EQU 1
CYDEV_CHIP_REV_PSOC5TM_PRODUCTION EQU 1
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4O_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4P_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Q_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4R_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4S_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4T_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4V_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4W_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4X_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Y_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_6A_ES EQU 17
CYDEV_CHIP_REVISION_6A_NO_UDB EQU 33
CYDEV_CHIP_REVISION_6A_PRODUCTION EQU 33
CYDEV_CHIP_REVISION_FM3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_FM4_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x80
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000000
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x0800
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0
    ENDIF
    END
