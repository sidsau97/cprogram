#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "Num.h"
/**
 * arv[要统计的点的个数,距离]
 * @return 0 if it runs normally , 1 or not.
 */
int main (int argc, char *argv[]) {
	int i,j,count = 0;
    int N = atoi(argv[1]);// 要计算的点数
    float d = atof(argv[2]);//distance
    // 用一个以为数组去容纳所有点
    point *a = malloc(N*sizeof(*a));
    // 内存是否分配成功检查,这是良好的编程习惯
    if(a == NULL){
    	printf("Insufficient memory.\n");
    	return 1;
    }
    // 初始化
    for(i = 0; i < N; i++){
    	a[i].x = randNum();
    	a[i].y = randNum();
    }
    // 循环比较距离
    for( i = 0; i < N; i++ ){
    	// 避免重复计算点(只需要和后边的进行比较就可以了,内部循环的目的与插入排序不同,要区分)
    	for( j = i+1; j < N; j++ ){
    		printf("%f ",distance(a[i],a[j]));
    		if(distance(a[i],a[j]) < d){
    			count ++;
    		}
    	}
    }
    printf("%d edges shorter than %f\n", count, d);
	return 0;
}
