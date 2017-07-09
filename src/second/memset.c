#include <stdio.h>
#include <string.h>

int main (){
	char str[] = "learn how to initiate a string";
	memset(str,'\0',6);
	char *pos = str + 5;
	// Write a string, followed by a newline, to stdout.
	puts(pos);// 无输出,因为刚开始就遇到字符串结束符号了 '\0'
	pos = str + 6;
	// Write a string, followed by a newline, to stdout.
	puts(pos);// 有输出
	return 0;
}


