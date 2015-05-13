pcloader:
	gcc pc_loader.c src/vm.c src/HAL.c src/syscall.c peripherals/encoder.c peripherals/ultrasonic.c ARCH/atmega328.c -o pc_loader
