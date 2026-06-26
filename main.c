#include "Bala_STM32.h"
void delay1(volatile long int a){
  for(volatile long int i=0;i<a;i++){

  }
}
const uint8_t FONT_A[8] = {0x00,0x18,0x24,0x42,0x7E,0x42,0x42,0x42};
const uint8_t FONT_B[8] = {0x00,0x3E,0x42,0x3E,0x42,0x42,0x42,0x3E};
const uint8_t FONT_L[8] = {0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x7E};

void MAX7219_Send(SPI_Handle_t *pSPIHandle,
                  uint8_t Address,
                  uint8_t Data)
{
  /*  CS LOW   */
    GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

  /* Transmitt Address  */
    SPI_Transmit(pSPIHandle, &Address, 1);

  /* Transmitt Data  */
    SPI_Transmit(pSPIHandle, &Data, 1);

  /*  CS HIGH   */
    GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);


}
void MAX7219_Send_ALL(SPI_Handle_t *pSPIHandle,
                  uint8_t Address,
                  uint8_t Data1,uint8_t Data2,uint8_t Data3,uint8_t Data4)
{
  /*  CS LOW   */
    GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

  /* Transmitt Address  */
    SPI_Transmit(pSPIHandle, &Address, 1);

  /* Transmitt Data  */
    SPI_Transmit(pSPIHandle, &Data1, 1);

      /* Transmitt Address  */
    SPI_Transmit(pSPIHandle, &Address, 1);

  /* Transmitt Data  */
    SPI_Transmit(pSPIHandle, &Data2, 1);

    /* Transmitt Address  */
    SPI_Transmit(pSPIHandle, &Address, 1);

  /* Transmitt Data  */
    SPI_Transmit(pSPIHandle, &Data3, 1);

  /* Transmitt Address  */
    SPI_Transmit(pSPIHandle, &Address, 1);

  /* Transmitt Data  */
    SPI_Transmit(pSPIHandle, &Data4, 1);
  /*  CS HIGH   */
    GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

}
void MAX7219_Init(SPI_Handle_t *pSPIHandle)
{
    /* Display OFF test  */
    MAX7219_Send(pSPIHandle,0x0F,0x00);

    /* Normal Operation */
    MAX7219_Send(pSPIHandle,0x0C,0x01);

    /* Scan All 8 Rows */
    MAX7219_Send(pSPIHandle,0x0B,0x07);

}

int main(void){

  GPIO_Handle_t GPIOHandle;

  RCC_GPIOClockControl(GPIOA, ENABLE);

  GPIOHandle.pGPIOx = GPIOA;

  GPIOHandle.GPIO_PinConfig.PinMode       = GPIO_MODE_ALTFN;
  GPIOHandle.GPIO_PinConfig.PinAltFunMode = GPIO_AF0;
  GPIOHandle.GPIO_PinConfig.PinSpeed = GPIO_SPEED_HIGH;
  GPIOHandle.GPIO_PinConfig.PinPullControl = GPIO_NO_PUPD;
  GPIOHandle.GPIO_PinConfig.PinOutputType = GPIO_OP_TYPE_PP;

  /* PA7 */
  GPIOHandle.GPIO_PinConfig.PinNumber = GPIO_PIN_7;
  GPIO_Init(&GPIOHandle);

  /* PA5 */
  GPIOHandle.GPIO_PinConfig.PinNumber = GPIO_PIN_5;
  GPIO_Init(&GPIOHandle);

  /* PA4 */
  GPIOHandle.GPIO_PinConfig.PinMode       = GPIO_MODE_OUT;
  GPIOHandle.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
  GPIO_Init(&GPIOHandle);



  /*   SPI INITIALISATION   */
  SPI_Handle_t SPIHandle;
  RCC_SPIClockControl(SPI1, ENABLE);
  SPIHandle.pSPIx=SPI1;
  SPIHandle.SPIConfig.DeviceMode = SPI_DEVICE_MODE_MASTER;
  SPIHandle.SPIConfig.BusConfig  = SPI_BUS_CONFIG_FD;
  SPIHandle.SPIConfig.SclkSpeed  = SPI_SCLK_DIV8;
  SPIHandle.SPIConfig.DataSize   = SPI_DATASIZE_8BIT;
  SPIHandle.SPIConfig.CPOL       = SPI_CPOL_LOW;
  SPIHandle.SPIConfig.CPHA       = SPI_CPHA_LOW;
  SPIHandle.SPIConfig.BitOrder   = SPI_FIRSTBIT_MSB;
  SPIHandle.SPIConfig.SSM        = SPI_SSM_ENABLE;

  SPI_Init(&SPIHandle);
  SPI_SSIConfig(SPI1, ENABLE);
  SPI_PeripheralControl(SPI1, ENABLE);

  GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

  /* Test -1 :Entire Matrix On  */
  MAX7219_Init(&SPIHandle);

  for (uint8_t row = 0; row < 8; row++)
  {
      MAX7219_Send_ALL(&SPIHandle,
                      row + 1,
                      FONT_B[row],
                      FONT_A[row],
                      FONT_L[row],
                      FONT_A[row]);
  }
  while(1);
}