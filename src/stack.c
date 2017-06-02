#include <stdlib.h>
typedef struct STACKnode* link;

/*
 * a stack implement by single linked list
 */
struct STACKnode {
	int item;
	link next;
};

/*
 * head is the start position of a stack
 * it is also the last inserted member
 */
static link head;

/**
 * allocate memory for a new link ,
 * set item as its value and
 * set its next as a given link
 */
link NEW(int item, link next) {
	link x = malloc(sizeof *x);
	x->item = item;
	x->next = next;
	return x;
}

/**
 * set link head to be NULL
 */
void STACKinit(int maxN) {
	head = NULL;
}

/*
 * check if head equal to NULL to indicate whether the stack is empty or not
 */
int STACKempty() {
	return head == NULL;
}

/*
 * insert a new item to the stack
 * <b>note</b> keep the head as the last inserted item
 */
void STACKpush(int item) {
	head = NEW(item, head);
}

/**
 * record the item of head, it will be return value.
 * record the position of head->next ,delete head from the link list
 * by free(head)
 * and point head to the previous record position of head->next
 * and  return the item of head
 */
int STACKpop() {
	int item = head->item;
	link t = head->next;
	free(head);
	head = t;
	return item;
}
