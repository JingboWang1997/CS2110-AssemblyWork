CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra
DEBUG_FLAGS = -g -DDEBUG

run-test : build-debug
	./test

run-gdb : build-debug
	gdb ./test

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./test

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : verify list.o test.o list.h
	$(CC) $(CFLAGS) test.o list.o -o test

list.o : list.c list.h
	$(CC) $(CFLAGS) -c list.c

test.o : test.c list.h
	$(CC) $(CFLAGS) -c test.c

clean :
	rm -f *.o test

submit : verify
	tar -czf list_submission.tar.gz list.c

verify : verify.sh
	@/bin/bash verify.sh

