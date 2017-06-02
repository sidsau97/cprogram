#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"

int main (){
    sqlist *list = NULL; // 空指针
    datatype arr[] = {12,23,34,35,56};
    int i, err;
    /*
     * 如果采用二级指针的话,参数位置为:
     * sqlist_create1(&list);
     */
    list = sqlist_create();

    if(list == NULL){
    	//fixed: error: expected ‘;’ before ‘}’ token 之前却少分号
    	//
    	fprintf(stderr,"sqlist_create() failed!\n");
    }
    for(i = 0; i <sizeof(arr)/sizeof(*arr); i++){
        /*
         *  插入一个元素,然后通过遍历查看列表的当前状态
         *  &arr[i] @todo 这里不理解
         *  **note:** 这里注意运算符优先级
         *
         */
        if((err = sqlist_insert(list, 0, &arr[i])) != 0){
        	if(err == -1){
        		fprintf(stderr, "The array is full.\n");
        	}else if(err == -2){
        		fprintf(stderr,"The position you what to insert is not correct!\n");
        	}else{
        		fprintf(stderr,"Error!\n");
        	}
        }
    }

    sqlist_display(list);

//    sqlist_destory(list);

	exit(0);
}
