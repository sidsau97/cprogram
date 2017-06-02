#include <stdio.h>
/*
 * my_stdio.h
 *
 *  Created on: Apr 10, 2017
 *      Author: root
 */
char* stdin_read(){
	int i = 0, t;
	int N = 1024;
	char a[N];
	char *p = a;
	//随后一个字符位置用于放 0
	for (i = 0; i < N - 1; i++) {
		/*
		 * bug:
		 * if(t = getchar() == EOF) break;
		 * Possible assignment in condition 't = getchar() == EOF'
		 * 注意运算符的优先级
		 */
		if ((t = getchar()) == EOF) {
			break;
		}
		a[i] = t;
	}
	a[i] = 0;
	return p;
}

