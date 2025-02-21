all: linux

linux:
	mkdir -p builds/linux
	cd builds/linux && cmake ../.. && make

windows:

	mkdir -p builds/windows
	cd builds/windows && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../toolchain.cmake && make

run:
	cd builds/linux && ./main

clean:
	@rm -rf builds
	@rm -rf build