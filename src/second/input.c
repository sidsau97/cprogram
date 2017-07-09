#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int main()
{
	// c 语言中二者是相等的
	assert('\0' == 0);
    int num, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &num);

    ptr = (int*) malloc(num * sizeof(int));  //memory allocated using malloc
    if(ptr == NULL)
    {
        printf("Error! memory not allocated.");
        exit(EXIT_FAILURE);
    }

    printf("Enter elements of array: ");

    for(i = 0; i < num; ++i)
    {
        /* scanf 不会对扫描的人大小进行控制,
         * 可能导致内存覆盖问题,使用的时候要注意
         */
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }

    printf("Sum = %d\n", sum);
    // free 一个指针代表的内存块的大小
    free(ptr);
    return 0;
}
