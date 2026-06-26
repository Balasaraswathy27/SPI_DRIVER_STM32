#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include "reg_map.h"
/*=========================================================
                    GPIO PIN NUMBERS
=========================================================*/

#define GPIO_PIN_0         0
#define GPIO_PIN_1         1
#define GPIO_PIN_2         2
#define GPIO_PIN_3         3
#define GPIO_PIN_4         4
#define GPIO_PIN_5         5
#define GPIO_PIN_6         6
#define GPIO_PIN_7         7
#define GPIO_PIN_8         8
#define GPIO_PIN_9         9
#define GPIO_PIN_10        10
#define GPIO_PIN_11        11
#define GPIO_PIN_12        12
#define GPIO_PIN_13        13
#define GPIO_PIN_14        14
#define GPIO_PIN_15        15

/*=========================================================
                    GPIO PIN MODES
=========================================================*/

#define GPIO_MODE_IN           0
#define GPIO_MODE_OUT          1
#define GPIO_MODE_ALTFN        2
#define GPIO_MODE_ANALOG       3

/*=========================================================
                   GPIO OUTPUT TYPES
=========================================================*/

#define GPIO_OP_TYPE_PP        0
#define GPIO_OP_TYPE_OD        1

/*=========================================================
                    GPIO OUTPUT SPEEDS
=========================================================*/

#define GPIO_SPEED_LOW         0
#define GPIO_SPEED_MEDIUM      1
#define GPIO_SPEED_HIGH        2
#define GPIO_SPEED_VERY_HIGH   3

/*=========================================================
                    GPIO PULL CONFIGURATION
=========================================================*/

#define GPIO_NO_PUPD           0
#define GPIO_PIN_PU            1
#define GPIO_PIN_PD            2

/*=========================================================
                GPIO PIN STATE
=========================================================*/

#define GPIO_PIN_RESET         0
#define GPIO_PIN_SET           1

/*=========================================================
                GPIO ALTERNATE FUNCTIONS
=========================================================*/

#define GPIO_AF0               0
#define GPIO_AF1               1
#define GPIO_AF2               2
#define GPIO_AF3               3
#define GPIO_AF4               4
#define GPIO_AF5               5
#define GPIO_AF6               6
#define GPIO_AF7               7
#define GPIO_AF8               8
#define GPIO_AF9               9
#define GPIO_AF10              10
#define GPIO_AF11              11
#define GPIO_AF12              12
#define GPIO_AF13              13
#define GPIO_AF14              14
#define GPIO_AF15              15


typedef struct
{
    uint8_t PinNumber;
    uint8_t PinMode;
    uint8_t PinOutputType;
    uint8_t PinSpeed;
    uint8_t PinPullControl;
    uint8_t PinAltFunMode;

} GPIO_Config_t;

typedef struct 
{
  GPIO_TypeDef *pGPIOx;
  GPIO_Config_t GPIO_PinConfig;

}GPIO_Handle_t;

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

void GPIO_WritePin(GPIO_TypeDef *pGPIOx,uint8_t PinNumber,uint8_t Value);

uint8_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx,uint8_t PinNumber);

void GPIO_TogglePin(GPIO_TypeDef *pGPIOx,uint8_t PinNumber);

void GPIO_LockPin(GPIO_TypeDef *pGPIOx,uint8_t PinNumber);


#endif