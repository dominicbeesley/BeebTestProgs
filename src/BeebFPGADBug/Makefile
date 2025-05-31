		include ../Makefile.defs

SSD=$(SSDS)/BeebFPGADBug.ssd
DEPLOY=$(DEPLOY_TOP)/BeebFPGADBug

SUBDIRS=stuckkeys
OBJS=stuckkeys/stuckkeys.bin 
EXTRAS=$(basename $(wildcard extras/*.inf))

OBJS_O=$(addprefix $(BUILD)/, $(OBJS))

.DELETE_ON_ERROR:

.PHONY: clean all $(SUBDIRS)

all: $(SUBDIRS)
ssd: all $(SSD)

clean: $(SUBDIRS)
	-rm $(SSD)

deploy: ssd
	mkdir -p $(DEPLOY)
	dfs read -i -d $(DEPLOY) $(SSD)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

$(BUILD)/stuckkeys/stuckkeys.bin:
	make -C stuckkeys all

$(SSD):	$(OBJS_O)
	dfs form -80 $(SSD)
	dfs title $(SSD) "BFPGADBUG"
	dfs add $(SSD) $(addsuffix .inf, $(OBJS_O) $(EXTRAS))
