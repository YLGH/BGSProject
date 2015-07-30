/*******************************************************************************
* File Name: SPI_PI_SPI.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_PI_PVT.h"
#include "SPI_PI_SPI_UART_PVT.h"

#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SPI_PI_SPI_INIT_STRUCT SPI_PI_configSpi =
    {
        SPI_PI_SPI_MODE,
        SPI_PI_SPI_SUB_MODE,
        SPI_PI_SPI_CLOCK_MODE,
        SPI_PI_SPI_OVS_FACTOR,
        SPI_PI_SPI_MEDIAN_FILTER_ENABLE,
        SPI_PI_SPI_LATE_MISO_SAMPLE_ENABLE,
        SPI_PI_SPI_WAKE_ENABLE,
        SPI_PI_SPI_RX_DATA_BITS_NUM,
        SPI_PI_SPI_TX_DATA_BITS_NUM,
        SPI_PI_SPI_BITS_ORDER,
        SPI_PI_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) SPI_PI_SCB_IRQ_INTERNAL,
        SPI_PI_SPI_INTR_RX_MASK,
        SPI_PI_SPI_RX_TRIGGER_LEVEL,
        SPI_PI_SPI_INTR_TX_MASK,
        SPI_PI_SPI_TX_TRIGGER_LEVEL,
        (uint8) SPI_PI_SPI_BYTE_MODE_ENABLE,
        (uint8) SPI_PI_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) SPI_PI_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: SPI_PI_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the SPI operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiInit(const SPI_PI_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SPI_PI_SetPins(SPI_PI_SCB_MODE_SPI, config->mode, SPI_PI_DUMMY_PARAM);

            /* Store internal configuration */
            SPI_PI_scbMode       = (uint8) SPI_PI_SCB_MODE_SPI;
            SPI_PI_scbEnableWake = (uint8) config->enableWake;
            SPI_PI_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SPI_PI_rxBuffer      =         config->rxBuffer;
            SPI_PI_rxDataBits    = (uint8) config->rxDataBits;
            SPI_PI_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            SPI_PI_txBuffer      =         config->txBuffer;
            SPI_PI_txDataBits    = (uint8) config->txDataBits;
            SPI_PI_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure SPI interface */
            SPI_PI_CTRL_REG     = SPI_PI_GET_CTRL_OVS(config->oversample)           |
                                            SPI_PI_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            SPI_PI_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            SPI_PI_CTRL_SPI;

            SPI_PI_SPI_CTRL_REG = SPI_PI_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SPI_PI_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SPI_PI_SPI_MODE_TI_PRECEDES_MASK) |
                                            SPI_PI_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SPI_PI_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SPI_PI_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            SPI_PI_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            SPI_PI_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SPI_PI_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SPI_PI_RX_CTRL_REG     =  SPI_PI_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SPI_PI_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SPI_PI_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SPI_PI_SPI_RX_CTRL;

            SPI_PI_RX_FIFO_CTRL_REG = SPI_PI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SPI_PI_TX_CTRL_REG      = SPI_PI_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SPI_PI_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SPI_PI_SPI_TX_CTRL;

            SPI_PI_TX_FIFO_CTRL_REG = SPI_PI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (SPI_PI_ISR_NUMBER);
            CyIntSetPriority(SPI_PI_ISR_NUMBER, SPI_PI_ISR_PRIORITY);
            (void) CyIntSetVector(SPI_PI_ISR_NUMBER, &SPI_PI_SPI_UART_ISR);

            /* Configure interrupt sources */
            SPI_PI_INTR_I2C_EC_MASK_REG = SPI_PI_NO_INTR_SOURCES;
            SPI_PI_INTR_SPI_EC_MASK_REG = SPI_PI_NO_INTR_SOURCES;
            SPI_PI_INTR_SLAVE_MASK_REG  = SPI_PI_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SPI_PI_INTR_MASTER_MASK_REG = SPI_PI_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SPI_PI_INTR_RX_MASK_REG     = SPI_PI_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SPI_PI_INTR_TX_MASK_REG     = SPI_PI_GET_SPI_INTR_TX_MASK(config->txInterruptMask);

            /* Set active SS0 */
            SPI_PI_SpiSetActiveSlaveSelect(SPI_PI_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            SPI_PI_rxBufferHead     = 0u;
            SPI_PI_rxBufferTail     = 0u;
            SPI_PI_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SPI_PI_txBufferHead = 0u;
            SPI_PI_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SPI_PI_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiInit(void)
    {
        /* Configure SPI interface */
        SPI_PI_CTRL_REG     = SPI_PI_SPI_DEFAULT_CTRL;
        SPI_PI_SPI_CTRL_REG = SPI_PI_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SPI_PI_RX_CTRL_REG      = SPI_PI_SPI_DEFAULT_RX_CTRL;
        SPI_PI_RX_FIFO_CTRL_REG = SPI_PI_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SPI_PI_TX_CTRL_REG      = SPI_PI_SPI_DEFAULT_TX_CTRL;
        SPI_PI_TX_FIFO_CTRL_REG = SPI_PI_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(SPI_PI_SCB_IRQ_INTERNAL)
            CyIntDisable    (SPI_PI_ISR_NUMBER);
            CyIntSetPriority(SPI_PI_ISR_NUMBER, SPI_PI_ISR_PRIORITY);
            (void) CyIntSetVector(SPI_PI_ISR_NUMBER, &SPI_PI_SPI_UART_ISR);
    #endif /* (SPI_PI_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        SPI_PI_INTR_I2C_EC_MASK_REG = SPI_PI_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SPI_PI_INTR_SPI_EC_MASK_REG = SPI_PI_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SPI_PI_INTR_SLAVE_MASK_REG  = SPI_PI_SPI_DEFAULT_INTR_SLAVE_MASK;
        SPI_PI_INTR_MASTER_MASK_REG = SPI_PI_SPI_DEFAULT_INTR_MASTER_MASK;
        SPI_PI_INTR_RX_MASK_REG     = SPI_PI_SPI_DEFAULT_INTR_RX_MASK;
        SPI_PI_INTR_TX_MASK_REG     = SPI_PI_SPI_DEFAULT_INTR_TX_MASK;

        /* Set active SS0 for master */
    #if (SPI_PI_SPI_MASTER_CONST)
        SPI_PI_SpiSetActiveSlaveSelect(SPI_PI_SPI_SLAVE_SELECT0);
    #endif /* (SPI_PI_SPI_MASTER_CONST) */

    #if(SPI_PI_INTERNAL_RX_SW_BUFFER_CONST)
        SPI_PI_rxBufferHead     = 0u;
        SPI_PI_rxBufferTail     = 0u;
        SPI_PI_rxBufferOverflow = 0u;
    #endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SPI_PI_INTERNAL_TX_SW_BUFFER_CONST)
        SPI_PI_txBufferHead = 0u;
        SPI_PI_txBufferTail = 0u;
    #endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SPI_PI_SpiPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI_PI_SpiPostEnable(void)
{
#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SPI_PI_CHECK_SPI_MASTER)
    {
    #if (SPI_PI_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_CTS_SCLK_HSIOM_REG, SPI_PI_CTS_SCLK_HSIOM_MASK,
                                       SPI_PI_CTS_SCLK_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
    #endif /* (SPI_PI_CTS_SCLK_PIN) */

    #if (SPI_PI_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_RTS_SS0_HSIOM_REG, SPI_PI_RTS_SS0_HSIOM_MASK,
                                       SPI_PI_RTS_SS0_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
    #endif /* (SPI_PI_RTS_SS0_PIN) */

    #if (SPI_PI_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS1_HSIOM_REG, SPI_PI_SS1_HSIOM_MASK,
                                       SPI_PI_SS1_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
    #endif /* (SPI_PI_SS1_PIN) */

    #if (SPI_PI_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS2_HSIOM_REG, SPI_PI_SS2_HSIOM_MASK,
                                       SPI_PI_SS2_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
    #endif /* (SPI_PI_SS2_PIN) */

    #if (SPI_PI_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS3_HSIOM_REG, SPI_PI_SS3_HSIOM_MASK,
                                       SPI_PI_SS3_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
    #endif /* (SPI_PI_SS3_PIN) */
    }

#else

#if (SPI_PI_SPI_MASTER_SCLK_PIN)
    /* Set SCB SPI to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SCLK_M_HSIOM_REG, SPI_PI_SCLK_M_HSIOM_MASK,
                                   SPI_PI_SCLK_M_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
#endif /* (SPI_PI_MISO_SDA_TX_PIN_PIN) */

#if (SPI_PI_SPI_MASTER_SS0_PIN)
    /* Set SCB SPI to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS0_M_HSIOM_REG, SPI_PI_SS0_M_HSIOM_MASK,
                                   SPI_PI_SS0_M_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS0_PIN) */

#if (SPI_PI_SPI_MASTER_SS1_PIN)
    /* Set SCB SPI to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS1_M_HSIOM_REG, SPI_PI_SS1_M_HSIOM_MASK,
                                   SPI_PI_SS1_M_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS1_PIN) */

#if (SPI_PI_SPI_MASTER_SS2_PIN)
    /* Set SCB SPI to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS2_M_HSIOM_REG, SPI_PI_SS2_M_HSIOM_MASK,
                                   SPI_PI_SS2_M_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS2_PIN) */

#if (SPI_PI_SPI_MASTER_SS3_PIN)
    /* Set SCB SPI to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS3_M_HSIOM_REG, SPI_PI_SS3_M_HSIOM_MASK,
                                   SPI_PI_SS3_M_HSIOM_POS, SPI_PI_HSIOM_SPI_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS3_PIN) */

#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI_PI_SpiStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) to
*  keep them inactive after the block is disabled. The output pins are
*  controlled by the GPIO data register.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI_PI_SpiStop(void)
{
#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SPI_PI_CHECK_SPI_MASTER)
    {
    #if (SPI_PI_SCLK_PIN)
        /* Set output pin state after block is disabled */
        SPI_PI_uart_cts_spi_sclk_Write(SPI_PI_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SCLK_HSIOM_REG, SPI_PI_SCLK_HSIOM_MASK,
                                       SPI_PI_SCLK_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
    #endif /* (SPI_PI_MISO_SDA_TX_PIN_PIN) */

    #if (SPI_PI_SS0_PIN)
        /* Set output pin state after block is disabled */
        SPI_PI_uart_rts_spi_ss0_Write(SPI_PI_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS0_HSIOM_REG, SPI_PI_SS0_HSIOM_MASK,
                                       SPI_PI_SS0_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
    #endif /* (SPI_PI_SS0_PIN) */

    #if (SPI_PI_SS1_PIN)
        /* Set output pin state after block is disabled */
        SPI_PI_spi_ss1_Write(SPI_PI_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS1_HSIOM_REG, SPI_PI_SS1_HSIOM_MASK,
                                       SPI_PI_SS1_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
    #endif /* (SPI_PI_SS1_PIN) */

    #if (SPI_PI_SS2_PIN)
        /* Set output pin state after block is disabled */
        SPI_PI_spi_ss2_Write(SPI_PI_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS2_HSIOM_REG, SPI_PI_SS2_HSIOM_MASK,
                                       SPI_PI_SS2_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
    #endif /* (SPI_PI_SS2_PIN) */

    #if (SPI_PI_SS3_PIN)
        /* Set output pin state after block is disabled */
        SPI_PI_spi_ss3_Write(SPI_PI_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        SPI_PI_SET_HSIOM_SEL(SPI_PI_SS3_HSIOM_REG, SPI_PI_SS3_HSIOM_MASK,
                                       SPI_PI_SS3_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
    #endif /* (SPI_PI_SS3_PIN) */
    }

#else

#if (SPI_PI_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    SPI_PI_sclk_m_Write(SPI_PI_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SCLK_M_HSIOM_REG, SPI_PI_SCLK_M_HSIOM_MASK,
                                   SPI_PI_SCLK_M_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
#endif /* (SPI_PI_MISO_SDA_TX_PIN_PIN) */

#if (SPI_PI_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    SPI_PI_ss0_m_Write(SPI_PI_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS0_M_HSIOM_REG, SPI_PI_SS0_M_HSIOM_MASK,
                                   SPI_PI_SS0_M_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS0_PIN) */

#if (SPI_PI_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    SPI_PI_ss1_m_Write(SPI_PI_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS1_M_HSIOM_REG, SPI_PI_SS1_M_HSIOM_MASK,
                                   SPI_PI_SS1_M_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS1_PIN) */

#if (SPI_PI_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    SPI_PI_ss2_m_Write(SPI_PI_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS2_M_HSIOM_REG, SPI_PI_SS2_M_HSIOM_MASK,
                                   SPI_PI_SS2_M_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS2_PIN) */

#if (SPI_PI_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    SPI_PI_ss3_m_Write(SPI_PI_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    SPI_PI_SET_HSIOM_SEL(SPI_PI_SS3_M_HSIOM_REG, SPI_PI_SS3_M_HSIOM_MASK,
                                   SPI_PI_SS3_M_HSIOM_POS, SPI_PI_HSIOM_GPIO_SEL);
#endif /* (SPI_PI_SPI_MASTER_SS3_PIN) */

#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SPI_PI_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: SPI_PI_SetActiveSlaveSelect
    ********************************************************************************
    *
    * Summary:
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set)
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    * Parameters:
    *  slaveSelect: slave select line which will be active while the following
    *               transfer.
    *   SPI_PI_SPI_SLAVE_SELECT0 - Slave select 0
    *   SPI_PI_SPI_SLAVE_SELECT1 - Slave select 1
    *   SPI_PI_SPI_SLAVE_SELECT2 - Slave select 2
    *   SPI_PI_SPI_SLAVE_SELECT3 - Slave select 3
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = SPI_PI_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~SPI_PI_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  SPI_PI_GET_SPI_CTRL_SS(slaveSelect);

        SPI_PI_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (SPI_PI_SPI_MASTER_CONST) */


#if !(SPI_PI_CY_SCBIP_V0 || SPI_PI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPI_PI_SpiSetSlaveSelectPolarity
    ********************************************************************************
    *
    * Summary:
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  This function does not check that these conditions are met.
    *
    * Parameters:
    *  slaveSelect: slave select line to change active polarity.
    *   SPI_PI_SPI_SLAVE_SELECT0 - Slave select 0
    *   SPI_PI_SPI_SLAVE_SELECT1 - Slave select 1
    *   SPI_PI_SPI_SLAVE_SELECT2 - Slave select 2
    *   SPI_PI_SPI_SLAVE_SELECT3 - Slave select 3
    *
    *  polarity: active polarity of slave select line.
    *   SPI_PI_SPI_SS_ACTIVE_LOW  - Slave select is active low
    *   SPI_PI_SPI_SS_ACTIVE_HIGH - Slave select is active high
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = SPI_PI_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            SPI_PI_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            SPI_PI_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(SPI_PI_CY_SCBIP_V0 || SPI_PI_CY_SCBIP_V1) */


#if(SPI_PI_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SPI_PI_SpiSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiSaveConfig(void)
    {
        SPI_PI_ClearSpiExtClkInterruptSource(SPI_PI_INTR_SPI_EC_WAKE_UP);
        SPI_PI_SetSpiExtClkInterruptMode(SPI_PI_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SPI_PI_SpiRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiRestoreConfig(void)
    {
        SPI_PI_SetSpiExtClkInterruptMode(SPI_PI_NO_INTR_SOURCES);
    }
#endif /* (SPI_PI_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
