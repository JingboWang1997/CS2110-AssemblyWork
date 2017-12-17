
run-tests: clean verify tests
	./tests

run-valgrind: clean  verify tests
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./tests

debug: clean verify tests
	gdb ./tests

submit: array_list.c
	rm -f tl6.tar.gz
	tar -czvf tl6.tar.gz array_list.c

tests: array_list.c tests.c
	gcc -Wl,--wrap=malloc,--wrap=free,--wrap=calloc,--wrap=realloc -Wall -Werror -pedantic -std=c99 -g array_list.c tests.c -o tests

verify : verify.sh
	@/bin/bash verify.sh

clean:
	rm -f tl6.tar.gz tests
