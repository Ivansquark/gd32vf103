OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{ 
	/* Run in FLASH */ 
	flash (rxai!w) : ORIGIN = 0x08000000, LENGTH = 128k
	ram   (wxa!ri) : ORIGIN = 0x20000000, LENGTH = 32K 

	/* Run in RAM */ 
/*	flash (rxai!w) : ORIGIN = 0x20000000, LENGTH = 24k
	ram   (wxa!ri) : ORIGIN = 0x20006000, LENGTH = 8K
*/	
}


SECTIONS
{  
  __stack_size = DEFINED(__stack_size) ? __stack_size : 2K;
  . = ALIGN(4); 

  .startjump : {
  } >flash
  

  . = ALIGN(4);
  .vectors :
  {
      KEEP (*(SORT_NONE(.vectors)))
  } >flash  

  .text           :
  {   
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >flash AT>flash 
  
 
  . = ALIGN(4);
  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
    KEEP (*(SORT_NONE(.fini)))
    . = ALIGN(4);
    /* The preinit code, i.e. an array of pointers to initialisation 
     * functions to be performed before constructors. */
		PROVIDE_HIDDEN (__preinit_array_start = .);
    /* The init code, i.e. an array of pointers to static constructors. */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
    /*The fini code, i.e. an array of pointers to static destructors.*/
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
		. = ALIGN(4);

  } >flash AT>flash 
  . = ALIGN(4);

   PROVIDE( _eilm = . );
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)    
    *(vtable)					/* C++ virtual tables */
  } >flash
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);/*0x80022c8*/
  PROVIDE (etext = .);/*0x80022c8*/
  /*
    . = ALIGN(4);
    PROVIDE( _eilm = . );
    
  .lalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data_lma = . );
  } >flash AT>flash 

  .dalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data = . );
  } >ram AT>flash 
  
  */
  . = ALIGN(8);
		.stack :              
	{
    . = ALIGN(8);
		_stack_begin = .;
		_StackLimit = _stack_begin + __stack_size; 
		. = . + __stack_size;
    _StackTop = .;  
    . = ALIGN(8);  
    PROVIDE(_estack = _StackTop);
	}>ram 
  
  _sidata = .;
  .data : {
    *(.rdata)    
    . = ALIGN(4);
    PROVIDE( __global_pointer$ = . + 0x800); 
    *(.sdata .sdata.*)
  } >ram AT>flash 

  . = ALIGN(8);
  PROVIDE( _edata = . );
  PROVIDE( edata = . );

  PROVIDE( _fbss = . ); /*0X200052A0  0X200002A0*/
  PROVIDE( _sbss = . );
  .bss            :
  {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
  } >ram AT>ram 

  . = ALIGN(8);
  PROVIDE( _ebss = . ); /*0X2000,0340*/
  PROVIDE( end = . );

  .heap : {
    PROVIDE( _heap_end = . );
  }
}
