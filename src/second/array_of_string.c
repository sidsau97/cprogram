#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nmax 1000
#define Mmax 1000


// int (*compar)(const void *, const void*)
// the prototype of function must match the prototype of the last parameter of qsort

// 整数的比较范例
// 大写字母的 ascii 值小于小写字母
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int compare(const void *i, const void *j) {
//	int strcmp (const char *__s1, const char *__s2)
//	expected ‘const char *’ but argument is of type ‘char **’
	// 将任意类型的指针转为字符串指针
	return strcmp( *(char **)i, *(char **)j);
}

int main() {
	char buf[Mmax];
	int M = 0;
	// 该例子中,字符串数组存放的是长度不一致的一系列字符串, 类似于 MYSQL varChar
	int i, N;
	char * a[Nmax];
	for (N = 0; N < Nmax; N++) {
		a[N] = &buf[M]; // a[0] = buf[0]
		// 不要输入太长的字符串,以免内存覆盖
		if (scanf("%s", a[N]) == EOF)
			break;
//format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘size_t {aka long unsigned int}
//[Some platforms have problems with %zu. Try printing it using %lu](https://stackoverflow.com/questions/17842293/c-size-t-not-printing-in-printf)
//		printf("the length of a[N] is :%lu\n", strlen(a[N]));
		// c 会自动将 long unsigned integer 转化为 int
		M += strlen(a[N]) + 1;
	}
//	int (*)(const void *, const void *)}’
//	but argument is of type ‘int (*)(void *, void *)
//	fix: add keywords "const" for each parameter of the function
	qsort(a, N, sizeof(char *), compare);
	for (i = 0; i < N; i++) {
		printf("%s\n", a[i]);
	}
	return 0;
}
