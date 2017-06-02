#include "Item.h"

void QUEUEinit ( int );

/*
 * check if the queue is empty
 */
int QUEUEempty ();

/*
 * put a new item to queue`
 */
void QUEUEput (Item);
/*
 * remove a member from queue,
 * and return the removed member
 */
Item QUEUEget ();
