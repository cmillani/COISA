pcloader:
	gcc pc_loader.c src/vm.c src/HAL.c src/syscall.c src/peripherals/encoder/CONFIG_encoder.c src/peripherals/ultrasonic/CONFIG_ultrasonic.c src/ARCH/atmega328/atmega328.c -o pc_loader
