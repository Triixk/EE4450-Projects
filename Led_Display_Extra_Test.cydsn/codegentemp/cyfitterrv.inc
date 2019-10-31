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

; Com
Com__0__INTTYPE EQU CYREG_PICU2_INTTYPE3
Com__0__MASK EQU 0x08
Com__0__PC EQU CYREG_PRT2_PC3
Com__0__PORT EQU 2
Com__0__SHIFT EQU 3
Com__1__INTTYPE EQU CYREG_PICU2_INTTYPE4
Com__1__MASK EQU 0x10
Com__1__PC EQU CYREG_PRT2_PC4
Com__1__PORT EQU 2
Com__1__SHIFT EQU 4
Com__2__INTTYPE EQU CYREG_PICU2_INTTYPE5
Com__2__MASK EQU 0x20
Com__2__PC EQU CYREG_PRT2_PC5
Com__2__PORT EQU 2
Com__2__SHIFT EQU 5
Com__3__INTTYPE EQU CYREG_PICU2_INTTYPE6
Com__3__MASK EQU 0x40
Com__3__PC EQU CYREG_PRT2_PC6
Com__3__PORT EQU 2
Com__3__SHIFT EQU 6
Com__AG EQU CYREG_PRT2_AG
Com__AMUX EQU CYREG_PRT2_AMUX
Com__BIE EQU CYREG_PRT2_BIE
Com__BIT_MASK EQU CYREG_PRT2_BIT_MASK
Com__BYP EQU CYREG_PRT2_BYP
Com__CTL EQU CYREG_PRT2_CTL
Com__DM0 EQU CYREG_PRT2_DM0
Com__DM1 EQU CYREG_PRT2_DM1
Com__DM2 EQU CYREG_PRT2_DM2
Com__DR EQU CYREG_PRT2_DR
Com__INP_DIS EQU CYREG_PRT2_INP_DIS
Com__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
Com__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
Com__LCD_EN EQU CYREG_PRT2_LCD_EN
Com__PORT EQU 2
Com__PRT EQU CYREG_PRT2_PRT
Com__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
Com__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
Com__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
Com__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
Com__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
Com__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
Com__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
Com__PS EQU CYREG_PRT2_PS
Com__SLW EQU CYREG_PRT2_SLW

