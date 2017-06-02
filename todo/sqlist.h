#ifndef SQLIST_H
#define SQLIST_H

#define DATASIZE 1024
typedef int datatype;

typedef struct node_st{
	//存放数据的数组
	datatype data[DATASIZE];
	//标识成员在线性表中位置的数
	int last;
} sqlist; // 结构体 typedef 的使用

sqlist *sqlist_create ();

void sqlist_create1 (sqlist **);

/*
 * 线性链表不允许在尾部插入
 */
int sqlist_insert(sqlist *,int i, datatype *);

int sqlist_delete(sqlist *,int i);

int sqlist_find (sqlist *, datatype *);

int sqlist_isempty(sqlist *);

int sqlist_setempty(sqlist *);

int sqlist_getnum(sqlist *);

void sqlist_destory (sqlist);

void sqlist_union (sqlist *, sqlist *);

/*
 * travel
 */
void sqlist_display(sqlist *);

/*
 * fixed : unterminated #ifndef
 */
#endif



