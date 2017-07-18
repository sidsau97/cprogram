//a stack implement by single linked list
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
/**
 * 二级指针智能修改一级指针值存在的情况下指针的内容而不许要返回值(也就是引用修改值)
 * 因此, STACKinit 初始化需要需要返回值
 *
 * @TODO 验证一下 php 中输入"汉字", argv 与 c 语言中的表现是否相同
 */
int main(int argc, char **argv) {
	STACK *books;
	books = STACKinit();
	STACKpush(books, "master algorithom with c");
	STACKpush(books, "c primer: 5th Edition");
	// argc 比实际输入的项目多一个
	for (int i = 1; i < argc; i++) {
		STACKpush(books, argv[i]);
	}
	STACKprinter(books, STACKnodePrinter);

	/**
	 * 注意 printf 打印变量是自右向左的,因此下面语句要分开执行
	 */
	printf("the name of remove book is:%s\n", STACKpop(books));
	printf("there are %d books left\n", books->count);
	printf("the name of remove book is:%s\n", STACKpop(books));
	printf("there are %d books left\n", books->count);
//	assert(NULL == STACKpop(books));
	return 0;
}

