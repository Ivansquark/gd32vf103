#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "gd32vf103.h"
#include "riscv_encoding.h"

// CSR_MSTATUS 0x300;
// CSR_MTVEC 0x305;
// MSTATUS_MIE (1<<3);
constexpr uint32_t ECLIC_ADDR_BASE = 0xd2000000;
constexpr uint32_t ECLIC_INT_IE_OFFSET = 0x1001;
constexpr uint32_t ECLIC_INT_IP_OFFSET = 0x1000;
constexpr uint32_t ECLIC_INT_CTRL_OFFSET = 0x1003;
constexpr uint32_t ECLIC_INT_ATTR_OFFSET = 0x1002;
constexpr uint32_t ECLIC_CFG_OFFSET = 0x0;
constexpr uint32_t ECLIC_MTH_OFFSET = 0xB;
constexpr uint32_t ECLIC_CFG_NLBITS_LSB = 0x1;
constexpr uint32_t ECLIC_CFG_NLBITS_MASK = 0x1E;
constexpr uint8_t  ECLICINTCTLBITS = 0x4;

asm(".equ CSR_MSTATUS, 0x300 \n"
    ".equ CSR_MTVEC, 0x305 \n"
    ".equ MSTATUS_MIE, (1<<3) \n");
inline void eclic_init(){
    asm("la t0,  CSR_MTVEC \n"
        "la t1, 0xFFFFFFC0 \n"
        "and t0, t0, t1    \n"
        "ori t0, t0, 3     \n"
        "csrw CSR_MTVEC, t0  # set eclic ");
}
inline void interruptEnable() {
    asm("csrrs zero, CSR_MSTATUS, MSTATUS_MIE");
}
inline void eclic_enable_interrupt (uint32_t source) {
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IE_OFFSET+source*4) = 1;
}
inline void eclic_disable_interrupt (uint32_t source){
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IE_OFFSET+source*4) = 0;
}
inline void eclic_set_pending(uint32_t source){
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IP_OFFSET+source*4) = 1;
}
inline void eclic_clear_pending(uint32_t source){
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IP_OFFSET+source*4) = 0;
}
inline void eclic_set_intctrl (uint32_t source, uint8_t intctrl){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTRL_OFFSET+source*4) = intctrl;
}

inline uint8_t eclic_get_intctrl  (uint32_t source){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTRL_OFFSET+source*4);
}

inline void eclic_set_intattr (uint32_t source, uint8_t intattr){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_ATTR_OFFSET+source*4) = intattr;
}

inline uint8_t eclic_get_intattr  (uint32_t source){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_ATTR_OFFSET+source*4);
}

inline void eclic_set_cliccfg (uint8_t cliccfg){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_CFG_OFFSET) = cliccfg;
}

inline uint8_t eclic_get_cliccfg  (){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_CFG_OFFSET);
}
inline void eclic_set_mth (uint8_t mth){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_MTH_OFFSET) = mth;
}

inline uint8_t eclic_get_mth  (){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_MTH_OFFSET);
}
//sets nlbits 
inline void eclic_set_nlbits(uint8_t nlbits) {
  //shift nlbits to correct position
  uint8_t nlbits_shifted = nlbits << ECLIC_CFG_NLBITS_LSB;
  //read the current cliccfg 
  uint8_t old_cliccfg = eclic_get_cliccfg();
  uint8_t new_cliccfg = (old_cliccfg & (~ECLIC_CFG_NLBITS_MASK)) | (ECLIC_CFG_NLBITS_MASK & nlbits_shifted); 
  eclic_set_cliccfg(new_cliccfg);
}
//get nlbits 
inline uint8_t eclic_get_nlbits(void) {
  //extract nlbits
  uint8_t nlbits = eclic_get_cliccfg();
  nlbits = (nlbits & ECLIC_CFG_NLBITS_MASK) >> ECLIC_CFG_NLBITS_LSB;
  return nlbits;
}

//sets an interrupt level based encoding of nlbits and ECLICINTCTLBITS
inline void eclic_set_irq_lvl(uint32_t source, uint8_t lvl) {
  //extract nlbits
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }
  //shift lvl right to mask off unused bits
  lvl = lvl >> (8-nlbits);
  //shift lvl into correct bit position
  lvl = lvl << (8-nlbits); 
  //write to clicintctrl
  uint8_t current_intctrl = eclic_get_intctrl(source);
  //shift intctrl left to mask off unused bits
  current_intctrl = current_intctrl << nlbits;
  //shift intctrl into correct bit position
  current_intctrl = current_intctrl >> nlbits;
  eclic_set_intctrl(source, (current_intctrl | lvl));
}

