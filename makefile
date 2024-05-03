.PHONY: clean build

build:
	cmake -B build
	cmake --build build -j24

clean:
	rm -rf build

rebuild:
	make clean
	make build