; LCD
LCD_ClkInternal__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
LCD_ClkInternal__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
LCD_ClkInternal__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
LCD_ClkInternal__CFG2_SRC_SEL_MASK EQU 0x07
LCD_ClkInternal__INDEX EQU 0x00
LCD_ClkInternal__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
LCD_ClkInternal__PM_ACT_MSK EQU 0x01
LCD_ClkInternal__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
LCD_ClkInternal__PM_STBY_MSK EQU 0x01
LCD_Com_Driver_Sync_ctrl_reg__0__MASK EQU 0x01
LCD_Com_Driver_Sync_ctrl_reg__0__POS EQU 0
LCD_Com_Driver_Sync_ctrl_reg__1__MASK EQU 0x02
LCD_Com_Driver_Sync_ctrl_reg__1__POS EQU 1
LCD_Com_Driver_Sync_ctrl_reg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB07_08_ACTL
LCD_Com_Driver_Sync_ctrl_reg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB07_08_CTL
LCD_Com_Driver_Sync_ctrl_reg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB07_08_CTL
LCD_Com_Driver_Sync_ctrl_reg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB07_08_CTL
LCD_Com_Driver_Sync_ctrl_reg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB07_08_CTL
LCD_Com_Driver_Sync_ctrl_reg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB07_08_MSK
LCD_Com_Driver_Sync_ctrl_reg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB07_08_MSK
LCD_Com_Driver_Sync_ctrl_reg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB07_08_MSK
LCD_Com_Driver_Sync_ctrl_reg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB07_08_MSK
LCD_Com_Driver_Sync_ctrl_reg__2__MASK EQU 0x04
LCD_Com_Driver_Sync_ctrl_reg__2__POS EQU 2
LCD_Com_Driver_Sync_ctrl_reg__3__MASK EQU 0x08
LCD_Com_Driver_Sync_ctrl_reg__3__POS EQU 3
LCD_Com_Driver_Sync_ctrl_reg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB07_ACTL
LCD_Com_Driver_Sync_ctrl_reg__CONTROL_REG EQU CYREG_B0_UDB07_CTL
LCD_Com_Driver_Sync_ctrl_reg__CONTROL_ST_REG EQU CYREG_B0_UDB07_ST_CTL
LCD_Com_Driver_Sync_ctrl_reg__COUNT_REG EQU CYREG_B0_UDB07_CTL
LCD_Com_Driver_Sync_ctrl_reg__COUNT_ST_REG EQU CYREG_B0_UDB07_ST_CTL
LCD_Com_Driver_Sync_ctrl_reg__MASK EQU 0x0F
LCD_Com_Driver_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB07_MSK_ACTL
LCD_Com_Driver_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB07_MSK_ACTL
LCD_Com_Driver_Sync_ctrl_reg__PERIOD_REG EQU CYREG_B0_UDB07_MSK
LCD_DMA_Com__DRQ_CTL EQU CYREG_IDMUX_DRQ_CTL0
LCD_DMA_Com__DRQ_NUMBER EQU 0
LCD_DMA_Com__NUMBEROF_TDS EQU 0
LCD_DMA_Com__PRIORITY EQU 2
LCD_DMA_Com__TERMIN_EN EQU 0
LCD_DMA_Com__TERMIN_SEL EQU 0
LCD_DMA_Com__TERMOUT0_EN EQU 1
LCD_DMA_Com__TERMOUT0_SEL EQU 0
LCD_DMA_Com__TERMOUT1_EN EQU 0
LCD_DMA_Com__TERMOUT1_SEL EQU 0
LCD_DMA_Seg__DRQ_CTL EQU CYREG_IDMUX_DRQ_CTL0
LCD_DMA_Seg__DRQ_NUMBER EQU 1
LCD_DMA_Seg__NUMBEROF_TDS EQU 0
LCD_DMA_Seg__PRIORITY EQU 2
LCD_DMA_Seg__TERMIN_EN EQU 0
LCD_DMA_Seg__TERMIN_SEL EQU 0
LCD_DMA_Seg__TERMOUT0_EN EQU 1
LCD_DMA_Seg__TERMOUT0_SEL EQU 1
LCD_DMA_Seg__TERMOUT1_EN EQU 0
LCD_DMA_Seg__TERMOUT1_SEL EQU 0
LCD_Seg_Driver_L_Sync_ctrl_reg__0__MASK EQU 0x01
LCD_Seg_Driver_L_Sync_ctrl_reg__0__POS EQU 0
LCD_Seg_Driver_L_Sync_ctrl_reg__1__MASK EQU 0x02
LCD_Seg_Driver_L_Sync_ctrl_reg__1__POS EQU 1
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB06_07_ACTL
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB06_07_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB06_07_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB06_07_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB06_07_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB06_07_MSK
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB06_07_MSK
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB06_07_MSK
LCD_Seg_Driver_L_Sync_ctrl_reg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB06_07_MSK
LCD_Seg_Driver_L_Sync_ctrl_reg__2__MASK EQU 0x04
LCD_Seg_Driver_L_Sync_ctrl_reg__2__POS EQU 2
LCD_Seg_Driver_L_Sync_ctrl_reg__3__MASK EQU 0x08
LCD_Seg_Driver_L_Sync_ctrl_reg__3__POS EQU 3
LCD_Seg_Driver_L_Sync_ctrl_reg__4__MASK EQU 0x10
LCD_Seg_Driver_L_Sync_ctrl_reg__4__POS EQU 4
LCD_Seg_Driver_L_Sync_ctrl_reg__5__MASK EQU 0x20
LCD_Seg_Driver_L_Sync_ctrl_reg__5__POS EQU 5
LCD_Seg_Driver_L_Sync_ctrl_reg__6__MASK EQU 0x40
LCD_Seg_Driver_L_Sync_ctrl_reg__6__POS EQU 6
LCD_Seg_Driver_L_Sync_ctrl_reg__7__MASK EQU 0x80
LCD_Seg_Driver_L_Sync_ctrl_reg__7__POS EQU 7
LCD_Seg_Driver_L_Sync_ctrl_reg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB06_ACTL
LCD_Seg_Driver_L_Sync_ctrl_reg__CONTROL_REG EQU CYREG_B0_UDB06_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__CONTROL_ST_REG EQU CYREG_B0_UDB06_ST_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__COUNT_REG EQU CYREG_B0_UDB06_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__COUNT_ST_REG EQU CYREG_B0_UDB06_ST_CTL
LCD_Seg_Driver_L_Sync_ctrl_reg__MASK EQU 0xFF
LCD_Seg_Driver_L_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB06_MSK_ACTL
LCD_Seg_Driver_L_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB06_MSK_ACTL
LCD_Seg_Driver_L_Sync_ctrl_reg__PERIOD_REG EQU CYREG_B0_UDB06_MSK

