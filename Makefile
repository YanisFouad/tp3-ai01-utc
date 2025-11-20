build:
	gcc -o main main.c global.c fcfs.c sjf.c gantt.c -Wall -Wextra -g

clean:
	rm -f main ./img/*.png ./data

run: build
	./main