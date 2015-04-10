DIRS=arduino USB_Host_Shield_2.0 tetris 
BUILD-DIRS=$(DIRS:%=build-%)
CLEAN-DIRS=$(DIRS:%=clean-%)

all: $(BUILD-DIRS) 
$(BUILD-DIRS):
	$(MAKE) -C $(@:build-%=%)

clean: $(CLEAN-DIRS)
$(CLEAN-DIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(BUILD-DIRS)
.PHONY: clean all