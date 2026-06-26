#include "spi.h"
void SPI_Init(SPI_Handle_t *pSPIHandle){


  /*  DEVICE MODE              */
      pSPIHandle->pSPIx->CR1&=~(1U<<SPI_CR1_MSTR_BIT);
      pSPIHandle->pSPIx->CR1|=((pSPIHandle->SPIConfig.DeviceMode)<< SPI_CR1_MSTR_BIT);

  /* BUS CONFIGURATION  */
  if(pSPIHandle->SPIConfig.BusConfig==SPI_BUS_CONFIG_FD){
      pSPIHandle->pSPIx->CR1&=~(1U<<SPI_CR1_RXONLY);
      pSPIHandle->pSPIx->CR1&=~(1U<<SPI_CR1_BIDIMODE);
  }
  else if(pSPIHandle->SPIConfig.BusConfig==SPI_BUS_CONFIG_HD){
      pSPIHandle->pSPIx->CR1|=(1U<<SPI_CR1_BIDIMODE);
  }
  else if(pSPIHandle->SPIConfig.BusConfig==SPI_BUS_CONFIG_SIMPLEX_RX){
      pSPIHandle->pSPIx->CR1&=~(1U<<SPI_CR1_BIDIMODE);
      pSPIHandle->pSPIx->CR1|=(1U<<SPI_CR1_RXONLY);
  }

  /*  SclkSpeed  */
      pSPIHandle->pSPIx->CR1&=~(7U<<3U);
      pSPIHandle->pSPIx->CR1|=((pSPIHandle->SPIConfig.SclkSpeed)<<SPI_CR1_BR);
  
  /*  Data Frame Format */
      pSPIHandle->pSPIx->CR2&=~(15U<<8U);
      pSPIHandle->pSPIx->CR2|=((pSPIHandle->SPIConfig.DataSize)<<SPI_CR2_DS); 

  /*  CPOL              */
      pSPIHandle->pSPIx->CR1&=~(1U<<1U);
      pSPIHandle->pSPIx->CR1|=((pSPIHandle->SPIConfig.CPOL)<< SPI_CR1_CPOL);     

  /*  CPHA              */
      pSPIHandle->pSPIx->CR1&=~(1U);
      pSPIHandle->pSPIx->CR1|=((pSPIHandle->SPIConfig.CPHA));    

  /*  SSM               */
      pSPIHandle->pSPIx->CR1&=~(1U<<9U);
      pSPIHandle->pSPIx->CR1|=((pSPIHandle->SPIConfig.SSM)<< SPI_CR1_SSM);  

  /*  BitOrder              */
      pSPIHandle->pSPIx->CR1&=~(1U<<7U);
      pSPIHandle->pSPIx->CR1|=((pSPIHandle->SPIConfig.BitOrder)<< SPI_CR1_BitOrder);   

}
void SPI_Transmit(SPI_Handle_t *pSPIHandle,
                  uint8_t *pTxBuffer,
                  uint32_t Len)
            
{

    while(Len>0){
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_TXE) & 1U));
    *(volatile uint8_t *)&pSPIHandle->pSPIx->DR = *pTxBuffer;
    pTxBuffer++;
    Len--;
    }
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_TXE) & 1U));
    while((pSPIHandle->pSPIx->SR>>SPI_SR_BSY)& 1U);

}

void SPI_Receive(SPI_Handle_t *pSPIHandle,
                 uint8_t *pRxBuffer,
                 uint32_t Len)
{
  while(Len>0){
  if(pSPIHandle->SPIConfig.DeviceMode==SPI_DEVICE_MODE_MASTER){
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_TXE) & 1U));
    pSPIHandle->pSPIx->DR=0xFF;//dummy byte
  }
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_RXNE) & 1U));
    *pRxBuffer = *(volatile uint8_t *)&pSPIHandle->pSPIx->DR;
    Len--;
    pRxBuffer++;
    }

    while((pSPIHandle->pSPIx->SR>>SPI_SR_BSY)& 1U);
}

void SPI_TransmitReceive(SPI_Handle_t *pSPIHandle,
                         uint8_t *pTxBuffer,
                         uint8_t *pRxBuffer,
                         uint32_t Len)
{
    while(Len>0){
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_TXE) & 1U));
    *(volatile uint8_t *)&pSPIHandle->pSPIx->DR = *pTxBuffer;
    pTxBuffer++;
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_RXNE) & 1U));
    *pRxBuffer = *(volatile uint8_t *)&pSPIHandle->pSPIx->DR;
    pRxBuffer++;
    Len--;

    }
    while(!((pSPIHandle->pSPIx->SR >> SPI_SR_TXE) & 1U));
    while((pSPIHandle->pSPIx->SR>>SPI_SR_BSY)& 1U);

}


void SPI_SSIConfig(SPI_TypeDef *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi==ENABLE){
        pSPIx->CR1|=(1U << SPI_CR1_SSI);
    }
    else{
        pSPIx->CR1&=~(1U << SPI_CR1_SSI);      
    }
}
void SPI_PeripheralControl(SPI_TypeDef *pSPIx,
                           uint8_t EnOrDi)
{
    if(EnOrDi==ENABLE){
        pSPIx->CR1|=(1U << SPI_CR1_SPE);
    }
    else{
        pSPIx->CR1&=~(1U << SPI_CR1_SPE);      
    }   
}