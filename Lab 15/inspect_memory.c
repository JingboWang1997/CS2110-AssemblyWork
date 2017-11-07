#include <stdio.h>

void print_my_stack(int call_number, int max_calls);

char a = 1;
static char b = 2;

int main() {
	printf("Code area of memory:\n");
	printf("  &main=%p\n  &print_my_stack=%p\n\n", &main, &print_my_stack);
	
	printf("Globals:\n  &a=%p\n  &b=%p\n\n", &a, &b);
	
	print_my_stack(0, 5);
}

void print_my_stack(int call_number, int max_calls) {
	int c = 1;
	static char d = 0;
	d++;
	printf("Call #%d\n  &local=%p\n", call_number, &c);
	printf("  &static var (inside function): %p\n", &d);
	printf("  static var (inside function) value = %d\n", d);
	if (call_number < max_calls) {
		print_my_stack(call_number + 1, max_calls);
	}
}