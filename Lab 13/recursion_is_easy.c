#include <stdio.h>
#define FACT_FORMAT "fact(%d) == %d == 0x%x"

int factorial(int n);

int main(int argc, const char* argv[])
{
	printf(FACT_FORMAT, 1, factorial(1), factorial(1));
	printf(FACT_FORMAT, 2, factorial(2), factorial(2));
	printf(FACT_FORMAT, 5, factorial(5), factorial(5));
	printf(FACT_FORMAT, 7, factorial(7), factorial(7));
}

int factorial(int n)
{
	if (n == 1 || n == 0) {
		return n;
	}
	return factorial(n-1) + factorial(n-2);
}