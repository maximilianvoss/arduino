# C Compiler
CC=avr-gcc
CFLAGS=-c -g -Os -Wall -w -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=158 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I libs/arduino -I libs/tetris -I libs/arduino/variants/standard -I libs/USB_Host_Shield_2.0 -I libs/ledboard -I . 

# C++ Compiler
CXX=avr-g++
CXXFLAGS=-c -g -Os -Wall -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=158 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I libs/arduino -I libs/tetris -I libs/arduino/variants/standard -I libs/USB_Host_Shield_2.0 -I libs/ledboard -I .

# Linking
LDFLAGS=-L libs/arduino -L libs/arduino/SPI -L libs/USB_Host_Shield_2.0 -L libs/tetris -L libs/ledboard -lspi -lhostshield -ltetris -lledboard-ard -larduino
ALLFLAGS=-w -Os -Wl,--gc-sections -mmcu=atmega328p

# AVR Object
OBJCOPY=avr-objcopy
HEXFLAGS=-O ihex -R .eeprom
EEPFLAGS=-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0

# AVR Dude
AVRDUDE=avrdude
AVRDUDEFLAGS=-Cetc/avrdude.conf -v -patmega328p -carduino -D 

# AVR Size
AVRSIZE=avr-size

# Sources
CSOURCES=$(wildcard *.c)
CXXSOURCES=$(wildcard *.cpp)
OBJECTS=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)
EXECUTABLE=tetris.elf
HEXFILE=$(EXECUTABLE:.elf=.hex)

# Libraries
LIBRARY=libs
BUILD-LIBRARY=$(LIBRARY:%=build-%)
CLEAN-LIBRARY=$(LIBRARY:%=clean-%)

ifeq ($(SERIAL_PORT),)
	SERIAL_PORT=/dev/cu.usbmodem1411
endif
ifeq ($(SERIAL_BAUDRATE),)
	SERIAL_BAUDRATE=115200
endif

all: all-clean build

build: $(BUILD-LIBRARY) size 

upload: $(HEXFILE)
	$(AVRDUDE) $(AVRDUDEFLAGS) -P$(SERIAL_PORT) -b$(SERIAL_BAUDRATE) -Uflash:w:$<:i 

size: $(EXECUTABLE)
	$(AVRSIZE) $<

$(HEXFILE): $(EXECUTABLE)
	$(OBJCOPY) $(HEXFLAGS) $< $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(ALLFLAGS) $(OBJECTS) --output $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD-LIBRARY):
	$(MAKE) -C $(@:build-%=%)

all-clean: clean clean-library

clean:
	rm -f $(HEXFILE)
	rm -f $(EXECUTABLE)
	rm -f $(CSOURCES:.c=.o)
	rm -f $(CXXSOURCES:.cpp=.o)

clean-library: $(CLEAN-LIBRARY)
$(CLEAN-LIBRARY):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(BUILD-LIBRARY)
.PHONY: clean all