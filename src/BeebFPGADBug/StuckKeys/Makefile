		include ../../Makefile.defs

AS=ca65 -I $(TOP)/includes 
LD=ld65

TARGETS=stuckkeys_l stuckkeys_n
DEPS=

OBJS_O=$(addprefix $(BUILD)/, $(addsuffix .o, $(OBJS)))
TARGETS_O=$(addprefix $(BUILD)/, $(addsuffix .bin, $(TARGETS)))

all:	$(TARGETS_O)
ssd:	all
deploy:	ssd


$(BUILD)/stuckkeys_l.o: stuckkeys.asm $(DEPS) $(INCS)
	$(AS) -o $@ -g -D LEDS -l $(basename $@).lst $<

$(BUILD)/stuckkeys_n.o: stuckkeys.asm $(DEPS) $(INCS)
	$(AS) -o $@ -g -l $(basename $@).lst $<


$(BUILD)/%.bin: $(BUILD)/%.o stuckkeys.cfg
	$(LD) -vm -Ln $(basename $@).sy2 -m $(basename $@).map -o $@ -C $(filter %.cfg, $^) $(basename $@).o $(LIBS)
	$(SCRIPTS)/getsymbols.pl <$(basename $@).sy2 >$(basename $@).noi
	cp $(notdir $@).inf $(BUILD)

clean:
	-rm $(OBJS_O)
	-rm $(patsubst %.o, %.lst, $(OBJS_O))
	-rm $(TARGETS_O)
	-rm $(addsuffix .inf, $(TARGETS_O))
	-rm $(patsubst %.bin, %.sy2, $(TARGETS_O))
	-rm $(patsubst %.bin, %.map, $(TARGETS_O))
	-rm $(patsubst %.bin, %.noi, $(TARGETS_O))
