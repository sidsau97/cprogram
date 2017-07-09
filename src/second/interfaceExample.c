/*complile with int.c, Num.h*/
#include <stdio.h>
#include <stdlib.h>
#include "Num.h"

// gcc 在编译的时候,如果没有申明接口的具体实现,会在当前目录下取找接口的实现(可能会找到多个,因而产生冲突)
// 需要在编译的时候,决定好相应的实现
int main(int argc, char *argv[]) {
	int i, N = atoi(argv[1]);
	float m1 = 0.0;
	Number x;
	for (i = 0; i < N; i++) {
		x = randNum();
		m1 += ((float) x) / N;
	}
	printf("       Average: %f\n", m1);
	return 0;
}
