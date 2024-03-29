;
; File Name: cyfitteriar.inc
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

#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* LED */
LED__0__INTTYPE EQU CYREG_PICU2_INTTYPE1
LED__0__MASK EQU 0x02
LED__0__PC EQU CYREG_PRT2_PC1
LED__0__PORT EQU 2
LED__0__SHIFT EQU 1
LED__AG EQU CYREG_PRT2_AG
LED__AMUX EQU CYREG_PRT2_AMUX
LED__BIE EQU CYREG_PRT2_BIE
LED__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LED__BYP EQU CYREG_PRT2_BYP
LED__CTL EQU CYREG_PRT2_CTL
LED__DM0 EQU CYREG_PRT2_DM0
LED__DM1 EQU CYREG_PRT2_DM1
LED__DM2 EQU CYREG_PRT2_DM2
LED__DR EQU CYREG_PRT2_DR
LED__INP_DIS EQU CYREG_PRT2_INP_DIS
LED__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
LED__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LED__LCD_EN EQU CYREG_PRT2_LCD_EN
LED__MASK EQU 0x02
LED__PORT EQU 2
LED__PRT EQU CYREG_PRT2_PRT
LED__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LED__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LED__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LED__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LED__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LED__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LED__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LED__PS EQU CYREG_PRT2_PS
LED__SHIFT EQU 1
LED__SLW EQU CYREG_PRT2_SLW

/* PWM */
PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB12_13_ACTL
PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB12_13_CTL
PWM_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB12_13_CTL
PWM_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB12_13_CTL
PWM_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB12_13_CTL
PWM_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB12_13_MSK
PWM_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB12_13_MSK
PWM_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB12_13_MSK
PWM_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB12_13_MSK
PWM_PWMUDB_genblk1_ctrlreg__7__MASK EQU 0x80
PWM_PWMUDB_genblk1_ctrlreg__7__POS EQU 7
PWM_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB12_ACTL
PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG EQU CYREG_B0_UDB12_CTL
PWM_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG EQU CYREG_B0_UDB12_ST_CTL
PWM_PWMUDB_genblk1_ctrlreg__COUNT_REG EQU CYREG_B0_UDB12_CTL
PWM_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG EQU CYREG_B0_UDB12_ST_CTL
PWM_PWMUDB_genblk1_ctrlreg__MASK EQU 0x80
PWM_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB12_MSK_ACTL
PWM_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB12_MSK_ACTL
PWM_PWMUDB_genblk1_ctrlreg__PERIOD_REG EQU CYREG_B0_UDB12_MSK
PWM_PWMUDB_genblk8_stsreg__0__MASK EQU 0x01
PWM_PWMUDB_genblk8_stsreg__0__POS EQU 0
PWM_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB12_13_ACTL
PWM_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG EQU CYREG_B0_UDB12_13_ST
PWM_PWMUDB_genblk8_stsreg__2__MASK EQU 0x04
PWM_PWMUDB_genblk8_stsreg__2__POS EQU 2
PWM_PWMUDB_genblk8_stsreg__3__MASK EQU 0x08
PWM_PWMUDB_genblk8_stsreg__3__POS EQU 3
PWM_PWMUDB_genblk8_stsreg__MASK EQU 0x0D
PWM_PWMUDB_genblk8_stsreg__MASK_REG EQU CYREG_B0_UDB12_MSK
PWM_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB12_MSK_ACTL
PWM_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB12_MSK_ACTL
PWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB12_ACTL
PWM_PWMUDB_genblk8_stsreg__STATUS_CNT_REG EQU CYREG_B0_UDB12_ST_CTL
PWM_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG EQU CYREG_B0_UDB12_ST_CTL
PWM_PWMUDB_genblk8_stsreg__STATUS_REG EQU CYREG_B0_UDB12_ST
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB11_12_A0
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB11_12_A1
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB11_12_D0
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB11_12_D1
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB11_12_ACTL
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB11_12_F0
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB11_12_F1
PWM_PWMUDB_sP8_pwmdp_u0__A0_A1_REG EQU CYREG_B0_UDB11_A0_A1
PWM_PWMUDB_sP8_pwmdp_u0__A0_REG EQU CYREG_B0_UDB11_A0
PWM_PWMUDB_sP8_pwmdp_u0__A1_REG EQU CYREG_B0_UDB11_A1
PWM_PWMUDB_sP8_pwmdp_u0__D0_D1_REG EQU CYREG_B0_UDB11_D0_D1
PWM_PWMUDB_sP8_pwmdp_u0__D0_REG EQU CYREG_B0_UDB11_D0
PWM_PWMUDB_sP8_pwmdp_u0__D1_REG EQU CYREG_B0_UDB11_D1
PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB11_ACTL
PWM_PWMUDB_sP8_pwmdp_u0__F0_F1_REG EQU CYREG_B0_UDB11_F0_F1
PWM_PWMUDB_sP8_pwmdp_u0__F0_REG EQU CYREG_B0_UDB11_F0
PWM_PWMUDB_sP8_pwmdp_u0__F1_REG EQU CYREG_B0_UDB11_F1

