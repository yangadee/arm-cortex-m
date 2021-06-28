#include "reg.h"
#include <stdint.h>

#define USART_FLAG_TXE ((uint16_t)0x0080)

int puts(const char *str) {
  while (*str) {
    while (!(*(USART1_SR)&USART_FLAG_TXE))
      ;
    *(USART1_DR) = *str++ & 0xFF;
  }
  return 0;
}

void main(void) {
  /* AFIOEN = 1 * && /* AFIOAN = 1 */
  *(RCC_APB2ENR) |= (uint32_t)(0x00000001 | 0x00000004);
  *(RCC_APB1ENR) |= (uint32_t)(0x00020000);

  // USART2 config PA2 & PA3 for default, if let AF remap reg
  // default(AFIO_MAPR).
  /* USART2 Configuration */
  *(GPIOA_CRH) |= 0x00000030 | 0x00000080;
  *(GPIOA_CRH) &= ~(0x00000040);
  // *(GPIOA_CRL) = 0x00004B00;
  // *(GPIOA_CRH) = 0x44444444;

  // *(USART2_CR1) = 0x0000000C;
  // *(USART2_CR1) |= 0x2000;
  *(USART1_CR1) = 0x0004 | 0x0008 | 0x2000;
  *(USART1_BRR) = 0x1D4C; // for 72MHZ on APB2 bus
  puts("Hello World!\n");

  while (1) {
    puts("Hello World! in while loop\n");
  }
}
