all: linker.ld firstTest.c
	$(HOME)/ellcc/bin/ecc -target mips-linux-eng -c firstTest.c -O0 -nostdlib -fno-exceptions -fno-rtti -static -o obj.o
	/opt/cross/mips-binutils/bin/mips-unknown-elf-ld -T linker.ld obj.o -o prog.bin
	/opt/cross/mips-binutils/bin/mips-unknown-elf-objcopy -O binary prog.bin binary.bin	
	rm obj.o
	rm prog.bin
