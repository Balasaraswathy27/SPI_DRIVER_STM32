#include "rcc.h"
void RCC_GPIOClockControl(GPIO_TypeDef *pGPIOx,
                          uint8_t EnOrDi)
{
    uint8_t bitPos;

    if(pGPIOx == GPIOA)
        bitPos = GPIOA_RCC_EN_BIT;
    else if(pGPIOx == GPIOB)
        bitPos = GPIOB_RCC_EN_BIT;
    else if(pGPIOx == GPIOC)
        bitPos = GPIOC_RCC_EN_BIT;
    else if(pGPIOx == GPIOD)
        bitPos = GPIOD_RCC_EN_BIT;
    else if(pGPIOx == GPIOF)
        bitPos = GPIOF_RCC_EN_BIT;
    else
        return;

    if(EnOrDi == ENABLE)
        RCC->IOPENR |= (1U << bitPos);
    else
        RCC->IOPENR &= ~(1U << bitPos);
}

void RCC_SPIClockControl(SPI_TypeDef *pSPIx,
                         uint8_t EnOrDi)
{
    if(pSPIx == SPI1)
    {
        if(EnOrDi == ENABLE)
        {
            RCC->APBENR2 |= (1U << SPI1_RCC_EN_BIT);
        }
        else
        {
            RCC->APBENR2 &= ~(1U << SPI1_RCC_EN_BIT);
        }
    }
    else if(pSPIx == SPI2)
    {
        if(EnOrDi == ENABLE)
        {
            RCC->APBENR1 |= (1U << SPI2_RCC_EN_BIT);
        }
        else
        {
            RCC->APBENR1 &= ~(1U << SPI2_RCC_EN_BIT);
        }
    }
}