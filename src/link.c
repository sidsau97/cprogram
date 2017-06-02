#include <stdio.h>
#include <stdlib.h>
typedef struct node *link;
struct node {
	int item;
	/*
	 * bug: link *next; link 已经是指针了,不用加 * 了
	 */
	link next;
};

/*
 * 约瑟夫问题,自己动手实践 2017-04-15
 * return -1 means null
 */
int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int i, j;
	link a = malloc(sizeof *a);
	if (a == NULL) {
		return -1;
	}
	a->item = 1;
	a->next = a;
	link t = a;
//循环链表

/* 初始化N用于构建
 * initiate
 */
	for (i = 2; i <= N; i++) {
		a = (a->next = malloc(sizeof(*a)));
		if (a == NULL)
			return -1;
		a->item = i;
		a->next = t;
	}
	/*
	 * bug : i = i++  这使得i的结果始终未1
	 * 严重逻辑错误,编程翻译不对
	 */
//	for (i = 1; i <= N; i++) {
//		a = a->next;
//		for (j = 1; j < M; j++)
//			break;
//		t = a->next;
//		a->next = t->next;
//		free(t);
//		N--;
//	}

	while (a != a->next){
		for(i = 1; i < M; i++)
			a = a->next;
		t = a->next;
		a->next = t ->next;
		printf("%d\n", t->item);
		free(t);
		N--;
	}
	printf("%d\n", a->item);
	return 0;
}
