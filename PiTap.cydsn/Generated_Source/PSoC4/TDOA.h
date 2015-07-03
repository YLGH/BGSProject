/*******************************************************************************
* File Name: TDOA.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_TDOA_H)
#define CY_Timer_v2_60_TDOA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TDOA_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TDOA_Resolution                 32u
#define TDOA_UsingFixedFunction         0u
#define TDOA_UsingHWCaptureCounter      0u
#define TDOA_SoftwareCaptureMode        0u
#define TDOA_SoftwareTriggerMode        0u
#define TDOA_UsingHWEnable              0u
#define TDOA_EnableTriggerMode          0u
#define TDOA_InterruptOnCaptureCount    0u
#define TDOA_RunModeUsed                0u
#define TDOA_ControlRegRemoved          0u

#if defined(TDOA_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TDOA_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TDOA_UsingFixedFunction)
    #define TDOA_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TDOA_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TDOA_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TDOA_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TDOA_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TDOA_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TDOA_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TDOA_Start(void) ;
void    TDOA_Stop(void) ;

void    TDOA_SetInterruptMode(uint8 interruptMode) ;
uint8   TDOA_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TDOA_GetInterruptSource() TDOA_ReadStatusRegister()

#if(!TDOA_UDB_CONTROL_REG_REMOVED)
    uint8   TDOA_ReadControlRegister(void) ;
    void    TDOA_WriteControlRegister(uint8 control) ;
#endif /* (!TDOA_UDB_CONTROL_REG_REMOVED) */

uint32  TDOA_ReadPeriod(void) ;
void    TDOA_WritePeriod(uint32 period) ;
uint32  TDOA_ReadCounter(void) ;
void    TDOA_WriteCounter(uint32 counter) ;
uint32  TDOA_ReadCapture(void) ;
void    TDOA_SoftwareCapture(void) ;

#if(!TDOA_UsingFixedFunction) /* UDB Prototypes */
    #if (TDOA_SoftwareCaptureMode)
        void    TDOA_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TDOA_UsingFixedFunction) */

    #if (TDOA_SoftwareTriggerMode)
        void    TDOA_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TDOA_SoftwareTriggerMode) */

    #if (TDOA_EnableTriggerMode)
        void    TDOA_EnableTrigger(void) ;
        void    TDOA_DisableTrigger(void) ;
    #endif /* (TDOA_EnableTriggerMode) */


    #if(TDOA_InterruptOnCaptureCount)
        void    TDOA_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TDOA_InterruptOnCaptureCount) */

    #if (TDOA_UsingHWCaptureCounter)
        void    TDOA_SetCaptureCount(uint8 captureCount) ;
        uint8   TDOA_ReadCaptureCount(void) ;
    #endif /* (TDOA_UsingHWCaptureCounter) */

    void TDOA_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TDOA_Init(void)          ;
void TDOA_Enable(void)        ;
void TDOA_SaveConfig(void)    ;
void TDOA_RestoreConfig(void) ;
void TDOA_Sleep(void)         ;
void TDOA_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TDOA__B_TIMER__CM_NONE 0
#define TDOA__B_TIMER__CM_RISINGEDGE 1
#define TDOA__B_TIMER__CM_FALLINGEDGE 2
#define TDOA__B_TIMER__CM_EITHEREDGE 3
#define TDOA__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TDOA__B_TIMER__TM_NONE 0x00u
#define TDOA__B_TIMER__TM_RISINGEDGE 0x04u
#define TDOA__B_TIMER__TM_FALLINGEDGE 0x08u
#define TDOA__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TDOA__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TDOA_INIT_PERIOD             4294967295u
#define TDOA_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TDOA_CTRL_CAP_MODE_SHIFT))
#define TDOA_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TDOA_CTRL_TRIG_MODE_SHIFT))
#if (TDOA_UsingFixedFunction)
    #define TDOA_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TDOA_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TDOA_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TDOA_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TDOA_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TDOA_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TDOA_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TDOA_UsingFixedFunction) */
