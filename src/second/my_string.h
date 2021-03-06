int my_strlen(char *a) {
	int i;
	/**
	 * 该 for 循环没有循环体,一定要在循环结束后,加上引号
	 * 字符串以0未结束符号
	 */
	for (i = 0; a[i] != 0; i++);
	return i;
}

/*
 * copies the string pointed to, by src to dest.
 *
 */
char my_strcpy(char *dest, char *src){
	for(int i = 0;(dest[i] = src[i]) != 0;i++);
	return dest;
}

/*
 * 标准c库里边不存在这个函数
 * 类似 php 版本的 strpos
 */
int my_strpos(char *haystack, char *needle) {
	int i, j;
	for (i = 0; haystack[i] != 0; i++) {
		for (j = 0; needle[j] != 0; j++) {
			if (haystack[i + j] != needle[j]) break;
		}
		if (needle[j] == 0) return i;
	}
	return -1;
}

/*
 * prefix comparison
 * bug:
 *  warning: type of ‘a’ defaults to ‘int’
 *  fixed: add parameter type
 */
int my_strncmp(char *a, char *b){
	int length = my_strlen(a);
	int i;
	for(i = 0; i < length; i++){
		if(a[i] != b[i]) return a[i] - b[i];
	}
	return 0;
}

/*
 * bk means book
 */
int bk_strncmp(char *a, char *b){
	int length = my_strlen(a);
	int i;
	for(i = 0; a[i] == b[i] && i < length ;i++);
	if(a[i] == 0) return 0;
	return a[i] - b[i];
}

/*
 * 字符串连接,在字符串a后面连接b
 */
int bk_strcat(char *a, char *b){
	 my_strcpy(a + my_strlen(a), b);
}


