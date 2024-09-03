build:
	gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lm -o game `sdl2-config --cflags` `sdl2-config --libs`

run:
	./game

clean:
	rm game
