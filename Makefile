PHONY: all, clean, load

SRC = src/
BLD = build/
LIB = lib/
INC = -Iinc/

CC = riscv64-unknown-elf-gcc
CPP = riscv64-unknown-elf-g++
AS = riscv64-unknown-elf-as
OBJCOPY = riscv64-unknown-elf-objcopy  
OBJDUMP = riscv64-unknown-elf-objdump
CFLAGS = -g -O0 -march=rv32imac -mabi=ilp32 -mcmodel=medlow -nostdlib  
CPPFLAGS = -g -O0 -march=rv32imac -mabi=ilp32 -mcmodel=medlow -nostdlib -Wall \
			-nostartfiles -fno-common -D"assert_param(x)=" \
			-ffunction-sections -Wno-pointer-arith -fno-rtti
#-mcmodel=medany
LFLAGS = -T$(LIB)GD32VF103.ld -Xlinker -Map=$(BLD)prog.map
ASFLAGS = -march=rv32imac -mabi=ilp32 

all: $(BLD)prog.elf $(BLD)prog.bin $(BLD)prog.lst $(BLD)prog.hex
$(BLD)prog.hex: $(BLD)prog.elf
	$(OBJCOPY) -O ihex $(BLD)prog.elf $(BLD)prog.hex
$(BLD)prog.bin: $(BLD)prog.elf
	$(OBJCOPY) -O binary $(BLD)prog.elf $(BLD)prog.bin
$(BLD)prog.lst: $(BLD)prog.elf
	$(OBJDUMP) -dr -S $(BLD)prog.elf > $(BLD)prog.lst

#$(BLD)main.elf: $(SRC)start.s
#	$(CC) $(SRC)start.s -o $(BLD)main.elf $(CFLAGS) $(LFLAGS)
$(BLD)prog.elf: $(BLD)main.o $(BLD)startup.o $(BLD)startjump.o $(BLD)uart0.o
	$(CC) $(BLD)startup.o $(BLD)main.o $(BLD)uart0.o $(BLD)startjump.o $(LFLAGS) -o $(BLD)prog.elf $(CPPFLAGS) $(INC)
	@echo "********************  SIZE  **************************"
	@riscv64-unknown-elf-size $(BLD)prog.elf
	@echo "******************************************************"	
$(BLD)startjump.o: $(LIB)startjump.s	
	$(AS) -c $(LIB)startjump.s -o $(BLD)startjump.o $(ASFLAGS)
	$(OBJDUMP) -dr -S $(BLD)startjump.o > $(BLD)startjump.lst
$(BLD)startup.o: $(LIB)startup.cpp
	$(CPP) -c $(LIB)startup.cpp -o $(BLD)startup.o $(CFLAGS)
	$(OBJDUMP) -dr -S $(BLD)startup.o > $(BLD)startup.lst
$(BLD)main.o: $(SRC)main.cpp
	$(CPP) -c $(SRC)main.cpp -o $(BLD)main.o $(CPPFLAGS) $(INC) -I$(LIB)
	$(OBJDUMP) -dr -S $(BLD)main.o > $(BLD)main.lst
$(BLD)uart0.o: $(SRC)uart0.cpp
	$(CPP) -c $(SRC)uart0.cpp -o $(BLD)uart0.o $(CPPFLAGS) $(INC) -I$(LIB)
	$(OBJDUMP) -dr -S $(BLD)uart0.o > $(BLD)uart0.lst

clean:
	rm -R build
	mkdir build	

load:
#	stm32flash /dev/ttyUSB0 -w $(BLD)main.bin
	dfu-util -a 0 -d 28e9:0189 -s 0x08000000 -D $(BLD)prog.bin

# ****  instruction to use dfu-util without sudo *******
# sudo nano /etc/udev/rules.d/99-particles.rules
# SUBSYSTEMS=="usb", ATTRS{idVendor}=="28e9", ATTRS{idProduct}=="0189", GROUP="plugdev", MODE="0666"
# *** checkout::::          dfu-util -l	