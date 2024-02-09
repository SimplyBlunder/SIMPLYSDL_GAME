build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o SimplyGame

run:
	./SimplyGame

clean:
	rm SimplyGame
