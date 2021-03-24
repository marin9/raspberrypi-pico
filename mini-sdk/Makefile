ARMGNU	= arm-none-eabi
XCPU	= -mcpu=cortex-m0
AOPS	= --warn --fatal-warnings $(XCPU)
COPS	= -Wall -Wextra -O2 -ffreestanding $(XCPU) -fpic -mthumb
LOPS	= -nostdlib -nostartfiles

LINKER	= memory.ld
TARGET	= prog
MKUF2	= ../mkuf2
RUNSC	= ../run.sh

ASM 	:= start.s
SRC 	:= init.c
SRC 	+= gpio.c
SRC 	+= uart.c
SRC 	+= resets.c
SRC 	+= testcase.c
INC		:= $(wildcard *.h)
OBJA	:= $(ASM:%.s=%.o)
OBJC	:= $(SRC:%.c=%.o)


all: $(TARGET).bin $(TARGET).list $(TARGET).uf2

run: $(TARGET).bin $(TARGET).list $(TARGET).uf2
	@echo " Run..."
	@./$(RUNSC)

$(TARGET).uf2 : $(TARGET).bin
	@echo " Create\t\t" $@
	@./$(MKUF2) -i $< -o $@

$(TARGET).list: $(TARGET).elf
	@echo " Create\t\t" $@
	@$(ARMGNU)-objdump -D $< > $@

$(TARGET).bin: $(TARGET).elf
	@echo " Create\t\t" $@
	@$(ARMGNU)-objcopy -O binary $< $@

$(TARGET).elf : $(LINKER) $(OBJA) $(OBJC)
	@echo " Create\t\t" $@
	@$(ARMGNU)-ld $(LOPS) -T $(LINKER) $(OBJA) $(OBJC) -o $@

$(OBJA): %.o : %.s $(INC)
	@echo " Compile\t" $<
	@$(ARMGNU)-as $(AOP) $< -o $@

$(OBJC): %.o : %.c $(INC)
	@echo " Compile\t" $<
	@$(ARMGNU)-gcc $(COPS) -c $< -o $@

clean :
	@echo " Clean"
	@rm -f *.o
	@rm -f $(TARGET).*
