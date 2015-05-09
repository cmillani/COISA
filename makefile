pcloader:
	gcc pc_loader.c src/vm.c src/HAL.c src/syscall.c sensors/encoder.c sensors/ultrasonic.c -o pc_loader
