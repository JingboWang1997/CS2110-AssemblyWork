#include <stdio.h>
#define FACT_FORMAT "fact(%d) == %d == 0x%x"

int factorial(int n);

int main(int argc, const char* argv[])
{
	char firstname[100];
	char lastname[100];
	char maidenname[100]; 
	char city[100];

	printf("firstname:\n");
	scanf("%s", firstname);
	printf("last name:\n");
	scanf("%s", lastname);
	printf("maiden name:\n");
	scanf("%s", maidenname);
	printf("city:\n");
	scanf("%s", city);

	printf("Star War Name: %c%c%c%c%c %c%c%c%c%c\n", firstname[0], firstname[1], firstname[2], lastname[0], lastname[1], maidenname[0], maidenname[1], city[0], city[1], city[2]);
}