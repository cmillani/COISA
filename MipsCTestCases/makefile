.SUFFIXES:
all: 
	@echo "Nothing to be done, no target"

LD=/opt/cross/mips-binutils/bin/mips-unknown-elf-ld
LD_SCRIPT=linker.ld
AS=/opt/cross/mips-binutils/bin/mips-unknown-elf-as
INCLUDE = -I extras/lib/
LIBRARIES = extras/crt0.s extras/lib/THING_ultrasonic.s extras/lib/THING_serial.s extras/lib/THING_encoder.s extras/lib/THING_movement.s 

%.manifest:
	extras/scribe $(MANIFESTFLAGS) -o $@

%.s: %.c
	$(HOME)/ellcc/bin/ecc -target mips-linux-eng -S $< $(INCLUDE) -O3 -nostdlib -fno-exceptions -fno-rtti -static -o $@

%.o: %.s
	$(AS) $< $(LIBRARIES) -o $@

%.bin: %.o
	$(LD) -T $(LD_SCRIPT) $< -o $@

%.x: %.bin
	/opt/cross/mips-binutils/bin/mips-unknown-elf-objcopy -O binary $< $@
clean:
	rm -f *.o *.bin *.x *.s *.manifest
tester:
	gcc main_test.c src/vm.c src/HAL.c src/syscall.c sensors/encoder.c sensors/ultrasonic.c -o vmTester
