#define __STDC_HOSTED__ 0
#include "riscv_encoding.h"
#include "gd32vf103.h"
#include "uart0.h"

void gpioInit();
void delay(volatile uint32_t val);

int main() {
    gpioInit();   
    GPIOC->BSRR |= (1<<29);
    GPIOC->BSRR |= (1<<13);
    Uart0 uart;
    uint8_t count = 0;
    while (1) {
        uart.sendByte(count++);        
        //GPIOC->BSRR |= (1<<29);
        //delay(500000);
        //GPIOC->BSRR |= (1<<13);
        //delay(1000000);
         GPIOC->ODR |= (1<<13);
         delay(500000);
         GPIOC->ODR &=~ (1<<13);
         delay(500000);
    }
    return 0;
}

void gpioInit() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &=~ GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13; //00:11 GPIO output max speed
}

void delay(volatile uint32_t val) {
    while(val!=0) {
        val--;
    }
}

void USART0_IRQn_handler() {
    GPIOC->ODR |= (1 << 13);
    delay(100000);
    GPIOC->ODR &= ~(1 << 13);
    delay(100000);
}