#include <stdio.h>
int main(int argc,char *argv[]) {
	char a[] = "*+ 7 * * 4 6 +  8 91 50";
	int i = 0;
	/**
	 * 函数返回一个数字
	 */
	int eval() {
		int x = 0;

		while (a[i] == ' ')
			i++;

		if (a[i] == '+') {
			i++;
			return eval() + eval();
		}

		if (a[i] == '*') {
			i++;
			return eval() * eval();
		}

		//string to integer
		while ((a[i] >= '0') && (a[i] <= '9')) {
			x = x * 10 + (a[i] - '0');
			i++;
		}
		return x;
	}
	int result;
	result = eval();
	/**
	 *在c语言中要特别注意单引号和双引号的区别
	 */
	printf("%d\n", result);
	return 0;
}
