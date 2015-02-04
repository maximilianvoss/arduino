# C Compiler
CC=avr-gcc
CFLAGS=-c -g -Os -w -Wall -Wl,--gc-sections -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=158 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I variants/standard -I .

# Archive
AR=avr-ar
ARFLAGS=-rcs

# Sources
CSOURCES=$(wildcard *.c)
OBJECTS=$(CSOURCES:.c=.o)
ARCHIVE=libtetris.a

all: $(ARCHIVE)

$(ARCHIVE): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(ARCHIVE)
	rm -f $(CSOURCES:.c=.o)

