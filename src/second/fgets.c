#include <stdio.h>
int main() {
	char buf[20];
//	Get a newline-terminated string of finite length from STREAM.
// NULL will return if fgets() read EOF
	puts("please enter a string, the max size allowed is 20");
	// 当超过给定长度-1后,自动拆未两行
	while (NULL != (fgets(buf, sizeof(buf), stdin))) {
		if ('\n' == *buf)
			break;
		printf("%s\n", buf);
	}
	return 0;
}
