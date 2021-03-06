extern "C" void Reset_Handler(); 
extern "C" void Default_Handler();
extern "C" int main();

extern "C" void eclic_msip_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void eclic_mtip_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void eclic_bwei_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void eclic_pmovi_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void watchdog_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void LVD_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void tamper_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void RTC_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void FMC_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void RCU_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI2_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI3_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI4_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan2_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan3_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan4_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan5_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA0_chan6_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void ADC0_1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN0_TX_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN0_RX0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN0_RX1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN0_EWMC_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI5_9_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM0_break_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM0_update_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM0_trigger_commutation_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM0_channel_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM2_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM3_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C0_EV_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C0_ER_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C1_EV_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C1_ER_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void SPI0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void SPI1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void USART0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void USART1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void USART2_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI10_15_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void RTC_alarm_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void USB_wakeup_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void EXMC_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM4_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void SPI2_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void UART3_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void UART4_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM5_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM6_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_chan0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_chan1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_chan2_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_chan3_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_chan4_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN1_TX_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN1_RX0_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN1_RX1_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN1_EWMC_IRQn_handler() __attribute__((weak, alias("Default_Handler")));
extern "C" void USB_IRQn_handler() __attribute__((weak, alias("Default_Handler")));


void (*Vectors[86])(void) __attribute__((section(".vectors"))) {
    0,
    0,
    eclic_msip_handler,  //# Software interrupt
    0,
    0,
    0,
    eclic_mtip_handler,  //# Timer interrupt
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    eclic_bwei_handler,      
    eclic_pmovi_handler,     
    watchdog_IRQn_handler,
    LVD_IRQn_handler,
    tamper_IRQn_handler,
    RTC_IRQn_handler,
    FMC_IRQn_handler,
    RCU_IRQn_handler,
    EXTI0_IRQn_handler,
    EXTI1_IRQn_handler,
    EXTI2_IRQn_handler,
    EXTI3_IRQn_handler,
    EXTI4_IRQn_handler,
    DMA0_chan0_IRQn_handler,
    DMA0_chan1_IRQn_handler,
    DMA0_chan2_IRQn_handler,
    DMA0_chan3_IRQn_handler,
    DMA0_chan4_IRQn_handler,
    DMA0_chan5_IRQn_handler,
    DMA0_chan6_IRQn_handler,
    ADC0_1_IRQn_handler,
    CAN0_TX_IRQn_handler,
    CAN0_RX0_IRQn_handler,
    CAN0_RX1_IRQn_handler,
    CAN0_EWMC_IRQn_handler,
    EXTI5_9_IRQn_handler,
    TIM0_break_IRQn_handler,
    TIM0_update_IRQn_handler,
    TIM0_trigger_commutation_IRQn_handler,
    TIM0_channel_IRQn_handler,
    TIM1_IRQn_handler,
    TIM2_IRQn_handler,
    TIM3_IRQn_handler,
    I2C0_EV_IRQn_handler,
    I2C0_ER_IRQn_handler,
    I2C1_EV_IRQn_handler,
    I2C1_ER_IRQn_handler,
    SPI0_IRQn_handler,
    SPI1_IRQn_handler,
    USART0_IRQn_handler,
    USART1_IRQn_handler,
    USART2_IRQn_handler,
    EXTI10_15_IRQn_handler,
    RTC_alarm_IRQn_handler,
    USB_wakeup_IRQn_handler,
    0,
    0,
    0,
    0,
    0,
    EXMC_IRQn_handler,
    0,
    TIM4_IRQn_handler,
    SPI2_IRQn_handler,
    UART3_IRQn_handler,
    UART4_IRQn_handler,
    TIM5_IRQn_handler,
    TIM6_IRQn_handler,
    DMA1_chan0_IRQn_handler,
    DMA1_chan1_IRQn_handler,
    DMA1_chan2_IRQn_handler,
    DMA1_chan3_IRQn_handler,
    DMA1_chan4_IRQn_handler,
    0,
    0,
    CAN1_TX_IRQn_handler,
    CAN1_RX0_IRQn_handler,
    CAN1_RX1_IRQn_handler,
    CAN1_EWMC_IRQn_handler,
    USB_IRQn_handler    
};

extern void (*__preinit_array_start []) (void) __attribute__((weak)); //from linker
extern void (*__preinit_array_end []) (void) __attribute__((weak));	//from linker
extern void (*__init_array_start []) (void) __attribute__((weak)); //from linker constructors
extern void (*__init_array_end []) (void) __attribute__((weak)); //from linker	constructors
extern void (*__fini_array_start []) (void) __attribute__((weak)); //from linker destructors
extern void (*__fini_array_end []) (void) __attribute__((weak)); //from linker	destructors
// dummy This section holds executable instructions that contribute to the process initialization code. When a program
// starts to run, the system arranges to execute the code in this section before calling the main program entry point
// (called main for C programs).
void __attribute__ ((weak)) _init(void)  {}
// dummy This section holds executable instructions that contribute to the process termination code. That is,
// when a program exits normally, the system arranges to execute the code in this section
void __attribute__ ((weak)) _fini(void)  {} 

/* Iterate over all the init routines.  */
// static initialization constructors function
extern "C" void __libc_init_array(void) {
    int count;
    int i;
    count = __preinit_array_end - __preinit_array_start; // counts of preinit functions DK what it is
    for (i = 0; i < count; i++)
        __preinit_array_start[i]();
    _init();
    count = __init_array_end - __init_array_start; // counts of init constructors
    for (i = 0; i < count; i++)
        __init_array_start[i]();
}
/* Run all the cleanup routines.  */
//!< destructors not usefull in microcontrollers
extern "C" void __libc_fini_array(void) {
    int count;
    int i;
    count = __fini_array_end - __fini_array_start;
    for (i = count; i > 0; i--)
        __fini_array_start[i - 1]();
    _fini();
}

extern void *_sidata, *_sdata, *_edata, *_sbss, *_ebss; //???? ???????????? ??????????????
extern "C" void __attribute__((naked,noreturn)) Reset_Handler() {
    // jump to 0x0800xxxx address field from 0x0000xxxx address field
    asm("la a0, 0x08000000 \n"
         "addi a0, a0, 0x28a \n"
         "jr a0");
    // check if PC == 0x0800xxxx     
    asm("la s0, _estack \n" 
        "la s1, 0x20000800 \n"
        "bne s0, s1, Reset_Handler");
    asm("mv sp, s1"); // set stack ptr
    asm("csrc 0x300, 8"); // disable interrupts
    /* Intial the mtvt*/
    asm(".equ CSR_MTVT,  0x307 \n   "
        //"la t0, Vectors-4 \n      "
        "lui t0, 0x08000 \n"
        "csrw CSR_MTVT, t0          ");
    __libc_init_array(); 
    main();
}
extern "C" void Default_Handler() {
     while(1) {
        //     *((int*)(0x40011000 + 12)) ^= (1 << 13);
        //     for(volatile int i=0; i<500000;i++){}
     }
}