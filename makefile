.SUFFIXES:
all: binary symlink tester

LD=/opt/cross/mips-binutils/bin/mips-unknown-elf-ld
LD_SCRIPT=linker.ld
AS=/opt/cross/mips-binutils/bin/mips-unknown-elf-as

%.s: %.c
	$(HOME)/ellcc/bin/ecc -target mips-linux-eng -S $< -O0 -nostdlib -fno-exceptions -fno-rtti -static -o $@

%.o: %.s
	$(AS) $< crt0.s -o $@

%.bin: %.o
	$(LD) -T $(LD_SCRIPT) $< -o $@

%.x: %.bin
	/opt/cross/mips-binutils/bin/mips-unknown-elf-objcopy -O binary $< $@

clean:
	rm -f *.o *.bin *.x
	for i in $$( ls *.s ); do if [ $$i != crt0.s ]; then rm $$i; fi; done
tester:
	gcc main_test.c src/vm.c src/HAL.c src/syscall.c sensors/encoder.c sensors/ultrasonic.c -o vmTester
