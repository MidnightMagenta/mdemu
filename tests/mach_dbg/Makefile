AS = ca65
LD = ld65

roms = rom.bin

all: $(roms)

clean:
	@echo CLEAN machine_debug
	@find -name "*.o" -type f -delete
	@find -name "*.bin" -type f -delete

%.bin: %.o
	$(LD) -C mach_dbg.cfg -o $@ $^

%.o: %.s
	$(AS) -o $@ $^
