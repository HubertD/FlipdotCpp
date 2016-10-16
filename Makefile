all: pc

pc: sdl

sdl:
	$(MAKE) -f Makefile.SDL

clean:
	rm -rf obj/
	rm -rf bin/
