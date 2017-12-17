
run-tests: clean  tests
	./tests

tests: array_list.c tests.c
	gcc -Wl,--wrap=malloc,--wrap=free,--wrap=calloc,--wrap=realloc -Wall -Werror -pedantic -std=c99 -g array_list.c tests.c -o tests

grader-tar:
	tar -czvf grader.tar.gz array_list.h Makefile tests.c tests.h

clean:
	rm -f tl6.tar.gz tests gradelog.json grader.tar.gz
