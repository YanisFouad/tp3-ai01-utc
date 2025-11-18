build:
	gcc -o main main.c global.c fcfs.c sjf.c -Wall -Wextra -g

clean:
	rm -f main

run: build
	./main