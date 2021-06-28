/* Includes */

#include "stm32f10x.h"
#include <stddef.h>
#include <stdint.h>

#define USART_SR_RXNE ((uint16_t)0x0020) /*!< Read Data Register Not Empty */
#define USART_SR_TC ((uint16_t)0x0040)   /*!< Transmission Complete */

int main(void) {

  //-----------------------| UART CODE
  //|---------------------- USART1 / GPIOA clock enable
  *(RCC_APB2ENR) |= (uint32_t)(0x00000001 | 0x00000004);

  // remaping if needed
  // AFIO->MAPR |= AFIO_MAPR_USART1_REMAP ; //remap RX TX to PB7 PB6

  // pin configurations: PA9- TX is set to ALternate-push-pull and 50MHz
  *(GPIOA_CRH) |= 0x00000030 | 0x00000080;
  *(GPIOA_CRH) &= ~(0x00000040);

  /* PIN PA10 is the RX pin and it has to be set to input &FLOATING
   * this is the rest value of the pin so we dont do anything to it
   */

  // USART DIV value
  *(USART1_BRR) = 0x1D4C; // for 72MHZ on APB2 bus

  //----------  RX enable  TX enable UART enable
  *(USART1_CR1) |= 0x0004 | 0x0008 | 0x2000;

  while (1) {
    if (*(USART1_SR)&USART_SR_RXNE) // if RX is not empty
    {
      char temp = *(USART1_DR);           // fetch the data received
      *(USART1_DR) = temp;                // send it back out
      while (!(*(USART1_SR)&USART_SR_TC)) // wait for TX to be complete
        ;
    }
  }
}