/* Clock_1 */
Clock_1__CFG0 EQU CYREG_CLKDIST_DCFG1_CFG0
Clock_1__CFG1 EQU CYREG_CLKDIST_DCFG1_CFG1
Clock_1__CFG2 EQU CYREG_CLKDIST_DCFG1_CFG2
Clock_1__CFG2_SRC_SEL_MASK EQU 0x07
Clock_1__INDEX EQU 0x01
Clock_1__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
Clock_1__PM_ACT_MSK EQU 0x02
Clock_1__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
Clock_1__PM_STBY_MSK EQU 0x02

/* CapSense */
CapSense_BufCH0__CFG0 EQU CYREG_CAPSL_CFG0
CapSense_BufCH0__CFG1 EQU CYREG_CAPSL_CFG1
CapSense_BufCH0__PM_ACT_CFG EQU CYREG_PM_ACT_CFG11
CapSense_BufCH0__PM_ACT_MSK EQU 0x10
CapSense_BufCH0__PM_STBY_CFG EQU CYREG_PM_STBY_CFG11
CapSense_BufCH0__PM_STBY_MSK EQU 0x10
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB12_13_A0
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB12_13_A1
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB12_13_D0
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB12_13_D1
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB12_13_ACTL
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB12_13_F0
CapSense_ClockGen_sC16_PRSdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB12_13_F1
CapSense_ClockGen_sC16_PRSdp_u0__A0_A1_REG EQU CYREG_B0_UDB12_A0_A1
CapSense_ClockGen_sC16_PRSdp_u0__A0_REG EQU CYREG_B0_UDB12_A0
CapSense_ClockGen_sC16_PRSdp_u0__A1_REG EQU CYREG_B0_UDB12_A1
CapSense_ClockGen_sC16_PRSdp_u0__D0_D1_REG EQU CYREG_B0_UDB12_D0_D1
CapSense_ClockGen_sC16_PRSdp_u0__D0_REG EQU CYREG_B0_UDB12_D0
CapSense_ClockGen_sC16_PRSdp_u0__D1_REG EQU CYREG_B0_UDB12_D1
CapSense_ClockGen_sC16_PRSdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB12_ACTL
CapSense_ClockGen_sC16_PRSdp_u0__F0_F1_REG EQU CYREG_B0_UDB12_F0_F1
CapSense_ClockGen_sC16_PRSdp_u0__F0_REG EQU CYREG_B0_UDB12_F0
CapSense_ClockGen_sC16_PRSdp_u0__F1_REG EQU CYREG_B0_UDB12_F1
CapSense_ClockGen_sC16_PRSdp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB12_MSK_ACTL
CapSense_ClockGen_sC16_PRSdp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB12_MSK_ACTL
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_A0_REG EQU CYREG_B0_UDB13_14_A0
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_A1_REG EQU CYREG_B0_UDB13_14_A1
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_D0_REG EQU CYREG_B0_UDB13_14_D0
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_D1_REG EQU CYREG_B0_UDB13_14_D1
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_F0_REG EQU CYREG_B0_UDB13_14_F0
CapSense_ClockGen_sC16_PRSdp_u1__16BIT_F1_REG EQU CYREG_B0_UDB13_14_F1
CapSense_ClockGen_sC16_PRSdp_u1__A0_A1_REG EQU CYREG_B0_UDB13_A0_A1
CapSense_ClockGen_sC16_PRSdp_u1__A0_REG EQU CYREG_B0_UDB13_A0
CapSense_ClockGen_sC16_PRSdp_u1__A1_REG EQU CYREG_B0_UDB13_A1
CapSense_ClockGen_sC16_PRSdp_u1__D0_D1_REG EQU CYREG_B0_UDB13_D0_D1
CapSense_ClockGen_sC16_PRSdp_u1__D0_REG EQU CYREG_B0_UDB13_D0
CapSense_ClockGen_sC16_PRSdp_u1__D1_REG EQU CYREG_B0_UDB13_D1
CapSense_ClockGen_sC16_PRSdp_u1__DP_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
CapSense_ClockGen_sC16_PRSdp_u1__F0_F1_REG EQU CYREG_B0_UDB13_F0_F1
CapSense_ClockGen_sC16_PRSdp_u1__F0_REG EQU CYREG_B0_UDB13_F0
CapSense_ClockGen_sC16_PRSdp_u1__F1_REG EQU CYREG_B0_UDB13_F1
CapSense_ClockGen_sC16_PRSdp_u1__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
CapSense_ClockGen_sC16_PRSdp_u1__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
CapSense_ClockGen_ScanSpeed__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
CapSense_ClockGen_ScanSpeed__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB13_14_CTL
CapSense_ClockGen_ScanSpeed__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB13_14_CTL
CapSense_ClockGen_ScanSpeed__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB13_14_CTL
CapSense_ClockGen_ScanSpeed__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB13_14_CTL
CapSense_ClockGen_ScanSpeed__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB13_14_MSK
CapSense_ClockGen_ScanSpeed__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB13_14_MSK
CapSense_ClockGen_ScanSpeed__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB13_14_MSK
CapSense_ClockGen_ScanSpeed__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB13_14_MSK
CapSense_ClockGen_ScanSpeed__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
CapSense_ClockGen_ScanSpeed__CONTROL_REG EQU CYREG_B0_UDB13_CTL
CapSense_ClockGen_ScanSpeed__CONTROL_ST_REG EQU CYREG_B0_UDB13_ST_CTL
CapSense_ClockGen_ScanSpeed__COUNT_REG EQU CYREG_B0_UDB13_CTL
CapSense_ClockGen_ScanSpeed__COUNT_ST_REG EQU CYREG_B0_UDB13_ST_CTL
CapSense_ClockGen_ScanSpeed__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
CapSense_ClockGen_ScanSpeed__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
CapSense_ClockGen_ScanSpeed__PERIOD_REG EQU CYREG_B0_UDB13_MSK
CapSense_ClockGen_SyncCtrl_CtrlReg__0__MASK EQU 0x01
CapSense_ClockGen_SyncCtrl_CtrlReg__0__POS EQU 0
CapSense_ClockGen_SyncCtrl_CtrlReg__1__MASK EQU 0x02
CapSense_ClockGen_SyncCtrl_CtrlReg__1__POS EQU 1
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB10_11_ACTL
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB10_11_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_ClockGen_SyncCtrl_CtrlReg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB10_11_MSK
CapSense_ClockGen_SyncCtrl_CtrlReg__2__MASK EQU 0x04
CapSense_ClockGen_SyncCtrl_CtrlReg__2__POS EQU 2
CapSense_ClockGen_SyncCtrl_CtrlReg__4__MASK EQU 0x10
CapSense_ClockGen_SyncCtrl_CtrlReg__4__POS EQU 4
CapSense_ClockGen_SyncCtrl_CtrlReg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB10_ACTL
CapSense_ClockGen_SyncCtrl_CtrlReg__CONTROL_REG EQU CYREG_B0_UDB10_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__CONTROL_ST_REG EQU CYREG_B0_UDB10_ST_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__COUNT_REG EQU CYREG_B0_UDB10_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__COUNT_ST_REG EQU CYREG_B0_UDB10_ST_CTL
CapSense_ClockGen_SyncCtrl_CtrlReg__MASK EQU 0x17
CapSense_ClockGen_SyncCtrl_CtrlReg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_ClockGen_SyncCtrl_CtrlReg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_ClockGen_SyncCtrl_CtrlReg__PERIOD_REG EQU CYREG_B0_UDB10_MSK
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_A0_REG EQU CYREG_B0_UDB10_11_A0
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_A1_REG EQU CYREG_B0_UDB10_11_A1
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_D0_REG EQU CYREG_B0_UDB10_11_D0
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_D1_REG EQU CYREG_B0_UDB10_11_D1
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB10_11_ACTL
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_F0_REG EQU CYREG_B0_UDB10_11_F0
CapSense_ClockGen_UDB_PrescalerDp_u0__16BIT_F1_REG EQU CYREG_B0_UDB10_11_F1
CapSense_ClockGen_UDB_PrescalerDp_u0__A0_A1_REG EQU CYREG_B0_UDB10_A0_A1
CapSense_ClockGen_UDB_PrescalerDp_u0__A0_REG EQU CYREG_B0_UDB10_A0
CapSense_ClockGen_UDB_PrescalerDp_u0__A1_REG EQU CYREG_B0_UDB10_A1
CapSense_ClockGen_UDB_PrescalerDp_u0__D0_D1_REG EQU CYREG_B0_UDB10_D0_D1
CapSense_ClockGen_UDB_PrescalerDp_u0__D0_REG EQU CYREG_B0_UDB10_D0
CapSense_ClockGen_UDB_PrescalerDp_u0__D1_REG EQU CYREG_B0_UDB10_D1
CapSense_ClockGen_UDB_PrescalerDp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB10_ACTL
CapSense_ClockGen_UDB_PrescalerDp_u0__F0_F1_REG EQU CYREG_B0_UDB10_F0_F1
CapSense_ClockGen_UDB_PrescalerDp_u0__F0_REG EQU CYREG_B0_UDB10_F0
CapSense_ClockGen_UDB_PrescalerDp_u0__F1_REG EQU CYREG_B0_UDB10_F1
CapSense_ClockGen_UDB_PrescalerDp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_ClockGen_UDB_PrescalerDp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB10_MSK_ACTL
CapSense_CmodCH0__0__INTTYPE EQU CYREG_PICU15_INTTYPE4
CapSense_CmodCH0__0__MASK EQU 0x10
CapSense_CmodCH0__0__PC EQU CYREG_IO_PC_PRT15_PC4
CapSense_CmodCH0__0__PORT EQU 15
CapSense_CmodCH0__0__SHIFT EQU 4
CapSense_CmodCH0__AG EQU CYREG_PRT15_AG
CapSense_CmodCH0__AMUX EQU CYREG_PRT15_AMUX
CapSense_CmodCH0__BIE EQU CYREG_PRT15_BIE
CapSense_CmodCH0__BIT_MASK EQU CYREG_PRT15_BIT_MASK
CapSense_CmodCH0__BYP EQU CYREG_PRT15_BYP
CapSense_CmodCH0__Cmod_CH0__INTTYPE EQU CYREG_PICU15_INTTYPE4
CapSense_CmodCH0__Cmod_CH0__MASK EQU 0x10
CapSense_CmodCH0__Cmod_CH0__PC EQU CYREG_IO_PC_PRT15_PC4
CapSense_CmodCH0__Cmod_CH0__PORT EQU 15
CapSense_CmodCH0__Cmod_CH0__SHIFT EQU 4
CapSense_CmodCH0__CTL EQU CYREG_PRT15_CTL
CapSense_CmodCH0__DM0 EQU CYREG_PRT15_DM0
CapSense_CmodCH0__DM1 EQU CYREG_PRT15_DM1
CapSense_CmodCH0__DM2 EQU CYREG_PRT15_DM2
CapSense_CmodCH0__DR EQU CYREG_PRT15_DR
CapSense_CmodCH0__INP_DIS EQU CYREG_PRT15_INP_DIS
CapSense_CmodCH0__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU15_BASE
CapSense_CmodCH0__LCD_COM_SEG EQU CYREG_PRT15_LCD_COM_SEG
CapSense_CmodCH0__LCD_EN EQU CYREG_PRT15_LCD_EN
CapSense_CmodCH0__MASK EQU 0x10
CapSense_CmodCH0__PORT EQU 15
CapSense_CmodCH0__PRT EQU CYREG_PRT15_PRT
CapSense_CmodCH0__PRTDSI__CAPS_SEL EQU CYREG_PRT15_CAPS_SEL
CapSense_CmodCH0__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT15_DBL_SYNC_IN
CapSense_CmodCH0__PRTDSI__OE_SEL0 EQU CYREG_PRT15_OE_SEL0
CapSense_CmodCH0__PRTDSI__OE_SEL1 EQU CYREG_PRT15_OE_SEL1
CapSense_CmodCH0__PRTDSI__OUT_SEL0 EQU CYREG_PRT15_OUT_SEL0
CapSense_CmodCH0__PRTDSI__OUT_SEL1 EQU CYREG_PRT15_OUT_SEL1
CapSense_CmodCH0__PRTDSI__SYNC_OUT EQU CYREG_PRT15_SYNC_OUT
CapSense_CmodCH0__PS EQU CYREG_PRT15_PS
CapSense_CmodCH0__SHIFT EQU 4
CapSense_CmodCH0__SLW EQU CYREG_PRT15_SLW
CapSense_CompCH0_ctComp__CLK EQU CYREG_CMP1_CLK
CapSense_CompCH0_ctComp__CMP_MASK EQU 0x02
CapSense_CompCH0_ctComp__CMP_NUMBER EQU 1
CapSense_CompCH0_ctComp__CR EQU CYREG_CMP1_CR
CapSense_CompCH0_ctComp__LUT__CR EQU CYREG_LUT1_CR
CapSense_CompCH0_ctComp__LUT__MSK EQU CYREG_LUT_MSK
CapSense_CompCH0_ctComp__LUT__MSK_MASK EQU 0x02
CapSense_CompCH0_ctComp__LUT__MSK_SHIFT EQU 1
CapSense_CompCH0_ctComp__LUT__MX EQU CYREG_LUT1_MX
CapSense_CompCH0_ctComp__LUT__SR EQU CYREG_LUT_SR
CapSense_CompCH0_ctComp__LUT__SR_MASK EQU 0x02
CapSense_CompCH0_ctComp__LUT__SR_SHIFT EQU 1
CapSense_CompCH0_ctComp__PM_ACT_CFG EQU CYREG_PM_ACT_CFG7
CapSense_CompCH0_ctComp__PM_ACT_MSK EQU 0x02
CapSense_CompCH0_ctComp__PM_STBY_CFG EQU CYREG_PM_STBY_CFG7
CapSense_CompCH0_ctComp__PM_STBY_MSK EQU 0x02
CapSense_CompCH0_ctComp__SW0 EQU CYREG_CMP1_SW0
CapSense_CompCH0_ctComp__SW2 EQU CYREG_CMP1_SW2
CapSense_CompCH0_ctComp__SW3 EQU CYREG_CMP1_SW3
CapSense_CompCH0_ctComp__SW4 EQU CYREG_CMP1_SW4
CapSense_CompCH0_ctComp__SW6 EQU CYREG_CMP1_SW6
CapSense_CompCH0_ctComp__TR0 EQU CYREG_CMP1_TR0
CapSense_CompCH0_ctComp__TR1 EQU CYREG_CMP1_TR1
CapSense_CompCH0_ctComp__TRIM__TR0 EQU CYREG_FLSHID_MFG_CFG_CMP1_TR0
CapSense_CompCH0_ctComp__TRIM__TR0_HS EQU CYREG_FLSHID_CUST_TABLES_CMP1_TR0_HS
CapSense_CompCH0_ctComp__TRIM__TR1 EQU CYREG_FLSHID_MFG_CFG_CMP1_TR1
CapSense_CompCH0_ctComp__TRIM__TR1_HS EQU CYREG_FLSHID_CUST_TABLES_CMP1_TR1_HS
CapSense_CompCH0_ctComp__WRK EQU CYREG_CMP_WRK
CapSense_CompCH0_ctComp__WRK_MASK EQU 0x02
CapSense_CompCH0_ctComp__WRK_SHIFT EQU 1
CapSense_IdacCH0_viDAC8__CR0 EQU CYREG_DAC3_CR0
CapSense_IdacCH0_viDAC8__CR1 EQU CYREG_DAC3_CR1
CapSense_IdacCH0_viDAC8__D EQU CYREG_DAC3_D
CapSense_IdacCH0_viDAC8__PM_ACT_CFG EQU CYREG_PM_ACT_CFG8
CapSense_IdacCH0_viDAC8__PM_ACT_MSK EQU 0x08
CapSense_IdacCH0_viDAC8__PM_STBY_CFG EQU CYREG_PM_STBY_CFG8
CapSense_IdacCH0_viDAC8__PM_STBY_MSK EQU 0x08
CapSense_IdacCH0_viDAC8__STROBE EQU CYREG_DAC3_STROBE
CapSense_IdacCH0_viDAC8__SW0 EQU CYREG_DAC3_SW0
CapSense_IdacCH0_viDAC8__SW2 EQU CYREG_DAC3_SW2
CapSense_IdacCH0_viDAC8__SW3 EQU CYREG_DAC3_SW3
CapSense_IdacCH0_viDAC8__SW4 EQU CYREG_DAC3_SW4
CapSense_IdacCH0_viDAC8__TR EQU CYREG_DAC3_TR
CapSense_IdacCH0_viDAC8__TRIM__M1 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M1
CapSense_IdacCH0_viDAC8__TRIM__M2 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M2
CapSense_IdacCH0_viDAC8__TRIM__M3 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M3
CapSense_IdacCH0_viDAC8__TRIM__M4 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M4
CapSense_IdacCH0_viDAC8__TRIM__M5 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M5
CapSense_IdacCH0_viDAC8__TRIM__M6 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M6
CapSense_IdacCH0_viDAC8__TRIM__M7 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M7
CapSense_IdacCH0_viDAC8__TRIM__M8 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M8
CapSense_IdacCH0_viDAC8__TST EQU CYREG_DAC3_TST
CapSense_IntClock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
CapSense_IntClock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
CapSense_IntClock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
CapSense_IntClock__CFG2_SRC_SEL_MASK EQU 0x07
CapSense_IntClock__INDEX EQU 0x00
CapSense_IntClock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
CapSense_IntClock__PM_ACT_MSK EQU 0x01
CapSense_IntClock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
CapSense_IntClock__PM_STBY_MSK EQU 0x01
CapSense_IsrCH0__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
CapSense_IsrCH0__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
CapSense_IsrCH0__INTC_MASK EQU 0x01
CapSense_IsrCH0__INTC_NUMBER EQU 0
CapSense_IsrCH0__INTC_PRIOR_NUM EQU 7
CapSense_IsrCH0__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_0
CapSense_IsrCH0__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
CapSense_IsrCH0__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
CapSense_MeasureCH0_UDB_Counter_u0__A0_A1_REG EQU CYREG_B0_UDB15_A0_A1
CapSense_MeasureCH0_UDB_Counter_u0__A0_REG EQU CYREG_B0_UDB15_A0
CapSense_MeasureCH0_UDB_Counter_u0__A1_REG EQU CYREG_B0_UDB15_A1
CapSense_MeasureCH0_UDB_Counter_u0__D0_D1_REG EQU CYREG_B0_UDB15_D0_D1
CapSense_MeasureCH0_UDB_Counter_u0__D0_REG EQU CYREG_B0_UDB15_D0
CapSense_MeasureCH0_UDB_Counter_u0__D1_REG EQU CYREG_B0_UDB15_D1
CapSense_MeasureCH0_UDB_Counter_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB15_ACTL
CapSense_MeasureCH0_UDB_Counter_u0__F0_F1_REG EQU CYREG_B0_UDB15_F0_F1
CapSense_MeasureCH0_UDB_Counter_u0__F0_REG EQU CYREG_B0_UDB15_F0
CapSense_MeasureCH0_UDB_Counter_u0__F1_REG EQU CYREG_B0_UDB15_F1
CapSense_MeasureCH0_UDB_Window_u0__16BIT_A0_REG EQU CYREG_B0_UDB14_15_A0
CapSense_MeasureCH0_UDB_Window_u0__16BIT_A1_REG EQU CYREG_B0_UDB14_15_A1
CapSense_MeasureCH0_UDB_Window_u0__16BIT_D0_REG EQU CYREG_B0_UDB14_15_D0
CapSense_MeasureCH0_UDB_Window_u0__16BIT_D1_REG EQU CYREG_B0_UDB14_15_D1
CapSense_MeasureCH0_UDB_Window_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB14_15_ACTL
CapSense_MeasureCH0_UDB_Window_u0__16BIT_F0_REG EQU CYREG_B0_UDB14_15_F0
CapSense_MeasureCH0_UDB_Window_u0__16BIT_F1_REG EQU CYREG_B0_UDB14_15_F1
CapSense_MeasureCH0_UDB_Window_u0__A0_A1_REG EQU CYREG_B0_UDB14_A0_A1
CapSense_MeasureCH0_UDB_Window_u0__A0_REG EQU CYREG_B0_UDB14_A0
CapSense_MeasureCH0_UDB_Window_u0__A1_REG EQU CYREG_B0_UDB14_A1
CapSense_MeasureCH0_UDB_Window_u0__D0_D1_REG EQU CYREG_B0_UDB14_D0_D1
CapSense_MeasureCH0_UDB_Window_u0__D0_REG EQU CYREG_B0_UDB14_D0
CapSense_MeasureCH0_UDB_Window_u0__D1_REG EQU CYREG_B0_UDB14_D1
CapSense_MeasureCH0_UDB_Window_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB14_ACTL
CapSense_MeasureCH0_UDB_Window_u0__F0_F1_REG EQU CYREG_B0_UDB14_F0_F1
CapSense_MeasureCH0_UDB_Window_u0__F0_REG EQU CYREG_B0_UDB14_F0
CapSense_MeasureCH0_UDB_Window_u0__F1_REG EQU CYREG_B0_UDB14_F1
CapSense_PortCH0__0__INTTYPE EQU CYREG_PICU3_INTTYPE3
CapSense_PortCH0__0__MASK EQU 0x08
CapSense_PortCH0__0__PC EQU CYREG_PRT3_PC3
CapSense_PortCH0__0__PORT EQU 3
CapSense_PortCH0__0__SHIFT EQU 3
CapSense_PortCH0__1__INTTYPE EQU CYREG_PICU3_INTTYPE4
CapSense_PortCH0__1__MASK EQU 0x10
CapSense_PortCH0__1__PC EQU CYREG_PRT3_PC4
CapSense_PortCH0__1__PORT EQU 3
CapSense_PortCH0__1__SHIFT EQU 4
CapSense_PortCH0__2__INTTYPE EQU CYREG_PICU3_INTTYPE5
CapSense_PortCH0__2__MASK EQU 0x20
CapSense_PortCH0__2__PC EQU CYREG_PRT3_PC5
CapSense_PortCH0__2__PORT EQU 3
CapSense_PortCH0__2__SHIFT EQU 5
CapSense_PortCH0__3__INTTYPE EQU CYREG_PICU3_INTTYPE6
CapSense_PortCH0__3__MASK EQU 0x40
CapSense_PortCH0__3__PC EQU CYREG_PRT3_PC6
CapSense_PortCH0__3__PORT EQU 3
CapSense_PortCH0__3__SHIFT EQU 6
CapSense_PortCH0__4__INTTYPE EQU CYREG_PICU3_INTTYPE7
CapSense_PortCH0__4__MASK EQU 0x80
CapSense_PortCH0__4__PC EQU CYREG_PRT3_PC7
CapSense_PortCH0__4__PORT EQU 3
CapSense_PortCH0__4__SHIFT EQU 7
CapSense_PortCH0__AG EQU CYREG_PRT3_AG
CapSense_PortCH0__AMUX EQU CYREG_PRT3_AMUX
CapSense_PortCH0__BIE EQU CYREG_PRT3_BIE
CapSense_PortCH0__BIT_MASK EQU CYREG_PRT3_BIT_MASK
CapSense_PortCH0__BYP EQU CYREG_PRT3_BYP
CapSense_PortCH0__CTL EQU CYREG_PRT3_CTL
CapSense_PortCH0__DM0 EQU CYREG_PRT3_DM0
CapSense_PortCH0__DM1 EQU CYREG_PRT3_DM1
CapSense_PortCH0__DM2 EQU CYREG_PRT3_DM2
CapSense_PortCH0__DR EQU CYREG_PRT3_DR
CapSense_PortCH0__INP_DIS EQU CYREG_PRT3_INP_DIS
CapSense_PortCH0__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
CapSense_PortCH0__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
CapSense_PortCH0__LCD_EN EQU CYREG_PRT3_LCD_EN
CapSense_PortCH0__LinearSlider0_e0__LS__INTTYPE EQU CYREG_PICU3_INTTYPE3
CapSense_PortCH0__LinearSlider0_e0__LS__MASK EQU 0x08
CapSense_PortCH0__LinearSlider0_e0__LS__PC EQU CYREG_PRT3_PC3
CapSense_PortCH0__LinearSlider0_e0__LS__PORT EQU 3
CapSense_PortCH0__LinearSlider0_e0__LS__SHIFT EQU 3
CapSense_PortCH0__LinearSlider0_e1__LS__INTTYPE EQU CYREG_PICU3_INTTYPE4
CapSense_PortCH0__LinearSlider0_e1__LS__MASK EQU 0x10
CapSense_PortCH0__LinearSlider0_e1__LS__PC EQU CYREG_PRT3_PC4
CapSense_PortCH0__LinearSlider0_e1__LS__PORT EQU 3
CapSense_PortCH0__LinearSlider0_e1__LS__SHIFT EQU 4
CapSense_PortCH0__LinearSlider0_e2__LS__INTTYPE EQU CYREG_PICU3_INTTYPE5
CapSense_PortCH0__LinearSlider0_e2__LS__MASK EQU 0x20
CapSense_PortCH0__LinearSlider0_e2__LS__PC EQU CYREG_PRT3_PC5
CapSense_PortCH0__LinearSlider0_e2__LS__PORT EQU 3
CapSense_PortCH0__LinearSlider0_e2__LS__SHIFT EQU 5
CapSense_PortCH0__LinearSlider0_e3__LS__INTTYPE EQU CYREG_PICU3_INTTYPE6
CapSense_PortCH0__LinearSlider0_e3__LS__MASK EQU 0x40
CapSense_PortCH0__LinearSlider0_e3__LS__PC EQU CYREG_PRT3_PC6
CapSense_PortCH0__LinearSlider0_e3__LS__PORT EQU 3
CapSense_PortCH0__LinearSlider0_e3__LS__SHIFT EQU 6
CapSense_PortCH0__LinearSlider0_e4__LS__INTTYPE EQU CYREG_PICU3_INTTYPE7
CapSense_PortCH0__LinearSlider0_e4__LS__MASK EQU 0x80
CapSense_PortCH0__LinearSlider0_e4__LS__PC EQU CYREG_PRT3_PC7
CapSense_PortCH0__LinearSlider0_e4__LS__PORT EQU 3
CapSense_PortCH0__LinearSlider0_e4__LS__SHIFT EQU 7
CapSense_PortCH0__PORT EQU 3
CapSense_PortCH0__PRT EQU CYREG_PRT3_PRT
CapSense_PortCH0__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
CapSense_PortCH0__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
CapSense_PortCH0__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
CapSense_PortCH0__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
CapSense_PortCH0__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
CapSense_PortCH0__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
CapSense_PortCH0__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
CapSense_PortCH0__PS EQU CYREG_PRT3_PS
CapSense_PortCH0__SLW EQU CYREG_PRT3_SLW

/* Miscellaneous */
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
CYDEV_INTR_RISING EQU 0x00000001
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

#endif /* INCLUDED_CYFITTERIAR_INC */
