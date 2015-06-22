PROGRAM ?= 
EXTRAS ?=

arduino_burn:
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/cu.usbmodem1411 -b115200 -D -Uflash:w:ArduinoLoader.hex:i 

arduino_compile:
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10603 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/variants/standard ArduinoLoader.cpp ../src/*.c ../src/ARCH/atmega328/*.c 

	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -w -Os -Wl,--gc-sections -mmcu=atmega328p -o ArduinoLoader.elf ArduinoLoader.o core.a vm.o syscall.o atmega328.o HAL.o ARCH*.o -L. -lm
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 ArduinoLoader.elf ArduinoLoader.eep
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom ArduinoLoader.elf ArduinoLoader.hex
