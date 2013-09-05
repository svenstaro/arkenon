default: bake run

bake:
	mkdir -p build
	cd build; cmake ..; make -j3

run:
	bin/arkenon

debug:
	gdb bin/arkenon

docs:
	doxygen

clean:
	rm -r build
