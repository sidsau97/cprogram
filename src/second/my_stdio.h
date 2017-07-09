#include <stdio.h>
/*
 * my_stdio.h
 * (从内存种读取一行,不要纠结空间浪费问题)
 */
char* stdin_readLine(){
    int MAX_LINE_WIDTH = 1024;
	int i = 0, t;
	char a[MAX_LINE_WIDTH];
	char *p = a;

	for (i = 0; i <= MAX_LINE_WIDTH - 2; i++) {
		/*
		 * if(t = getchar() == EOF) break;
		 * Possible assignment in condition 't = getchar() == EOF'
		 */
		if (EOF == (t = getchar())) {
			break;
		}
		a[i] = t;
	}
	// 最后一个字符位置用于放 0, 这要保证字符串正常中止
	a[i] = 0;
	return p;
}

