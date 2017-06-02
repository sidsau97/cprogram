/**
 * initiate a stack
 */
void STACKinit(int);
/*
 * if head element equals to NULL,
 * then the stack is empty
 */
int STACKempty(void);
/**
 * allocate memory of size of link
 * and set item property as the given parameter integer
 * then move pointer header to the created and initiated node
 */
void STACKpush(int);

/**
 * record the item of head, it will be return value.
 * record the position of head->next ,delete head from the link list
 * by free(head)
 * and point head to the previous record position of head->next
 * and  return the item of head
 */
int STACKpop();
