#include "gpio.h"
#include "rcc.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint8_t pos;

    pos = 2U * pGPIOHandle->GPIO_PinConfig.PinNumber;

    pGPIOHandle->pGPIOx->MODER &= ~(3U << pos);

    pGPIOHandle->pGPIOx->MODER |=
        (pGPIOHandle->GPIO_PinConfig.PinMode << pos);

   if((pGPIOHandle->GPIO_PinConfig.PinMode == GPIO_MODE_OUT) ||
   (pGPIOHandle->GPIO_PinConfig.PinMode == GPIO_MODE_ALTFN))
      {
          pGPIOHandle->pGPIOx->OTYPER &=
              ~(1U << pGPIOHandle->GPIO_PinConfig.PinNumber);

          pGPIOHandle->pGPIOx->OTYPER |=
              (pGPIOHandle->GPIO_PinConfig.PinOutputType
              << pGPIOHandle->GPIO_PinConfig.PinNumber);
      }
   if((pGPIOHandle->GPIO_PinConfig.PinMode == GPIO_MODE_OUT) ||
   (pGPIOHandle->GPIO_PinConfig.PinMode == GPIO_MODE_ALTFN))
   {
    pGPIOHandle->pGPIOx->OSPEEDR &=
              ~(3U << pos);

          pGPIOHandle->pGPIOx->OSPEEDR |=
              (pGPIOHandle->GPIO_PinConfig.PinSpeed
              << pos);
   }


    pGPIOHandle->pGPIOx->PUPDR &=
              ~(3U << pos);

          pGPIOHandle->pGPIOx->PUPDR |=
              (pGPIOHandle->GPIO_PinConfig.PinPullControl
              << pos);
   
   if(pGPIOHandle->GPIO_PinConfig.PinMode == GPIO_MODE_ALTFN){
      uint8_t pinNo = pGPIOHandle->GPIO_PinConfig.PinNumber;

      if(pinNo <= 7)
      {
          pGPIOHandle->pGPIOx->AFRL &= ~(0xFU << (4U * pinNo));

          pGPIOHandle->pGPIOx->AFRL |=
              (pGPIOHandle->GPIO_PinConfig.PinAltFunMode
              << (4U * pinNo));
      }
      else
      {
          pGPIOHandle->pGPIOx->AFRH &= ~(0xFU << (4U * (pinNo - 8U)));

          pGPIOHandle->pGPIOx->AFRH |=
              (pGPIOHandle->GPIO_PinConfig.PinAltFunMode
              << (4U * (pinNo - 8U)));
      }
   }

}

void GPIO_WritePin(GPIO_TypeDef *pGPIOx,
                   uint8_t PinNumber,
                   uint8_t Value)
{
    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->BSRR = (1U << PinNumber);
    }
    else
    {
        pGPIOx->BSRR = (1U << (PinNumber + 16U));
    }
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx,
                     uint8_t PinNumber)
{
    return ((pGPIOx->IDR >> PinNumber) & 0x1U);
}

void GPIO_TogglePin(GPIO_TypeDef *pGPIOx,uint8_t PinNumber){
  pGPIOx->ODR^=(1<<PinNumber);
}