#define TDOA_INIT_CAPTURE_COUNT      (2u)
#define TDOA_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TDOA_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TDOA_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TDOA_STATUS         (*(reg8 *) TDOA_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TDOA_STATUS_MASK    (*(reg8 *) TDOA_TimerHW__SR0 )
    #define TDOA_CONTROL        (*(reg8 *) TDOA_TimerHW__CFG0)
    #define TDOA_CONTROL2       (*(reg8 *) TDOA_TimerHW__CFG1)
    #define TDOA_CONTROL2_PTR   ( (reg8 *) TDOA_TimerHW__CFG1)
    #define TDOA_RT1            (*(reg8 *) TDOA_TimerHW__RT1)
    #define TDOA_RT1_PTR        ( (reg8 *) TDOA_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TDOA_CONTROL3       (*(reg8 *) TDOA_TimerHW__CFG2)
        #define TDOA_CONTROL3_PTR   ( (reg8 *) TDOA_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TDOA_GLOBAL_ENABLE  (*(reg8 *) TDOA_TimerHW__PM_ACT_CFG)
    #define TDOA_GLOBAL_STBY_ENABLE  (*(reg8 *) TDOA_TimerHW__PM_STBY_CFG)

    #define TDOA_CAPTURE_LSB         (* (reg16 *) TDOA_TimerHW__CAP0 )
    #define TDOA_CAPTURE_LSB_PTR       ((reg16 *) TDOA_TimerHW__CAP0 )
    #define TDOA_PERIOD_LSB          (* (reg16 *) TDOA_TimerHW__PER0 )
    #define TDOA_PERIOD_LSB_PTR        ((reg16 *) TDOA_TimerHW__PER0 )
    #define TDOA_COUNTER_LSB         (* (reg16 *) TDOA_TimerHW__CNT_CMP0 )
    #define TDOA_COUNTER_LSB_PTR       ((reg16 *) TDOA_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TDOA_BLOCK_EN_MASK                     TDOA_TimerHW__PM_ACT_MSK
    #define TDOA_BLOCK_STBY_EN_MASK                TDOA_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TDOA_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TDOA_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TDOA_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TDOA_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TDOA_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TDOA_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TDOA_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TDOA_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TDOA_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TDOA_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TDOA_CTRL_MODE_SHIFT                 0x01u
        #define TDOA_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TDOA_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TDOA_CTRL_RCOD_SHIFT        0x02u
        #define TDOA_CTRL_ENBL_SHIFT        0x00u
        #define TDOA_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TDOA_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TDOA_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TDOA_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TDOA_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TDOA_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TDOA_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TDOA_CTRL_RCOD       ((uint8)((uint8)0x03u << TDOA_CTRL_RCOD_SHIFT))
        #define TDOA_CTRL_ENBL       ((uint8)((uint8)0x80u << TDOA_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TDOA_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TDOA_RT1_MASK                        ((uint8)((uint8)0x03u << TDOA_RT1_SHIFT))
    #define TDOA_SYNC                            ((uint8)((uint8)0x03u << TDOA_RT1_SHIFT))
    #define TDOA_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TDOA_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TDOA_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TDOA_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TDOA_SYNCDSI_SHIFT))

    #define TDOA_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TDOA_CTRL_MODE_SHIFT))
    #define TDOA_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TDOA_CTRL_MODE_SHIFT))
    #define TDOA_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TDOA_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TDOA_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TDOA_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TDOA_STATUS_TC_INT_MASK_SHIFT        (TDOA_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TDOA_STATUS_CAPTURE_INT_MASK_SHIFT   (TDOA_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TDOA_STATUS_TC                       ((uint8)((uint8)0x01u << TDOA_STATUS_TC_SHIFT))
    #define TDOA_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TDOA_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TDOA_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TDOA_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TDOA_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TDOA_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TDOA_STATUS              (* (reg8 *) TDOA_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TDOA_STATUS_MASK         (* (reg8 *) TDOA_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TDOA_STATUS_AUX_CTRL     (* (reg8 *) TDOA_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TDOA_CONTROL             (* (reg8 *) TDOA_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TDOA_Resolution <= 8u) /* 8-bit Timer */
        #define TDOA_CAPTURE_LSB         (* (reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define TDOA_CAPTURE_LSB_PTR       ((reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define TDOA_PERIOD_LSB          (* (reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define TDOA_PERIOD_LSB_PTR        ((reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define TDOA_COUNTER_LSB         (* (reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define TDOA_COUNTER_LSB_PTR       ((reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(TDOA_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TDOA_CAPTURE_LSB         (* (reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define TDOA_CAPTURE_LSB_PTR       ((reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define TDOA_PERIOD_LSB          (* (reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define TDOA_PERIOD_LSB_PTR        ((reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define TDOA_COUNTER_LSB         (* (reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define TDOA_COUNTER_LSB_PTR       ((reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TDOA_CAPTURE_LSB         (* (reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define TDOA_CAPTURE_LSB_PTR       ((reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define TDOA_PERIOD_LSB          (* (reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define TDOA_PERIOD_LSB_PTR        ((reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define TDOA_COUNTER_LSB         (* (reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define TDOA_COUNTER_LSB_PTR       ((reg16 *) TDOA_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TDOA_Resolution <= 24u)/* 24-bit Timer */
        #define TDOA_CAPTURE_LSB         (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define TDOA_CAPTURE_LSB_PTR       ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define TDOA_PERIOD_LSB          (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define TDOA_PERIOD_LSB_PTR        ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define TDOA_COUNTER_LSB         (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define TDOA_COUNTER_LSB_PTR       ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TDOA_CAPTURE_LSB         (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define TDOA_CAPTURE_LSB_PTR       ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define TDOA_PERIOD_LSB          (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define TDOA_PERIOD_LSB_PTR        ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define TDOA_COUNTER_LSB         (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define TDOA_COUNTER_LSB_PTR       ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TDOA_CAPTURE_LSB         (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define TDOA_CAPTURE_LSB_PTR       ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define TDOA_PERIOD_LSB          (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define TDOA_PERIOD_LSB_PTR        ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define TDOA_COUNTER_LSB         (* (reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define TDOA_COUNTER_LSB_PTR       ((reg32 *) TDOA_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TDOA_COUNTER_LSB_PTR_8BIT       ((reg8 *) TDOA_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (TDOA_UsingHWCaptureCounter)
        #define TDOA_CAP_COUNT              (*(reg8 *) TDOA_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TDOA_CAP_COUNT_PTR          ( (reg8 *) TDOA_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TDOA_CAPTURE_COUNT_CTRL     (*(reg8 *) TDOA_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TDOA_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TDOA_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TDOA_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TDOA_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TDOA_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TDOA_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TDOA_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TDOA_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TDOA_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TDOA_CTRL_INTCNT_SHIFT))
    #define TDOA_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TDOA_CTRL_TRIG_MODE_SHIFT))
    #define TDOA_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TDOA_CTRL_TRIG_EN_SHIFT))
    #define TDOA_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TDOA_CTRL_CAP_MODE_SHIFT))
    #define TDOA_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TDOA_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TDOA_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TDOA_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TDOA_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TDOA_STATUS_TC_INT_MASK_SHIFT       TDOA_STATUS_TC_SHIFT
    #define TDOA_STATUS_CAPTURE_INT_MASK_SHIFT  TDOA_STATUS_CAPTURE_SHIFT
    #define TDOA_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TDOA_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TDOA_STATUS_FIFOFULL_INT_MASK_SHIFT TDOA_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TDOA_STATUS_TC                      ((uint8)((uint8)0x01u << TDOA_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TDOA_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TDOA_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TDOA_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TDOA_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TDOA_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TDOA_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TDOA_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TDOA_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TDOA_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TDOA_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TDOA_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TDOA_STATUS_FIFOFULL_SHIFT))

    #define TDOA_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TDOA_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TDOA_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TDOA_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TDOA_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TDOA_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TDOA_H */


/* [] END OF FILE */
