ARMGNU	= arm-none-eabi
XCPU	= -mcpu=cortex-m0
AOPS	= --warn --fatal-warnings $(XCPU)
COPS	= -Wall -Wextra -O2 -ffreestanding $(XCPU) -fpic -mthumb
LOPS	= -nostdlib -nostartfiles
UOPS	= -f

MKUF2	= mkuf2
LINKER	= memory.ld
TARGET	= picobin

ASM		= $(wildcard src/*.s)
SRC 	= $(wildcard src/*.c)
INC		= $(wildcard inc/*.h)
OBJA	= $(ASM:src/%.s=build/%.o)
OBJC	= $(SRC:src/%.c=build/%.o)


all: build $(TARGET).bin $(TARGET).list $(TARGET).uf2

run: build $(TARGET).bin $(TARGET).list $(TARGET).uf2
	@echo " Copy to MCU"
	@mkdir -p /mnt/pico
	@sudo mount /dev/sda1 /mnt/pico
	@cp $(TARGET).uf2 /mnt/pico
	@sync
	@sudo umount /mnt/pico

clean :
		@echo " Clean"
		@rm -rf build
		@rm -f $(TARGET).*


$(TARGET).uf2 : $(TARGET).bin
	@echo " Create\t\t" $@
	@./$(MKUF2) -i $< -o $@ $(UOPS)

$(TARGET).list: $(TARGET).elf
	@echo " Create\t\t" $@
	@$(ARMGNU)-objdump -D $< > $@

$(TARGET).bin: $(TARGET).elf
	@echo " Create\t\t" $@
	@$(ARMGNU)-objcopy -O binary $< $@

$(TARGET).elf : $(LINKER) $(OBJA) $(OBJC)
	@echo " Create\t\t" $@
	@$(ARMGNU)-ld $(LOPS) -T $(LINKER) $(OBJA) $(OBJC) -o $@

$(OBJA): build/%.o : src/%.s $(INC)
	@echo " Compile\t" $<
	@$(ARMGNU)-as $(AOP) $< -o $@

$(OBJC): build/%.o : src/%.c $(INC)
	@echo " Compile\t" $<
	@$(ARMGNU)-gcc $(COPS) -Iinc -c $< -o $@

build:
	@echo " Create\t\t" $@
	@mkdir build
