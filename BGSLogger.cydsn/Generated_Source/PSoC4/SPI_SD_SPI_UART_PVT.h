/*******************************************************************************
* File Name: SPI_SD_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_SPI_SD_H)
#define CY_SCB_SPI_UART_PVT_SPI_SD_H

#include "SPI_SD_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(SPI_SD_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SPI_SD_rxBufferHead;
    extern volatile uint32  SPI_SD_rxBufferTail;
    extern volatile uint8   SPI_SD_rxBufferOverflow;
#endif /* (SPI_SD_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SPI_SD_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SPI_SD_txBufferHead;
    extern volatile uint32  SPI_SD_txBufferTail;
#endif /* (SPI_SD_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SPI_SD_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SPI_SD_rxBufferInternal[SPI_SD_RX_BUFFER_SIZE];
#endif /* (SPI_SD_INTERNAL_RX_SW_BUFFER) */

#if(SPI_SD_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SPI_SD_txBufferInternal[SPI_SD_TX_BUFFER_SIZE];
#endif /* (SPI_SD_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(SPI_SD_SCB_MODE_SPI_CONST_CFG)
    void SPI_SD_SpiInit(void);
#endif /* (SPI_SD_SCB_MODE_SPI_CONST_CFG) */

#if(SPI_SD_SPI_WAKE_ENABLE_CONST)
    void SPI_SD_SpiSaveConfig(void);
    void SPI_SD_SpiRestoreConfig(void);
#endif /* (SPI_SD_SPI_WAKE_ENABLE_CONST) */

#if(SPI_SD_SCB_MODE_UART_CONST_CFG)
    void SPI_SD_UartInit(void);
#endif /* (SPI_SD_SCB_MODE_UART_CONST_CFG) */

#if(SPI_SD_UART_WAKE_ENABLE_CONST)
    void SPI_SD_UartSaveConfig(void);
    void SPI_SD_UartRestoreConfig(void);
    #define SPI_SD_UartStop() \
        do{                             \
            SPI_SD_UART_RX_CTRL_REG &= ~SPI_SD_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define SPI_SD_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (SPI_SD_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define SPI_SD_SpiUartEnableIntRx(intSourceMask)  SPI_SD_SetRxInterruptMode(intSourceMask)
#define SPI_SD_SpiUartEnableIntTx(intSourceMask)  SPI_SD_SetTxInterruptMode(intSourceMask)
uint32  SPI_SD_SpiUartDisableIntRx(void);
uint32  SPI_SD_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SPI_SD_SetPins() */
#define SPI_SD_UART_RX_PIN_ENABLE    (SPI_SD_UART_RX)
#define SPI_SD_UART_TX_PIN_ENABLE    (SPI_SD_UART_TX)

/* UART RTS and CTS position to be used in  SPI_SD_SetPins() */
#define SPI_SD_UART_RTS_PIN_ENABLE    (0x10u)
#define SPI_SD_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_SPI_SD_H) */


/* [] END OF FILE */
