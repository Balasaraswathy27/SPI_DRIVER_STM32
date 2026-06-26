#ifndef SPI_H
#define SPI_H
#include "reg_map.h"
#include<stdint.h>
#define ENABLE                    1
/*=========================================================
                    DEVICE MODE
=========================================================*/

#define SPI_DEVICE_MODE_SLAVE      0
#define SPI_DEVICE_MODE_MASTER     1

/*=========================================================
                    BUS CONFIG
=========================================================*/

#define SPI_BUS_CONFIG_FD          0   // Full Duplex
#define SPI_BUS_CONFIG_HD          1   // Half Duplex
#define SPI_BUS_CONFIG_SIMPLEX_RX  2

/*=========================================================
                    CLOCK SPEED
=========================================================*/

#define SPI_SCLK_DIV2              0
#define SPI_SCLK_DIV4              1
#define SPI_SCLK_DIV8              2
#define SPI_SCLK_DIV16             3
#define SPI_SCLK_DIV32             4
#define SPI_SCLK_DIV64             5
#define SPI_SCLK_DIV128            6
#define SPI_SCLK_DIV256            7

/*=========================================================
                    SPI DATA SIZE
=========================================================*/

#define SPI_DATASIZE_4BIT      3
#define SPI_DATASIZE_5BIT      4
#define SPI_DATASIZE_6BIT      5
#define SPI_DATASIZE_7BIT      6
#define SPI_DATASIZE_8BIT      7
#define SPI_DATASIZE_9BIT      8
#define SPI_DATASIZE_10BIT     9
#define SPI_DATASIZE_11BIT     10
#define SPI_DATASIZE_12BIT     11
#define SPI_DATASIZE_13BIT     12
#define SPI_DATASIZE_14BIT     13
#define SPI_DATASIZE_15BIT     14
#define SPI_DATASIZE_16BIT     15

/*=========================================================
                    CLOCK POLARITY
=========================================================*/

#define SPI_CPOL_LOW               0
#define SPI_CPOL_HIGH              1


/*=========================================================
                    CLOCK PHASE
=========================================================*/

#define SPI_CPHA_LOW               0
#define SPI_CPHA_HIGH              1

/*=========================================================
                    SOFTWARE SLAVE MANAGEMENT
=========================================================*/

#define SPI_SSM_DISABLE            0
#define SPI_SSM_ENABLE             1

/*=========================================================
                    BIT ORDER
=========================================================*/

#define SPI_FIRSTBIT_MSB           0
#define SPI_FIRSTBIT_LSB           1


#define SPI_CR1_MSTR_BIT 2
#define SPI_CR1_RXONLY   10
#define SPI_CR1_BIDIMODE 15
#define SPI_CR1_BR       3
#define SPI_CR2_DS       8
#define SPI_CR1_CPOL     1
#define SPI_CR1_SSM      9
#define SPI_CR1_BitOrder 7
#define SPI_CR1_SSI     8U
#define SPI_CR1_SPE     6U

#define SPI_SR_TXE       1
#define SPI_SR_BSY       7
#define SPI_SR_RXNE      0



typedef struct
{
    uint8_t DeviceMode;
    uint8_t BusConfig;
    uint8_t SclkSpeed;
    uint8_t DataSize;
    uint8_t CPOL;
    uint8_t CPHA;
    uint8_t SSM;
    uint8_t BitOrder;

} SPI_Config_t;


typedef struct
{
    SPI_TypeDef *pSPIx;
    SPI_Config_t SPIConfig;

} SPI_Handle_t;

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_SSIConfig(SPI_TypeDef *pSPIx, uint8_t EnOrDi);
void SPI_PeripheralControl(SPI_TypeDef *pSPIx,
                           uint8_t EnOrDi);
void SPI_Transmit(SPI_Handle_t *pSPIHandle,
                  uint8_t *pTxBuffer,
                  uint32_t Len);

void SPI_Receive(SPI_Handle_t *pSPIHandle,
                 uint8_t *pRxBuffer,
                 uint32_t Len);

void SPI_TransmitReceive(SPI_Handle_t *pSPIHandle,
                         uint8_t *pTxBuffer,
                         uint8_t *pRxBuffer,
                         uint32_t Len);
#endif