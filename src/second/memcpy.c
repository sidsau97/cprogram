/**
 * mems.c -- using memcpy() and memmove()
 * memmove在copy两个有重叠区域的内存时可以保证copy的正确，而memcopy就不行了
 * @TODO why memcpy and memmove seems work in the same way?
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
void printStrings(const int ar[], int n);

void printStrings(const int ar[], int n) {
	int i;
	printf("[ ");
	for (i = 0; i < n - 1; i++)
		printf("%d, ", ar[i]);
	printf("%d ", ar[i]);
	putchar(']');
	putchar('\n');
}

int main() {
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printStrings(a, SIZE);
	puts("\nUsing memcpy() with overlapping ranges:");
	memcpy(a + 4, a, sizeof(int) * 6);
	printStrings(a, SIZE);

	int b[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	puts("\nUsing memmove() with overlapping ranges:");
	memmove(b + 4, b, sizeof(int) * 6);
	printStrings(b, SIZE);
	return 0;
}
