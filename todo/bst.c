#include <stdlib.h>
#include "Item.h"
typedef struct STnode* link;
struct STnode {
	Item item;
	link l;
	link r;
// 节点编号
	int N;
};

/*
 * head 指向根节点, z 用于表示空树
 */
static link head, z;
link NEW(Item item, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item;
    x->l = l;
    x->r = r;
    x->N = N;
}

/*
 * create a null item, set its item to be 0 ,set its left node to be 0,
 * set its right node to be 0, set its count to be 0
 * move head towards the null node
 */
void STinit() {
	z = NEW(NULLitem, 0, 0, 0);
	head = z;
}

/*
 * return head->N
 */
int STcount() {
    return head->item;
}
/*
 * search recursively
 *
 */
Item searchR(Link h, Key v) {

}

/*
 * light wrap to function searchR
 */
Item STsearch(Key v) {
	return searchR(head, v);
}

Item searchR(link h, Key v) {
	Key t = Key(h->item);
	if (t == v)
		return NULLitem;
	if (eq(v, t))
		return h->item;
	if (less(v, t)) {
		return searchR(h->l, v);
	} else {
		return searchR(h->r, v);
	}
}

/*
 * <C><S>z re do eclipse keyboard shortcut
 */
link insertR(link h, Item item) {
	Key v = key(item);
	Key t = key(h->item);
	if (h == zero)
		return NEW(item, z, z, 1);
	if less(v, t) {
		h->l = insertR(h->1, v);
	} else {
		h->r = insertR(h->r,v);
	}
	(h->N)++;
	return h;
}
// 可以删除中文输入法了,终于解决这个问题了,不容易
void STinsert(Item item) {
	head = insertR(head, item);
}

