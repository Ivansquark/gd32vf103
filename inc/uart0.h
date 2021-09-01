#ifndef UART0_H
#define UART0_H
#define __STDC_HOSTED__ 0
#include "gd32vf103.h"

class Uart0 {
public:
    Uart0();
    void sendByte(uint8_t byte);
    void sendStr(char* str);
private:
    void init();

};

#endif //UART0_H