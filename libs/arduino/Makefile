# C Compiler
CC=avr-gcc
CFLAGS=-c -g -Os -Wall -w -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=158 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I variants/standard -I .

# C++ Compiler
CXX=avr-g++
CXXFLAGS=-c -g -Os -Wall -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=158 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I variants/standard -I .

# Archive
AR=avr-ar
ARFLAGS=-rcs

# Sources
CSOURCES=$(wildcard *.c)
CXXSOURCES=$(wildcard *.cpp)
OBJECTS=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)
ARCHIVE=libarduino.a

all: $(ARCHIVE)

$(ARCHIVE): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(ARCHIVE)
	rm -f $(CSOURCES:.c=.o)
	rm -f $(CXXSOURCES:.cpp=.o)

