default: bake run

bake:
	mkdir -p build
	cd build; cmake ..; make -j3

run:
	bin/arkenon

clean:
	rm -r build
