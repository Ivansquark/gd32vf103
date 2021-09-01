#include "uart0.h"

Uart0::Uart0() {
    init();
}

void Uart0::sendByte(uint8_t byte) {
    while(!(USART0->STAT & USART_STAT_TBE)){}
    USART0->DATA = byte;
    while(!(USART0->STAT & USART_STAT_TC)){}
}
void Uart0::sendStr(char* str) {
    while(*str!='\0') {
        sendByte(*str);
        str++;
    }
}

void Uart0::init() {
    // Tx A9 Rx A10
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;       
    GPIOA->CRH = 0;
    GPIOA->CRH |=  (1<<7) | (3<<4); //CTL9=1:0; MD9=1:1  AF push-pull max speed
    GPIOA->CRH |=  (1<<10) | (0<<8); //CTL10=0:1; MD9=0:0  input floating (HiZ)
    RCC->APB2ENR |= RCC_APB2ENR_USART0EN;
    USART0->BAUD = 0x341;//(8000000-4800)/9600 = 832,8 = 0x341
    USART0->CTL0 |= (USART_CTL0_UEN | USART_CTL0_REN | USART_CTL0_TEN | USART_CTL0_RBNEIE | USART_CTL0_TCIE);
}


