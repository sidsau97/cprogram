#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"
/**
 * 顺序存储的线性链表
 */
sqlist *sqlist_create() {
	sqlist *me;
	me = malloc(sizeof(*me));
	if (me == NULL)
		return NULL;
//  初始化未-1,表示里边没有内容
	me->last = -1;
	return me;
}

/*
 * 当需要多个返回结果时,二级指针比较好用
 * 通过二级指针传参数
 */
void sqlist_create1(sqlist **ptr) {
	*ptr = malloc(sizeof(**ptr));
	if (*ptr == NULL)
		return;
	//  初始化未-1,表示里边没有内容
	(*ptr)->last = -1;
	return;
}

/*
 * 在指定节点后插入心结点
 */
int sqlist_insert(sqlist *me, int i, datatype *data) {
	int j;
	// 如果已经存满了,m 不允许再存了
	if (me->last == DATASIZE - 1)
		return -1;
//  如果超出了最大值所在下标加1的位置
	if (i < 0 || i > me->last + 1)
		return 2;
//    将i以后的元素顺次往后移动
//    core dump if j++
	for (j = me->last; i <= j; j--) {
		/*
		 * bug: me[j + 1] = me->data[j];
		 * description: incompatible types when assigning to type ‘sqlist {aka struct node_st}’ from type ‘datatype {aka int}’
		 */
		me->data[j + 1] = me->data[j];
	}
	// 复杂数据类型这里可能不能成功赋值
	me->data[i] = *data;
	me->last++;
	return 0;
}

//int sqlist_delete(sqlist *me, int i) {
//
//}
//
//int sqlist_find(sqlist *me, datatype *data) {
//
//}
//
//int sqlist_isempty(sqlist *me) {
//
//}

//int sqlist_setempty(sqlist *me) {
//
//}

void sqlist_display(sqlist *me) {
	int i;
// 边界检查
	if (me->last == -1)
		return;
	for (i = 0; i <= me->last; i++) {
		printf("%d ", me->data[i]);
	}
	printf("\n");
	return;
}

//int sqlist_getnum(sqlist *me) {
//
//}

