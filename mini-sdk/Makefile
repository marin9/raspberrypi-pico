ARMGNU	= arm-none-eabi
XCPU	= -mcpu=cortex-m0
AOPS	= --warn --fatal-warnings $(XCPU)
COPS	= -Wall -Wextra -O2 -ffreestanding $(XCPU) -fpic -mthumb
LOPS	= -nostdlib -nostartfiles

LINKER	= memory.ld
TARGET	= picobin
MKUF2	= ../mkuf2
RUNSC	= ../run.sh

ASM		:= $(wildcard src/*.s)
SRC 	:= $(wildcard src/*.c)
INC		:= $(wildcard inc/*.h)
OBJA	:= $(ASM:src/%.s=obj/%.o)
OBJC	:= $(SRC:src/%.c=obj/%.o)


all: $(TARGET).bin $(TARGET).list $(TARGET).uf2

run: $(TARGET).bin $(TARGET).list $(TARGET).uf2
	@echo " Copy to MCU"
	@./$(RUNSC)

clean :
		@echo " Clean"
		@rm -f obj/*
		@rm -f $(TARGET).*

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

$(OBJA): obj/%.o : src/%.s $(INC)
	@echo " Compile\t" $<
	@$(ARMGNU)-as $(AOP) $< -o $@

$(OBJC): obj/%.o : src/%.c $(INC)
	@echo " Compile\t" $<
	@$(ARMGNU)-gcc $(COPS) -Iinc -c $< -o $@
