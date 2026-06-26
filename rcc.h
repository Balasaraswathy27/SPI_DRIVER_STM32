#ifndef RCC_H
#define RCC_H
#include "reg_map.h"
#include<stdint.h>

#define ENABLE              1
#define GPIOA_RCC_EN_BIT    0
#define GPIOB_RCC_EN_BIT    1
#define GPIOC_RCC_EN_BIT    2
#define GPIOD_RCC_EN_BIT    3
#define GPIOF_RCC_EN_BIT    5

#define SPI1_RCC_EN_BIT    12
#define SPI2_RCC_EN_BIT    14

void RCC_GPIOClockControl(GPIO_TypeDef *pGPIOx,
                          uint8_t EnOrDi);

void RCC_SPIClockControl(SPI_TypeDef *pSPIx,
                          uint8_t EnOrDi);

#endif