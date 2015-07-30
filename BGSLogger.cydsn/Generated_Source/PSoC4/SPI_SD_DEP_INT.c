/*******************************************************************************
* File Name: SPI_SD_DEP_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_SD_DEP_PVT.h"

/* User code required at start of ISR */
/* `#START SPI_SD_DEP_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPI_SD_DEP_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_SD_DEP_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPI_SD_DEP_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPI_SD_DEP_txBuffer[SPI_SD_DEP_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPI_SD_DEP_TX_ISR)
{
    #if(SPI_SD_DEP_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SPI_SD_DEP_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START SPI_SD_DEP_TX_ISR_START` */

    /* `#END` */

    #if(SPI_SD_DEP_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(SPI_SD_DEP_txBufferRead != SPI_SD_DEP_txBufferWrite)
        {
            tmpStatus = SPI_SD_DEP_GET_STATUS_TX(SPI_SD_DEP_swStatusTx);
            SPI_SD_DEP_swStatusTx = tmpStatus;

            if(0u != (SPI_SD_DEP_swStatusTx & SPI_SD_DEP_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == SPI_SD_DEP_txBufferFull)
                {
                   SPI_SD_DEP_txBufferRead++;

                    if(SPI_SD_DEP_txBufferRead >= SPI_SD_DEP_TX_BUFFER_SIZE)
                    {
                        SPI_SD_DEP_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPI_SD_DEP_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(SPI_SD_DEP_TXDATA_PTR, 
                                             SPI_SD_DEP_txBuffer[SPI_SD_DEP_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(SPI_SD_DEP_txBufferRead == SPI_SD_DEP_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            SPI_SD_DEP_TX_STATUS_MASK_REG &= ((uint8) ~SPI_SD_DEP_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (SPI_SD_DEP_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPI_SD_DEP_TX_ISR_END` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: SPI_SD_DEP_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_SD_DEP_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPI_SD_DEP_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPI_SD_DEP_rxBuffer[SPI_SD_DEP_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPI_SD_DEP_RX_ISR)
{
    #if(SPI_SD_DEP_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (SPI_SD_DEP_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START SPI_SD_DEP_RX_ISR_START` */

    /* `#END` */

    #if(SPI_SD_DEP_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = SPI_SD_DEP_GET_STATUS_RX(SPI_SD_DEP_swStatusRx);
        SPI_SD_DEP_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (SPI_SD_DEP_swStatusRx & SPI_SD_DEP_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(SPI_SD_DEP_RXDATA_PTR);

            /* Set next pointer. */
            SPI_SD_DEP_rxBufferWrite++;
            if(SPI_SD_DEP_rxBufferWrite >= SPI_SD_DEP_RX_BUFFER_SIZE)
            {
                SPI_SD_DEP_rxBufferWrite = 0u;
            }

            if(SPI_SD_DEP_rxBufferWrite == SPI_SD_DEP_rxBufferRead)
            {
                SPI_SD_DEP_rxBufferRead++;
                if(SPI_SD_DEP_rxBufferRead >= SPI_SD_DEP_RX_BUFFER_SIZE)
                {
                    SPI_SD_DEP_rxBufferRead = 0u;
                }

                SPI_SD_DEP_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPI_SD_DEP_rxBuffer[SPI_SD_DEP_rxBufferWrite] = rxData;

            tmpStatus = SPI_SD_DEP_GET_STATUS_RX(SPI_SD_DEP_swStatusRx);
            SPI_SD_DEP_swStatusRx = tmpStatus;
        }

    #endif /* (SPI_SD_DEP_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPI_SD_DEP_RX_ISR_END` */

    /* `#END` */
}

/* [] END OF FILE */
