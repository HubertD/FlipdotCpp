all: pc

pc: sdl vcd

sdl:
	$(MAKE) -f Makefile.SDL

vcd:
	$(MAKE) -f Makefile.VCD

clean:
	rm -rf obj/
	rm -rf bin/
