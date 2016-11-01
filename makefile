###################### i386 Variables ######################
INCLUDE_i386 = -I src/ -I src/peripherals/encoder/ -I src/peripherals/movement/ -I src/peripherals/PWM/ -I src/peripherals/serial/ -I src/peripherals/ultrasonic/ -I src/ARCH/i386_OS/ -I src/peripherals/timer/ -I src/peripherals/button/ -I src/peripherals/leds/ -I src/peripherals/stepper/
CC_i386 = gcc
CFLAGS_i386 = -DARCH=1  -DMEASURING=0 -DRUN_VM=1 -DCOUNTING=0 -DCOUNTING_STACK=0 -Os
############################################################

###################### Dir Variables #######################
OBJDIR = bin
SRCDIR = src
BENCHDIR = benchmarks
MIPSDIR = MipsCTestCases
TESTSDIR = tests
############################################################

################## i386 Output File Name ###################
NAME = microvm
############################################################

GOLDENMODELS = $(BENCHDIR)/goldenmodels
MODELS = $(BENCHDIR)/models

##################### Arduino Variables ####################
ARDUINO_BIN = /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin
ARDUINO_AVR = /Applications/Arduino.app/Contents/Java/hardware/arduino/avr
AVRDUDE_CONF = /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf

AVRDUDE = $(ARDUINO_BIN)/avrdude
AVR_OBJCPY = $(ARDUINO_BIN)/avr-objcopy
AVR_SIZE = $(ARDUINO_BIN)/avr-size

ARCHFILES_avr = ARCH_avr_timer.o ARCH_avr_encoder.o ARCH_avr_movement.o ARCH_avr_PWM.o ARCH_avr_serial.o ARCH_avr_ultrasonic.o ARCH_avr_button.o ARCH_avr_leds.o ARCH_avr_magnetometer.o ARCH_avr_i2c.o ARCH_avr_IMU.o ARCH_avr_stepper.o
FLAGS_avr = -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10603 -DARDUINO_AVR_UNO -DARDUINO_ARCH_A -DRUN_VM=1 -DMEASURING=0 -DEVENT_ON=1 -DSIMAVR=0 -lm
INCLUDE_avr = -I$(ARDUINO_AVR)/cores/arduino -I$(ARDUINO_AVR)/variants/standard -I src/ -I src/peripherals/encoder/ -I src/peripherals/movement/ -I src/peripherals/PWM/ -I src/peripherals/serial/ -I src/peripherals/ultrasonic/ -I src/peripherals/timer/ -I src/peripherals/button/ -I src/peripherals/leds/ -I src/ARCH/atmega328/ -I src/peripherals/magnetometer -I src/peripherals/i2c -I src/peripherals/IMU -I src/peripherals/stepper
REQOBJ_avr = $(addprefix $(OBJDIR)/, avr_static/core.a atmega328.o $(ARCHFILES_avr) vm.o syscall.o HAL.o TM.o EH.o CONFIG_timer.o ArduinoLoader.o CONFIG_ultrasonic.o stdutils.o CONFIG_encoder.o)
CC_avr = $(ARDUINO_BIN)/avr-g++

PORT = /dev/cu.wchusbserial1410 
#/dev/cu.usbmodem1411
#############################################################

################# Mips Guest Code Variables #################
LD_mips=/opt/cross/mips-binutils/bin/mips-unknown-elf-ld
LD_SCRIPT_mips=$(MIPSDIR)/linker.ld
AS_mips=/opt/cross/mips-binutils/bin/mips-unknown-elf-as
INCLUDE_mips = -I $(MIPSDIR)/extras/lib/
CFLAGS_mips = -Os -nostdlib -fno-exceptions -fno-rtti -static -fno-builtin -nostdinc
# LIBRARIES_mips = $(addprefix $(MIPSDIR)/,extras/crt0.s extras/lib/THING_serial.s extras/lib/THING_movement.s)
LIBRARIES_mips = $(addprefix $(MIPSDIR)/,extras/crt0.s extras/lib/THING_ultrasonic.s extras/lib/THING_serial.s extras/lib/THING_encoder.s extras/lib/THING_movement.s extras/lib/THING_EH.s extras/lib/THING_button.s)
#############################################################


BENCHMARK_FILES = ackermann array fib lists matrix sieve heapsort random
# random

CC = gcc
CFLAGS = 
LFLAGS = 

FOLDERS = $(GOLDENMODELS) $(MODELS)

.PHONY: results clean data

all: $(FOLDERS) $(TESTSDIR) i386 bench_files
	
####################### Benchmarking ########################
allbench:
	./bench.sh
	
data: mips_benchmarks $(OBJDIR)/$(NAME)
	./tests.sh
	
perf_data: mips_benchmarks $(OBJDIR)/$(NAME)
	./perf.sh

bench_files: goldenmodels mips_benchmarks
	
goldenmodels: $(addprefix $(BENCHDIR)/goldenmodels/,$(addsuffix .o, $(BENCHMARK_FILES))) $(addprefix $(BENCHDIR)/goldenmodels/,$(addsuffix .out, $(BENCHMARK_FILES)))
	
mips_benchmarks:$(addprefix $(BENCHDIR)/models/,$(addsuffix .x, $(BENCHMARK_FILES))) $(addprefix $(BENCHDIR)/models/,$(addsuffix .out, $(BENCHMARK_FILES)))

results: $(addprefix $(BENCHDIR)/models/,$(addsuffix .out, $(BENCHMARK_FILES))) $(addprefix $(BENCHDIR)/goldenmodels/,$(addsuffix .out, $(BENCHMARK_FILES)))
	@echo ">>>>>>>>>>Starting Output Tests<<<<<<<<<<"
	@echo
	@for f in $(addsuffix .out, $(BENCHMARK_FILES)); do \
		echo "$$f:"; \
		diff $(GOLDENMODELS)/$$f $(MODELS)/$$f; \
	done
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

#############################################################


#################### i386 VM Compilation ####################
i386:
	$(CC_i386) $(INCLUDE_i386) $(CFLAGS_i386) src/*.c src/ARCH/i386_OS/*.c -o $(OBJDIR)/$(NAME)
#############################################################

################### Arduino VM Compilation ##################
atmega328: link atmega328_write
	
link: $(REQOBJ_avr)
	$(CC_avr) -w -Os -Wl,--gc-sections -mmcu=atmega328p -o bin/ArduinoLoader.elf $^ -L $(OBJDIR)/avr_static -lm
	$(AVR_OBJCPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(OBJDIR)/ArduinoLoader.elf $(OBJDIR)/ArduinoLoader.eep
	$(AVR_OBJCPY) -O ihex -R .eeprom $(OBJDIR)/ArduinoLoader.elf $(OBJDIR)/$(NAME).hex
	@echo ">>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<"
	$(AVR_SIZE) bin/ArduinoLoader.elf
	@echo ">>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<"

atmega328_write:
	$(AVRDUDE) -C$(AVRDUDE_CONF) -v -patmega328p -carduino -P$(PORT) -b115200 -D -Uflash:w:$(OBJDIR)/$(NAME).hex:i 	
	
avrsim_write:
	$(AVRDUDE) -C$(AVRDUDE_CONF) -v -patmega328p -carduino -P$(DEVICEPATH) -b115200 -D -Uflash:w:$(OBJDIR)/$(NAME).hex:i 	

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
#############################################################

######################## Cleaning ###########################
clean:
	rm -r $(OBJDIR)/*[!avr_static] $(MODELS)/*
vm_clean: 
	rm -r $(OBJDIR)/*[!avr_static]
#############################################################
