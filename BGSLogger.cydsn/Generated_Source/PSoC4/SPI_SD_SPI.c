/*******************************************************************************
* File Name: SPI_SD_SPI.c
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

#include "SPI_SD_PVT.h"
#include "SPI_SD_SPI_UART_PVT.h"

#if(SPI_SD_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SPI_SD_SPI_INIT_STRUCT SPI_SD_configSpi =
    {
        SPI_SD_SPI_MODE,
        SPI_SD_SPI_SUB_MODE,
        SPI_SD_SPI_CLOCK_MODE,
        SPI_SD_SPI_OVS_FACTOR,
        SPI_SD_SPI_MEDIAN_FILTER_ENABLE,
        SPI_SD_SPI_LATE_MISO_SAMPLE_ENABLE,
        SPI_SD_SPI_WAKE_ENABLE,
        SPI_SD_SPI_RX_DATA_BITS_NUM,
        SPI_SD_SPI_TX_DATA_BITS_NUM,
        SPI_SD_SPI_BITS_ORDER,
        SPI_SD_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) SPI_SD_SCB_IRQ_INTERNAL,
        SPI_SD_SPI_INTR_RX_MASK,
        SPI_SD_SPI_RX_TRIGGER_LEVEL,
        SPI_SD_SPI_INTR_TX_MASK,
        SPI_SD_SPI_TX_TRIGGER_LEVEL,
        (uint8) SPI_SD_SPI_BYTE_MODE_ENABLE,
        (uint8) SPI_SD_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) SPI_SD_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: SPI_SD_SpiInit
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
    void SPI_SD_SpiInit(const SPI_SD_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SPI_SD_SetPins(SPI_SD_SCB_MODE_SPI, config->mode, SPI_SD_DUMMY_PARAM);

            /* Store internal configuration */
            SPI_SD_scbMode       = (uint8) SPI_SD_SCB_MODE_SPI;
            SPI_SD_scbEnableWake = (uint8) config->enableWake;
            SPI_SD_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SPI_SD_rxBuffer      =         config->rxBuffer;
            SPI_SD_rxDataBits    = (uint8) config->rxDataBits;
            SPI_SD_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            SPI_SD_txBuffer      =         config->txBuffer;
            SPI_SD_txDataBits    = (uint8) config->txDataBits;
            SPI_SD_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure SPI interface */
            SPI_SD_CTRL_REG     = SPI_SD_GET_CTRL_OVS(config->oversample)           |
                                            SPI_SD_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            SPI_SD_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            SPI_SD_CTRL_SPI;

            SPI_SD_SPI_CTRL_REG = SPI_SD_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SPI_SD_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SPI_SD_SPI_MODE_TI_PRECEDES_MASK) |
                                            SPI_SD_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SPI_SD_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SPI_SD_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            SPI_SD_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            SPI_SD_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SPI_SD_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SPI_SD_RX_CTRL_REG     =  SPI_SD_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SPI_SD_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SPI_SD_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SPI_SD_SPI_RX_CTRL;

            SPI_SD_RX_FIFO_CTRL_REG = SPI_SD_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SPI_SD_TX_CTRL_REG      = SPI_SD_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SPI_SD_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SPI_SD_SPI_TX_CTRL;

            SPI_SD_TX_FIFO_CTRL_REG = SPI_SD_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (SPI_SD_ISR_NUMBER);
            CyIntSetPriority(SPI_SD_ISR_NUMBER, SPI_SD_ISR_PRIORITY);
            (void) CyIntSetVector(SPI_SD_ISR_NUMBER, &SPI_SD_SPI_UART_ISR);

            /* Configure interrupt sources */
            SPI_SD_INTR_I2C_EC_MASK_REG = SPI_SD_NO_INTR_SOURCES;
            SPI_SD_INTR_SPI_EC_MASK_REG = SPI_SD_NO_INTR_SOURCES;
            SPI_SD_INTR_SLAVE_MASK_REG  = SPI_SD_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SPI_SD_INTR_MASTER_MASK_REG = SPI_SD_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SPI_SD_INTR_RX_MASK_REG     = SPI_SD_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SPI_SD_INTR_TX_MASK_REG     = SPI_SD_GET_SPI_INTR_TX_MASK(config->txInterruptMask);

            /* Set active SS0 */
            SPI_SD_SpiSetActiveSlaveSelect(SPI_SD_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            SPI_SD_rxBufferHead     = 0u;
            SPI_SD_rxBufferTail     = 0u;
            SPI_SD_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SPI_SD_txBufferHead = 0u;
            SPI_SD_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SPI_SD_SpiInit
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
    void SPI_SD_SpiInit(void)
    {
        /* Configure SPI interface */
        SPI_SD_CTRL_REG     = SPI_SD_SPI_DEFAULT_CTRL;
        SPI_SD_SPI_CTRL_REG = SPI_SD_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SPI_SD_RX_CTRL_REG      = SPI_SD_SPI_DEFAULT_RX_CTRL;
        SPI_SD_RX_FIFO_CTRL_REG = SPI_SD_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SPI_SD_TX_CTRL_REG      = SPI_SD_SPI_DEFAULT_TX_CTRL;
        SPI_SD_TX_FIFO_CTRL_REG = SPI_SD_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(SPI_SD_SCB_IRQ_INTERNAL)
            CyIntDisable    (SPI_SD_ISR_NUMBER);
            CyIntSetPriority(SPI_SD_ISR_NUMBER, SPI_SD_ISR_PRIORITY);
            (void) CyIntSetVector(SPI_SD_ISR_NUMBER, &SPI_SD_SPI_UART_ISR);
    #endif /* (SPI_SD_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        SPI_SD_INTR_I2C_EC_MASK_REG = SPI_SD_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SPI_SD_INTR_SPI_EC_MASK_REG = SPI_SD_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SPI_SD_INTR_SLAVE_MASK_REG  = SPI_SD_SPI_DEFAULT_INTR_SLAVE_MASK;
        SPI_SD_INTR_MASTER_MASK_REG = SPI_SD_SPI_DEFAULT_INTR_MASTER_MASK;
        SPI_SD_INTR_RX_MASK_REG     = SPI_SD_SPI_DEFAULT_INTR_RX_MASK;
        SPI_SD_INTR_TX_MASK_REG     = SPI_SD_SPI_DEFAULT_INTR_TX_MASK;

        /* Set active SS0 for master */
    #if (SPI_SD_SPI_MASTER_CONST)
        SPI_SD_SpiSetActiveSlaveSelect(SPI_SD_SPI_SLAVE_SELECT0);
    #endif /* (SPI_SD_SPI_MASTER_CONST) */

    #if(SPI_SD_INTERNAL_RX_SW_BUFFER_CONST)
        SPI_SD_rxBufferHead     = 0u;
        SPI_SD_rxBufferTail     = 0u;
        SPI_SD_rxBufferOverflow = 0u;
    #endif /* (SPI_SD_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SPI_SD_INTERNAL_TX_SW_BUFFER_CONST)
        SPI_SD_txBufferHead = 0u;
        SPI_SD_txBufferTail = 0u;
    #endif /* (SPI_SD_INTERNAL_TX_SW_BUFFER_CONST) */


    }
#endif /* (SPI_SD_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SPI_SD_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: SPI_SD_SetActiveSlaveSelect
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
    *   SPI_SD_SPI_SLAVE_SELECT0 - Slave select 0
    *   SPI_SD_SPI_SLAVE_SELECT1 - Slave select 1
    *   SPI_SD_SPI_SLAVE_SELECT2 - Slave select 2
    *   SPI_SD_SPI_SLAVE_SELECT3 - Slave select 3
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_SD_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = SPI_SD_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~SPI_SD_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  SPI_SD_GET_SPI_CTRL_SS(slaveSelect);

        SPI_SD_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (SPI_SD_SPI_MASTER_CONST) */


#if !(SPI_SD_CY_SCBIP_V0 || SPI_SD_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPI_SD_SpiSetSlaveSelectPolarity
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
    *   SPI_SD_SPI_SLAVE_SELECT0 - Slave select 0
    *   SPI_SD_SPI_SLAVE_SELECT1 - Slave select 1
    *   SPI_SD_SPI_SLAVE_SELECT2 - Slave select 2
    *   SPI_SD_SPI_SLAVE_SELECT3 - Slave select 3
    *
    *  polarity: active polarity of slave select line.
    *   SPI_SD_SPI_SS_ACTIVE_LOW  - Slave select is active low
    *   SPI_SD_SPI_SS_ACTIVE_HIGH - Slave select is active high
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_SD_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = SPI_SD_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            SPI_SD_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            SPI_SD_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(SPI_SD_CY_SCBIP_V0 || SPI_SD_CY_SCBIP_V1) */


#if(SPI_SD_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SPI_SD_SpiSaveConfig
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
    void SPI_SD_SpiSaveConfig(void)
    {
        SPI_SD_ClearSpiExtClkInterruptSource(SPI_SD_INTR_SPI_EC_WAKE_UP);
        SPI_SD_SetSpiExtClkInterruptMode(SPI_SD_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SPI_SD_SpiRestoreConfig
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
    void SPI_SD_SpiRestoreConfig(void)
    {
        SPI_SD_SetSpiExtClkInterruptMode(SPI_SD_NO_INTR_SOURCES);
    }
#endif /* (SPI_SD_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
