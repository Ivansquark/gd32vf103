#ifndef UART0_H
#define UART0_H
#include "gd32vf103.h"
#include "interrupt.h"

class Uart0 {
public:
    Uart0();
    static Uart0* pThis;
    void sendByte(uint8_t byte);
    void sendStr(char* str);
private:
    void init();

};

#endif //UART0_H