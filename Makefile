all: pc stm32

pc: sdl vcd

stm32: cubemx

sdl:
	$(MAKE) -f Makefile.SDL

vcd:
	$(MAKE) -f Makefile.VCD

cubemx:
	$(MAKE) -f Makefile.CubeMX

stm32f4:
	$(MAKE) -f Makefile.STM32F4

clean:
	rm -rf obj/
	rm -rf bin/
