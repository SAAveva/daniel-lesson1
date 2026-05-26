run: build/main
	./build/main

build/main: main.c | build
	cc main.c -o build/main -lSDL2 -lm

clean:
	mkdir -p build

