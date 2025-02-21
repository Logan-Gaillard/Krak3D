all: linux

linux:
	@g++ main.cpp -o main -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl

clean:
	@rm main