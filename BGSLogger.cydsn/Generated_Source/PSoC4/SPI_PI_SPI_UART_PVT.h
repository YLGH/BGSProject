/*******************************************************************************
* File Name: SPI_PI_SPI_UART_PVT.h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_SPI_PI_H)
#define CY_SCB_SPI_UART_PVT_SPI_PI_H

#include "SPI_PI_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SPI_PI_rxBufferHead;
    extern volatile uint32  SPI_PI_rxBufferTail;
    extern volatile uint8   SPI_PI_rxBufferOverflow;
#endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SPI_PI_txBufferHead;
    extern volatile uint32  SPI_PI_txBufferTail;
#endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER_CONST) */

#if (SPI_PI_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SPI_PI_rxBufferInternal[SPI_PI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SPI_PI_INTERNAL_RX_SW_BUFFER) */

#if (SPI_PI_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SPI_PI_txBufferInternal[SPI_PI_TX_BUFFER_SIZE];
#endif /* (SPI_PI_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void SPI_PI_SpiPostEnable(void);
void SPI_PI_SpiStop(void);

#if (SPI_PI_SCB_MODE_SPI_CONST_CFG)
    void SPI_PI_SpiInit(void);
#endif /* (SPI_PI_SCB_MODE_SPI_CONST_CFG) */

#if (SPI_PI_SPI_WAKE_ENABLE_CONST)
    void SPI_PI_SpiSaveConfig(void);
    void SPI_PI_SpiRestoreConfig(void);
#endif /* (SPI_PI_SPI_WAKE_ENABLE_CONST) */

void SPI_PI_UartPostEnable(void);
void SPI_PI_UartStop(void);

#if (SPI_PI_SCB_MODE_UART_CONST_CFG)
    void SPI_PI_UartInit(void);
#endif /* (SPI_PI_SCB_MODE_UART_CONST_CFG) */

#if (SPI_PI_UART_WAKE_ENABLE_CONST)
    void SPI_PI_UartSaveConfig(void);
    void SPI_PI_UartRestoreConfig(void);
#endif /* (SPI_PI_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SPI_PI_SetPins() */
#define SPI_PI_UART_RX_PIN_ENABLE    (SPI_PI_UART_RX)
#define SPI_PI_UART_TX_PIN_ENABLE    (SPI_PI_UART_TX)

/* UART RTS and CTS position to be used in  SPI_PI_SetPins() */
#define SPI_PI_UART_RTS_PIN_ENABLE    (0x10u)
#define SPI_PI_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define SPI_PI_SpiUartEnableIntRx(intSourceMask)  SPI_PI_SetRxInterruptMode(intSourceMask)
#define SPI_PI_SpiUartEnableIntTx(intSourceMask)  SPI_PI_SetTxInterruptMode(intSourceMask)
uint32  SPI_PI_SpiUartDisableIntRx(void);
uint32  SPI_PI_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_SPI_PI_H) */


/* [] END OF FILE */
