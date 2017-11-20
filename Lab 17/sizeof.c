#include <stdio.h>

struct p {char a; char b;};

int main(int argc, char const *argv[])
{
	printf("char: %lu\n", sizeof(char));
	printf("short: %lu\n", sizeof(short));
	printf("int: %lu\n", sizeof(int));
	printf("long: %lu\n", sizeof(long));
	printf("int*: %lu\n", sizeof(int*));
	printf("char*: %lu\n", sizeof(char*));
	printf("struct{char, char}: %lu\n", sizeof(struct{char a; char b;}));
	printf("struct{short, char, int}: %lu\n", sizeof(struct{short p; char a; int b;}));

}