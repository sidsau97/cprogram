/**
 *  variadic
 *  **note:** 注意书上直接粘贴过来有错误
 */
#include <stdio.h>
#include <stdarg.h>

#define DEBUG 1
#ifdef DEBUG
#define PR(X, ...)      printf("Message " #X ":"  __VA_ARGS__)
#else
//expected expression before ‘...’ token
// could not contain any white space between LOG_MSG and (...)
#define PR(...)
#endif

/* quote x */
#define STR(x) #x

#define JUST_CHECKING

// 类似 php 中的: func_num_args
double sum(int lim, ...);

int main(void) {
	double s, t;
	// 变长函数第一个参数是参数的数量
	s = sum(3, 1.1, 2.5, 13.3);
	t = sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);
	PR(1, "return value for " "sum(3, 1.1, 2.5, 13.3): %g\n", s);
	PR(2, "return value for " "sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): %g\n", t);
	printf("%s\n", STR(use '#' can quote everything as string\n));
	return 0;
}

double sum(int lim, ...) {
#ifdef JUST_CHECKING
	printf("%d\n", __LINE__);
#endif

	double total;
	int i = 0;
	// va_list(vl), va_start(vl, lim), va_arg(vl,double), va_end(vl);
	va_list vl;
	va_start(vl, lim);
	for (; i < lim; i++) {
		total += va_arg(vl, double);
	}
	va_end(vl);
	return total;
}
