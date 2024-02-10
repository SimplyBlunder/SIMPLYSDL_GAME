build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o SimplyLoop

run:
	./SimplyGame

clean:
	rm SimplyGame
