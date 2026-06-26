#ifndef REG_MAP_H
#define REG_MAP_H
#include <stdint.h>

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7
#define PIN8   8
#define PIN9   9
#define PIN10  10
#define PIN11  11
#define PIN12  12
#define PIN13  13
#define PIN14  14
#define PIN15  15

typedef struct {

  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;

}GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CFGR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t RESERVED0;
    volatile uint32_t CIER;
    volatile uint32_t CIFR;
    volatile uint32_t CICR;
    volatile uint32_t IOPRSTR;
    volatile uint32_t AHBRSTR;
    volatile uint32_t APBRSTR1;
    volatile uint32_t APBRSTR2;
    volatile uint32_t IOPENR;
    volatile uint32_t AHBENR;
    volatile uint32_t APBENR1;
    volatile uint32_t APBENR2;
} RCC_TypeDef;

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;

} SPI_TypeDef;

#define GPIOA ((GPIO_TypeDef *)0x50000000)
#define GPIOB ((GPIO_TypeDef *)0x50000400)
#define GPIOC ((GPIO_TypeDef *)0x50000800)
#define GPIOD ((GPIO_TypeDef *)0x50000C00)
#define GPIOF ((GPIO_TypeDef *)0x50001400)
#define RCC   ((RCC_TypeDef *)0x40021000)
#define SPI1  ((SPI_TypeDef *)0x40013000)
#define SPI2  ((SPI_TypeDef *)0x40003800)

#endif