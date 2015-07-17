INCLUDE_i386 = -I src/ -I src/peripherals/encoder/ -I src/peripherals/movement/ -I src/peripherals/PWM/ -I src/peripherals/serial/ -I src/peripherals/ultrasonic/ -I src/ARCH/i386_OS/
CC_i386 = gcc
CFLAGS_i386 = -DARCH=1 # -DMEASURING=1

OBJDIR = bin
SRCDIR = src
BENCHDIR = benchmarks
MIPSDIR = MipsCTestCases
TESTSDIR = tests

NAME = microvm

GOLDENMODELS = $(BENCHDIR)/goldenmodels
MODELS = $(BENCHDIR)/models

ARCHFILES_avr = ARCH_avr_serial.o
# ARCHFILES_avr = ARCH_avr_encoder.o ARCH_avr_movement.o ARCH_avr_PWM.o ARCH_avr_serial.o ARCH_avr_ultrasonic.o
FLAGS_avr = -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10603 -DARDUINO_AVR_UNO -DARDUINO_ARCH_A
INCLUDE_avr = -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/NewArduino.app/Contents/Java/hardware/arduino/avr/variants/standard -I src/ -I src/peripherals/encoder/ -I src/peripherals/movement/ -I src/peripherals/PWM/ -I src/peripherals/serial/ -I src/peripherals/ultrasonic/ 
OBJFILES_avr = ArduinoLoader.o avr_static/core.a vm.o syscall.o atmega328.o HAL.o $(ARCHFILES_avr)
REQOBJ_avr = $(addprefix $(OBJDIR)/, ArduinoLoader.o avr_static/core.a vm.o syscall.o atmega328.o HAL.o $(ARCHFILES_avr) ) 
CC_avr = /Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++

LD_mips=/opt/cross/mips-binutils/bin/mips-unknown-elf-ld
LD_SCRIPT_mips=$(MIPSDIR)/linker.ld
AS_mips=/opt/cross/mips-binutils/bin/mips-unknown-elf-as
INCLUDE_mips = -I $(MIPSDIR)/extras/lib/
CFLAGS_mips = -Os -nostdlib -fno-exceptions -fno-rtti -static -fno-builtin -nostdinc
LIBRARIES_mips = $(addprefix $(MIPSDIR)/,extras/crt0.s extras/lib/THING_serial.s)
# LIBRARIES_mips = $(addprefix $(MIPSDIR)/,extras/crt0.s extras/lib/THING_ultrasonic.s extras/lib/THING_serial.s extras/lib/THING_encoder.s extras/lib/THING_movement.s)

BENCHMARK_FILES = ackermann array fib lists matrix sieve heapsort random
# random

CC = gcc
CFLAGS = 
LFLAGS = 

FOLDERS = $(GOLDENMODELS) $(MODELS)

.PHONY: results clean data

all: $(FOLDERS) $(TESTSDIR) i386 bench_files
	
data: mips_benchmarks $(OBJDIR)/$(NAME)
	./tests.sh

bench_files: goldenmodels mips_benchmarks
	
goldenmodels: $(addprefix $(BENCHDIR)/goldenmodels/,$(addsuffix .o, $(BENCHMARK_FILES))) $(addprefix $(BENCHDIR)/goldenmodels/,$(addsuffix .out, $(BENCHMARK_FILES)))
	
mips_benchmarks:$(addprefix $(BENCHDIR)/models/,$(addsuffix .x, $(BENCHMARK_FILES))) $(addprefix $(BENCHDIR)/models/,$(addsuffix .out, $(BENCHMARK_FILES)))

results: $(addprefix $(BENCHDIR)/models/,$(addsuffix .out, $(BENCHMARK_FILES))) $(addprefix $(BENCHDIR)/goldenmodels/,$(addsuffix .out, $(BENCHMARK_FILES)))
	@echo ">>>>>>>>>>Starting Output Tests<<<<<<<<<<"
	@echo
	@echo
	@for f in $(addsuffix .out, $(BENCHMARK_FILES)); do \
		echo "$$f:"; \
		diff $(GOLDENMODELS)/$$f $(MODELS)/$$f; \
	done
	@echo
	@echo
	@echo ">>>>>>>>>>>All Tests Completed<<<<<<<<<<<" 
	
$(TESTSDIR):
	mkdir -p $(TESTSDIR)
	
$(FOLDERS) :
	mkdir -p $(FOLDERS)

$(BENCHDIR)/models/%.s: $(BENCHDIR)/src/%.c
	$(HOME)/ellcc/bin/ecc -target mips-linux-eng -S $< $(INCLUDE_mips) $(CFLAGS_mips) -o $@

$(MODELS)/%.o: $(MODELS)/%.s
	$(AS_mips) $< $(LIBRARIES_mips) -o $@

$(MODELS)/%.bin: $(MODELS)/%.o
	$(LD_mips) -T $(LD_SCRIPT_mips) $< -o $@

$(MODELS)/%.x: $(MODELS)/%.bin
	/opt/cross/mips-binutils/bin/mips-unknown-elf-objcopy -O binary $< $@

$(MODELS)/%.out: $(MODELS)/%.x
	./$(OBJDIR)/$(NAME) $^ > $@

$(GOLDENMODELS)/%.o: $(BENCHDIR)/src/%.c
	$(CC) $(CFLAGS) $^ -DX86 -o $@
	
$(GOLDENMODELS)/%.out: $(GOLDENMODELS)/%.o
	./$^ > $@


i386:
	$(CC_i386) $(INCLUDE_i386) $(CFLAGS_i386) src/*.c src/ARCH/i386_OS/*.c -o $(OBJDIR)/$(NAME)

atmega328: link atmega328_write
	
link: $(REQOBJ_avr)
	$(CC_avr) -w -Os -Wl,--gc-sections -mmcu=atmega328p -o bin/ArduinoLoader.elf $^ -L $(OBJDIR)/avr_static -lm
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(OBJDIR)/ArduinoLoader.elf $(OBJDIR)/ArduinoLoader.eep
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $(OBJDIR)/ArduinoLoader.elf $(OBJDIR)/$(NAME).hex
	@echo ">>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<"
	avr-size bin/ArduinoLoader.elf
	@echo ">>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<"

atmega328_write:
	/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/NewArduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/cu.usbmodem1421 -b115200 -D -Uflash:w:$(OBJDIR)/$(NAME).hex:i 	

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

clean:
	rm -r $(OBJDIR)/*[!avr_static] $(FOLDERS)
