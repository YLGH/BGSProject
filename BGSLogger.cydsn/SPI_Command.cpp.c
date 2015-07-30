/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <Command.h>
#include <SPI_Command.h>

void spiPutArray(uint8 dat[], uint32 len){
    SPI_PI_SpiUartPutArray(dat, len);
}

CY_ISR(SPI_COMMAND_CPP_ISR){
    uint8 val = SPI_PI_SpiUartReadRxData();
    
    SPI_PI_INTR_RX_REG = 0xFF;
    
    Command_Process_Char(val, SPI_PI_SpiUartClearTxBuffer, SPI_PI_SpiUartWriteTxData, spiPutArray);
}

/* [] END OF FILE */
