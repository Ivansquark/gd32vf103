# first two bytes in vector table must be jump instruction to Reset_Handler
# its implemented in that asm file (vector table in cpp file must be reduced on one first function ptr)
.section .startjump,"a",%progbits
.global StartJ
StartJ:
jal Reset_Handler