//gets an interrupt level based encoding of nlbits
inline uint8_t eclic_get_irq_lvl(uint32_t source) {
  //extract nlbits
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }
  uint8_t intctrl = eclic_get_intctrl(source);
  //shift intctrl
  intctrl = intctrl >> (8-nlbits);
  //shift intctrl
  uint8_t lvl = intctrl << (8-nlbits);
  return lvl;
}

inline void eclic_set_irq_lvl_abs(uint32_t source, uint8_t lvl_abs) {
  //extract nlbits
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  //shift lvl_abs into correct bit position
  uint8_t lvl = lvl_abs << (8-nlbits); 
  //write to clicintctrl
  uint8_t current_intctrl = eclic_get_intctrl(source);
  //shift intctrl left to mask off unused bits
  current_intctrl = current_intctrl << nlbits;
  //shift intctrl into correct bit position
  current_intctrl = current_intctrl >> nlbits;
  eclic_set_intctrl(source, (current_intctrl | lvl));
}

inline uint8_t eclic_get_irq_lvl_abs(uint32_t source) {
  //extract nlbits
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  uint8_t intctrl = eclic_get_intctrl(source);

  //shift intctrl
  intctrl = intctrl >> (8-nlbits);
  //shift intctrl
  uint8_t lvl_abs = intctrl;

  return lvl_abs;
}

//sets an interrupt priority based encoding of nlbits and ECLICINTCTLBITS
inline uint8_t eclic_set_irq_priority(uint32_t source, uint8_t priority) {
	//extract nlbits
	uint8_t nlbits = eclic_get_nlbits();
	if (nlbits >= ECLICINTCTLBITS) {
		nlbits = ECLICINTCTLBITS;
		return 0;
	}

	//shift priority into correct bit position
	priority = priority << (8 - ECLICINTCTLBITS);

	//write to eclicintctrl
	uint8_t current_intctrl = eclic_get_intctrl(source);
	//shift intctrl right to mask off unused bits
	current_intctrl = current_intctrl >> (8-nlbits);
	//shift intctrl into correct bit position
	current_intctrl = current_intctrl << (8-nlbits);

	eclic_set_intctrl(source, (current_intctrl | priority));

	return priority;
}

//gets an interrupt priority based encoding of nlbits
inline uint8_t eclic_get_irq_priority(uint32_t source) {
	//extract nlbits
	uint8_t nlbits = eclic_get_nlbits();
	if (nlbits > ECLICINTCTLBITS) {
		nlbits = ECLICINTCTLBITS;
	}

	uint8_t intctrl = eclic_get_intctrl(source);

	//shift intctrl
	intctrl = intctrl << nlbits;
	//shift intctrl
	uint8_t priority = intctrl >> (nlbits+(8 - ECLICINTCTLBITS));

	return priority;
}

//sets vector-mode or non-vector mode 
inline void eclic_set_vmode(uint32_t source) {
  //read the current attr 
  uint8_t old_intattr = eclic_get_intattr(source);
      // Keep other bits unchanged and only set the LSB bit
  uint8_t new_intattr = (old_intattr | 0x1); 

  eclic_set_intattr(source,new_intattr);
}

inline void eclic_set_nonvmode(uint32_t source) {
  //read the current attr 
  uint8_t old_intattr = eclic_get_intattr(source);
      // Keep other bits unchanged and only clear the LSB bit
  uint8_t new_intattr = (old_intattr & (~0x1));

  eclic_set_intattr(source,new_intattr);
}

inline void eclic_set_level_trig(uint32_t source) {
  //read the current attr 
  uint8_t old_intattr = eclic_get_intattr(source);
      // Keep other bits unchanged and only clear the bit 1
  uint8_t new_intattr = (old_intattr & (~0x2));

  eclic_set_intattr(source,new_intattr);
}

inline void eclic_set_posedge_trig(uint32_t source) {
  //read the current attr 
  uint8_t old_intattr = eclic_get_intattr(source);
      // Keep other bits unchanged and only set the bit 1
  uint8_t new_intattr = (old_intattr | 0x2);
      // Keep other bits unchanged and only clear the bit 2
  new_intattr = (old_intattr & (~0x4));
  eclic_set_intattr(source,new_intattr);
}

inline void eclic_set_negedge_trig(uint32_t source) {
  //read the current attr 
  uint8_t old_intattr = eclic_get_intattr(source);
      // Keep other bits unchanged and only set the bit 1
  uint8_t new_intattr = (old_intattr | 0x2);
      // Keep other bits unchanged and only set the bit 2
  new_intattr = (old_intattr | 0x4);
  eclic_set_intattr(source,new_intattr);
}
#endif //INTERRUPT_H