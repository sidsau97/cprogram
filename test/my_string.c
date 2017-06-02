int test_my_strlen() {
	char *a = stdin_read();
	/*
	 * 终端输入比较特殊,对多输入一个文件结束符号,因此,其长度比看起来的要大1,
	 * 这里-1表示去除文件结束符号后的长度
	 */
	int length = my_strlen(a) - 1;
	printf("string length:%d\n", length);
	return 0;
}

void test_my_strpos() {
	char a[] = "I live in Peking";
	char b[] = "in";
	int pos = my_strpos(a, b);
	assert(pos == 7);
}


void test_my_strcpy() {
	char a[] = "I live in Peking";
	char b[] = "in";
	my_strcpy(a, b);
	int length = my_strlen(a);
	int i = 0;
	for (; i < 2; i++) {
		assert(a[i] == b[i]);
	}
}

void test_my_strncmp() {
	char a[] = "I live in Peking";
	char b[] = "in";
	int less = my_strncmp(a, b);
	assert(less < 0);
}

void test_bk_strncmp() {
	char a[] = "I live in Peking";
	char b[] = "in";
	int less = bk_strncmp(a, b);
	assert(less < 0);
}

void test_bk_strcat(){
	char a[] = "I live in Peking";
	char b[] = "in";
	bk_strcat(a,b);
	// @todo 比较函数貌似没有达到预期,明天进一步测试
	assert(my_strncmp("I live in Pekingin",a) == 0);
}






