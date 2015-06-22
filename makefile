PROGRAM ?= 
EXTRAS ?=

pcloader:
	gcc pc_loader.c src/*.c src/ARCH/atmega328/*.c -o pc_loader
arduino_burn:
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/cu.usbmodem1411 -b115200 -D -Uflash:w:$(PROGRAM):i 

arduino_compile:
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10603 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/variants/standard $(PROGRAM) $(EXTRAS) 

	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -w -Os -Wl,--gc-sections -mmcu=atmega328p -o $(PROGRAM).elf $(PROGRAM).o ArduinoCompileSample/core.a -LArduinoCompileSample/ -lm
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(PROGRAM).elf $(PROGRAM).eep
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $(PROGRAM).elf $(PROGRAM).hex
