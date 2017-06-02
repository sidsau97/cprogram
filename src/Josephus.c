#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]) {
	int i;
	// 总数
	int N = atoi(argv[1]);
	// 跳跃间隔
	int M = atoi(argv[2]);
	/**
	 * 初始化闲余链表
	 */
	initNodes(N + 1);
	link t, x;
	for (i = 2, x = newNode(1); i <= N; i++) {
		t = newNode(i);
		insertNext(t, x);
		x = t;
	}
/*
 * 对循环链表,
 * x == Next(x) 表明只剩下最后一个元素了
 */
	while (x != Next(x)) {
		for (i = 1; i < M; i++)
			x = Next(x);
		/**
		 * deleteNext 将x的下一个元素从链表种删除,并返回刚才删除的这个元素
		 * freeNode 将刚才删除的这个元素有添加会闲余链表 freelist 的头部
		 */
		freeNode(deleteNext(x));
	}
	printf("%d\n",x->item);
}
