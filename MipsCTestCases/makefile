.SUFFIXES:
all: binary symlink tester

LD=/opt/cross/mips-binutils/bin/mips-unknown-elf-ld
LD_SCRIPT=linker.ld
AS=/opt/cross/mips-binutils/bin/mips-unknown-elf-as

%.s: %.c
	$(HOME)/ellcc/bin/ecc -target mips-linux-eng -S $< -O0 -nostdlib -fno-exceptions -fno-rtti -static -o $@

%.o: %.s
	$(AS) $< extras/crt0.s extras/stdthing.s -o $@

%.bin: %.o
	$(LD) -T $(LD_SCRIPT) $< -o $@

%.x: %.bin
	/opt/cross/mips-binutils/bin/mips-unknown-elf-objcopy -O binary $< $@
clean:
	rm -f *.o *.bin *.x
tester:
	gcc main_test.c src/vm.c src/HAL.c src/syscall.c sensors/encoder.c sensors/ultrasonic.c -o vmTester
