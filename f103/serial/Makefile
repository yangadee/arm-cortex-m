CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
CFLAGS = -fno-common -O0 \
	 -mcpu=cortex-m3 -mthumb \
	 -T serial.ld -nostartfiles \

TARGET = serial.bin
all: $(TARGET)

$(TARGET): serial.c startup.c
	$(CC) $(CFLAGS) $^ -o serial.elf
	$(CROSS_COMPILE)objcopy -Obinary serial.elf serial.bin
	$(CROSS_COMPILE)objdump -S serial.elf > serial.list

qemu: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel hello.bin

clean:
	rm -f *.o *.bin *.elf *.list
