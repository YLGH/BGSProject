/*******************************************************************************
* File Name: SPI_PI_SPI_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(SPI_PI_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 SPI_PI_rxBufferHead;
    volatile uint32 SPI_PI_rxBufferTail;
    volatile uint8  SPI_PI_rxBufferOverflow;
#endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SPI_PI_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 SPI_PI_txBufferHead;
    volatile uint32 SPI_PI_txBufferTail;
#endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SPI_PI_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 SPI_PI_rxBufferInternal[SPI_PI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER) */

#if(SPI_PI_INTERNAL_TX_SW_BUFFER)
    volatile uint8 SPI_PI_txBufferInternal[SPI_PI_TX_BUFFER_SIZE];
#endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER) */


#if(SPI_PI_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into SPI_PI_SpiInit for description.
    *
    *******************************************************************************/
    uint32 SPI_PI_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SPI_PI_CHECK_RX_SW_BUFFER)
        {
            if (SPI_PI_rxBufferHead != SPI_PI_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (SPI_PI_rxBufferTail + 1u);

                if (SPI_PI_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = SPI_PI_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                SPI_PI_rxBufferTail = locTail;

                #if (SPI_PI_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (SPI_PI_INTR_RX_MASK_REG & SPI_PI_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        SPI_PI_INTR_RX_MASK_REG |= SPI_PI_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = SPI_PI_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 SPI_PI_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SPI_PI_CHECK_RX_SW_BUFFER)
        {
            locHead = SPI_PI_rxBufferHead;

            if(locHead >= SPI_PI_rxBufferTail)
            {
                size = (locHead - SPI_PI_rxBufferTail);
            }
            else
            {
                size = (locHead + (SPI_PI_INTERNAL_RX_BUFFER_SIZE - SPI_PI_rxBufferTail));
            }
        }
        #else
        {
            size = SPI_PI_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiUartClearRxBuffer(void)
    {
        #if (SPI_PI_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SPI_PI_DisableInt();

            /* Flush RX software buffer */
            SPI_PI_rxBufferHead = SPI_PI_rxBufferTail;
            SPI_PI_rxBufferOverflow = 0u;

            SPI_PI_CLEAR_RX_FIFO;
            SPI_PI_ClearRxInterruptSource(SPI_PI_INTR_RX_ALL);

            #if (SPI_PI_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                SPI_PI_INTR_RX_MASK_REG |= SPI_PI_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            SPI_PI_EnableInt();
        }
        #else
        {
            SPI_PI_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (SPI_PI_RX_DIRECTION) */


#if(SPI_PI_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiUartWriteTxData(uint32 txData)
    {
    #if (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SPI_PI_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((SPI_PI_txBufferHead == SPI_PI_txBufferTail) &&
                (SPI_PI_SPI_UART_FIFO_SIZE != SPI_PI_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                SPI_PI_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (SPI_PI_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (SPI_PI_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == SPI_PI_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                SPI_PI_ClearTxInterruptSource(SPI_PI_INTR_TX_NOT_FULL);

                SPI_PI_PutWordInTxBuffer(locHead, txData);

                SPI_PI_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (SPI_PI_INTR_TX_MASK_REG & SPI_PI_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    SPI_PI_INTR_TX_MASK_REG |= (uint32) SPI_PI_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (SPI_PI_SPI_UART_FIFO_SIZE == SPI_PI_GET_TX_FIFO_ENTRIES)
            {
            }

            SPI_PI_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            SPI_PI_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 SPI_PI_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SPI_PI_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = SPI_PI_txBufferTail;

            if (SPI_PI_txBufferHead >= locTail)
            {
                size = (SPI_PI_txBufferHead - locTail);
            }
            else
            {
                size = (SPI_PI_txBufferHead + (SPI_PI_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = SPI_PI_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SPI_PI_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_SpiUartClearTxBuffer(void)
    {
        #if (SPI_PI_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SPI_PI_DisableInt();

            /* Flush TX software buffer */
            SPI_PI_txBufferHead = SPI_PI_txBufferTail;

            SPI_PI_INTR_TX_MASK_REG &= (uint32) ~SPI_PI_INTR_TX_NOT_FULL;
            SPI_PI_CLEAR_TX_FIFO;
            SPI_PI_ClearTxInterruptSource(SPI_PI_INTR_TX_ALL);

            /* Release lock */
            SPI_PI_EnableInt();
        }
        #else
        {
            SPI_PI_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (SPI_PI_TX_DIRECTION) */


/*******************************************************************************
* Function Name: SPI_PI_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 SPI_PI_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = SPI_PI_GetRxInterruptMode();

    SPI_PI_SetRxInterruptMode(SPI_PI_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: SPI_PI_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 SPI_PI_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = SPI_PI_GetTxInterruptMode();

    SPI_PI_SetTxInterruptMode(SPI_PI_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SPI_PI_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (SPI_PI_ONE_BYTE_WIDTH == SPI_PI_rxDataBits)
        {
            SPI_PI_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            SPI_PI_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            SPI_PI_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SPI_PI_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 SPI_PI_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (SPI_PI_ONE_BYTE_WIDTH == SPI_PI_rxDataBits)
        {
            value = SPI_PI_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) SPI_PI_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)SPI_PI_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: SPI_PI_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI_PI_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (SPI_PI_ONE_BYTE_WIDTH == SPI_PI_txDataBits)
        {
            SPI_PI_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            SPI_PI_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            SPI_PI_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SPI_PI_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 SPI_PI_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (SPI_PI_ONE_BYTE_WIDTH == SPI_PI_txDataBits)
        {
            value = (uint32) SPI_PI_txBuffer[idx];
        }
        else
        {
            value  = (uint32) SPI_PI_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) SPI_PI_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (SPI_PI_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
