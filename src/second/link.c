#include <stdio.h>
#include <stdlib.h>

// 未约瑟夫为题设计的双向链表,很方便的维护者头和尾
typedef struct node {
	int item;
	struct node * next;
}*cycleSingleLink;

/*
 * 约瑟夫问题,自己动手实践 2017-04-15
 * return -1 means null
 */
int main(int argc, char *argv[]) {
	if (argc < 3) {
		puts("enter two number\n");
		exit(EXIT_FAILURE);
	}
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int i;
	// 当只有一个元素是,最后一个元素就是第一个元素
	cycleSingleLink tail = malloc(sizeof(*tail));
	if (tail == NULL) {
		return -1;
	}
	tail->item = 1;
	tail->next = tail;
	// 用于标记第一个元素的位置
	cycleSingleLink head = tail;
//循环链表

	/* 初始化N用于构建
	 * initiate
	 */
	for (i = 2; i <= N; i++) {
		tail->next = malloc(sizeof(*tail));
		tail = tail->next;
		if (tail == NULL)
			return -1;
		tail->item = i;
		tail->next = head;
	}
	// 从尾部开始方位,刚好接下来跳到开始部分遍历
	cycleSingleLink visitor = tail;
	cycleSingleLink delete = NULL;
	while (visitor != visitor->next) {
		for (i = 1; i < M; i++)
			visitor = visitor->next;
		// 内层循环结束后,刚好跳到了要删除元素的前一个位置
		delete = visitor->next;
		visitor->next = delete->next;
		printf("%d\n", delete->item);
		free(delete);
	}
	printf("the find surviver is %d\n", visitor->item);
	free(visitor);
	// 养成习惯,避免野指针
	head = NULL;
	tail = NULL;
	visitor = NULL;
	delete = NULL;
	// 进过重置野指针后, 下面代码会显示 Segmentation fault (core dumped),从而避免了野指针
//	printf("the find surviver is %d\n", tail->item);
	return 0;
}
