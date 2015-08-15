DEBUG=Makefile-DEBUG
ARDUINO=Makefile-ARDUINO

all: arduino

arduino:
	$(MAKE) -f $(DEBUG) clean
	$(MAKE) -f $(ARDUINO) clean all

debug:
	$(MAKE) -f $(ARDUINO) clean
	$(MAKE) -f $(DEBUG) clean all

clean:
	$(MAKE) -f $(DEBUG) clean
	$(MAKE) -f $(ARDUINO) clean