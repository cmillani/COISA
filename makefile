INCLUDE_i386 = -I src/ -I src/peripherals/encoder/ -I src/peripherals/movement/ -I src/peripherals/PWM/ -I src/peripherals/serial/ -I src/peripherals/ultrasonic/ -I src/ARCH/i386_OS/
CC_i386 = gcc

OBJDIR = bin
SRCDIR = src
NAME = microvm

ARCHFILES_avr = ARCH_avr_encoder.o ARCH_avr_movement.o ARCH_avr_PWM.o ARCH_avr_serial.o ARCH_avr_ultrasonic.o
FLAGS_avr = -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10603 -DARDUINO_AVR_UNO -DARDUINO_ARCH_A
INCLUDE_avr = -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/variants/standard -I src/ -I src/peripherals/encoder/ -I src/peripherals/movement/ -I src/peripherals/PWM/ -I src/peripherals/serial/ -I src/peripherals/ultrasonic/ 
OBJFILES_avr = ArduinoLoader.o avr_static/core.a vm.o syscall.o atmega328.o HAL.o $(ARCHFILES_avr)
REQOBJ_avr = $(addprefix $(OBJDIR)/, ArduinoLoader.o avr_static/core.a vm.o syscall.o atmega328.o HAL.o $(ARCHFILES_avr) ) 

CC_avr = /Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++


i386:
	$(CC_i386) $(INCLUDE_i386) -DARCH=1 src/*.c src/ARCH/i386_OS/*.c -o $(OBJDIR)/$(NAME)

atmega328: link

teste:
	@echo $(REQOBJ_avr)

$(OBJDIR)/%.o: $(SRCDIR)/*/*/%.cpp
	$(CC_avr) $(FLAGS_avr) $(INCLUDE_avr) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/*/%.cpp
	$(CC_avr) $(FLAGS_avr) $(INCLUDE_avr) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC_avr) $(FLAGS_avr) $(INCLUDE_avr) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/*/*/%.c
	$(CC_avr) $(FLAGS_avr) $(INCLUDE_avr) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/*/%.c
	$(CC_avr) $(FLAGS_avr) $(INCLUDE_avr) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC_avr) $(FLAGS_avr) $(INCLUDE_avr) $^ -o $@

link: $(REQOBJ_avr)
	$(CC_avr) -w -Os -Wl,--gc-sections -mmcu=atmega328p -o bin/ArduinoLoader.elf $^ -L $(OBJDIR)/avr_static -lm
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(OBJDIR)/ArduinoLoader.elf $(OBJDIR)/ArduinoLoader.eep
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $(OBJDIR)/ArduinoLoader.elf $(OBJDIR)/$(NAME).hex

atmega328_write:
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/cu.usbmodem1411 -b115200 -D -Uflash:w:ArduinoLoader.hex:i 

clean:
	rm $(OBJDIR)/*
