CC=/usr/bin/gcc
CXX=/usr/bin/g++
CFLAGS=-c -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -std=gnu99
CXXFLAGS=-Wall -c -std=c++0x -DPC_DEBUG
LDFLAGS=
ALLFLAGS=-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -std=gnu99
CSOURCES=$(wildcard *.c)
CXXSOURCES=$(wildcard *.cpp)
OBJECTS=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)
EXECUTABLE=tetris

all: clean $(SOURCESC) $(SOURCESCPP) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(ALLFLAGS) $(OBJECTS) --output $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE)
	rm -f $(CSOURCES:.c=.o)
	rm -f $(CXXSOURCES:.cpp=.o)