; Seg
Seg__0__INTTYPE EQU CYREG_PICU12_INTTYPE0
Seg__0__MASK EQU 0x01
Seg__0__PC EQU CYREG_PRT12_PC0
Seg__0__PORT EQU 12
Seg__0__SHIFT EQU 0
Seg__1__INTTYPE EQU CYREG_PICU12_INTTYPE1
Seg__1__MASK EQU 0x02
Seg__1__PC EQU CYREG_PRT12_PC1
Seg__1__PORT EQU 12
Seg__1__SHIFT EQU 1
Seg__2__INTTYPE EQU CYREG_PICU12_INTTYPE2
Seg__2__MASK EQU 0x04
Seg__2__PC EQU CYREG_PRT12_PC2
Seg__2__PORT EQU 12
Seg__2__SHIFT EQU 2
Seg__3__INTTYPE EQU CYREG_PICU12_INTTYPE3
Seg__3__MASK EQU 0x08
Seg__3__PC EQU CYREG_PRT12_PC3
Seg__3__PORT EQU 12
Seg__3__SHIFT EQU 3
Seg__4__INTTYPE EQU CYREG_PICU12_INTTYPE4
Seg__4__MASK EQU 0x10
Seg__4__PC EQU CYREG_PRT12_PC4
Seg__4__PORT EQU 12
Seg__4__SHIFT EQU 4
Seg__5__INTTYPE EQU CYREG_PICU12_INTTYPE5
Seg__5__MASK EQU 0x20
Seg__5__PC EQU CYREG_PRT12_PC5
Seg__5__PORT EQU 12
Seg__5__SHIFT EQU 5
Seg__6__INTTYPE EQU CYREG_PICU12_INTTYPE6
Seg__6__MASK EQU 0x40
Seg__6__PC EQU CYREG_PRT12_PC6
Seg__6__PORT EQU 12
Seg__6__SHIFT EQU 6
Seg__7__INTTYPE EQU CYREG_PICU12_INTTYPE7
Seg__7__MASK EQU 0x80
Seg__7__PC EQU CYREG_PRT12_PC7
Seg__7__PORT EQU 12
Seg__7__SHIFT EQU 7
Seg__AG EQU CYREG_PRT12_AG
Seg__BIE EQU CYREG_PRT12_BIE
Seg__BIT_MASK EQU CYREG_PRT12_BIT_MASK
Seg__BYP EQU CYREG_PRT12_BYP
Seg__DM0 EQU CYREG_PRT12_DM0
Seg__DM1 EQU CYREG_PRT12_DM1
Seg__DM2 EQU CYREG_PRT12_DM2
Seg__DR EQU CYREG_PRT12_DR
Seg__INP_DIS EQU CYREG_PRT12_INP_DIS
Seg__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
Seg__PORT EQU 12
Seg__PRT EQU CYREG_PRT12_PRT
Seg__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
Seg__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
Seg__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
Seg__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
Seg__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
Seg__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
Seg__PS EQU CYREG_PRT12_PS
Seg__SIO_CFG EQU CYREG_PRT12_SIO_CFG
Seg__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
Seg__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
Seg__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
Seg__SLW EQU CYREG_PRT12_SLW

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

; LED_Board
LED_Board__0__INTTYPE EQU CYREG_PICU2_INTTYPE1
LED_Board__0__MASK EQU 0x02
LED_Board__0__PC EQU CYREG_PRT2_PC1
LED_Board__0__PORT EQU 2
LED_Board__0__SHIFT EQU 1
LED_Board__AG EQU CYREG_PRT2_AG
LED_Board__AMUX EQU CYREG_PRT2_AMUX
LED_Board__BIE EQU CYREG_PRT2_BIE
LED_Board__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LED_Board__BYP EQU CYREG_PRT2_BYP
LED_Board__CTL EQU CYREG_PRT2_CTL
LED_Board__DM0 EQU CYREG_PRT2_DM0
LED_Board__DM1 EQU CYREG_PRT2_DM1
LED_Board__DM2 EQU CYREG_PRT2_DM2
LED_Board__DR EQU CYREG_PRT2_DR
LED_Board__INP_DIS EQU CYREG_PRT2_INP_DIS
LED_Board__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
LED_Board__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LED_Board__LCD_EN EQU CYREG_PRT2_LCD_EN
LED_Board__MASK EQU 0x02
LED_Board__PORT EQU 2
LED_Board__PRT EQU CYREG_PRT2_PRT
LED_Board__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LED_Board__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LED_Board__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LED_Board__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LED_Board__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LED_Board__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LED_Board__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LED_Board__PS EQU CYREG_PRT2_PS
LED_Board__SHIFT EQU 1
LED_Board__SLW EQU CYREG_PRT2_SLW

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
DMA_CHANNELS_USED__MASK0 EQU 0x00000003
CYDEV_BOOTLOADER_ENABLE EQU 0
    ENDIF
    END