#include "riscv_encoding.h"
#include "gd32vf103.h"
#include "uart0.h"

void gpioInit();
void delay(volatile uint32_t val);
Uart0 uart;
int main() {
    int i = -7;
    
    gpioInit();   
    GPIOC->BSRR |= (1<<29);
    GPIOC->BSRR |= (1<<13);
    GPIOC->BSRR |= (1<<29);
    uint8_t count = 0x30;
    while (1) {
        //uart.sendByte(count++);        
        if(count == 0x50) {
            count = 0;
        }
        //GPIOC->BSRR |= (1<<29);
        //delay(500000);
        //GPIOC->BSRR |= (1<<13);
        //delay(1000000);
         //GPIOC->ODR |= (1<<13);
         delay(50000);
         //GPIOC->ODR &=~ (1<<13);
         delay(50000);
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

extern "C" void USART0_IRQn_handler() {
    // GPIOC->ODR |= (1 << 13);
    // delay(100000);
    // GPIOC->ODR &= ~(1 << 13);
    // delay(100000);
    //USART0->STAT &=~ USART_STAT_RBNE;
    GPIOC->ODR ^= (1<<13);
    uint8_t byte = USART0->DATA;
    //  Uart0::pThis->sendByte('O');
    //  Uart0::pThis->sendByte('P');
    //  Uart0::pThis->sendByte('A');
}