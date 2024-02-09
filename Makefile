build:
	gcc -Wall -std=c99 ./src/*.c -o SimplyGame

run:
	./SimplyGame

clean:
	rm SimplyGame
