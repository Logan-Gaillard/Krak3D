.PHONY: all linux windows runl runw clean

all: linux

linux:
	mkdir -p builds/linux
	cd builds/linux && cmake ../.. && make

windows:
	mkdir -p builds/windows
	cd builds/windows && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../toolchain.cmake && make

runl:
	cd builds/linux && ./main

runw:
	cd builds/windows && ./main.exe


clean:
	@rm -rf builds
	@rm -rf build