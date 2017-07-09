#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 1000
#define MMAx 1000

void printStrings (char **arr, int count);

// 这个比较方案区别大小写
int compare (const void *a, const void *b){
    return strcmp(*(char **)a, *(char **)b);
}


int main (int argc, char **argv){
    char buff[NMAX];
    // 这个是关键
    char *a[NMAX];
    int i = 0, j = 0;
    for(;i < NMAX; i++){
        // a 为二维数组
        a[i] = &buff[j];
        // format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘char **’
        // 数组本身就是引用类型
        // 循环中止条件: (思路要清晰)
        if(scanf("%s",a[i]) == EOF){
             break;
        }
        // 这里之前写的有问题,字符串的长度要累加,(之前死路不清晰)
        j += strlen(a[i]) + 1;
    }
    printf("strings before sort!\n");
    printStrings(a , i);
    // void qsort(void *base, size_t nmemb, size_t size,int (*compar)(const void *, const void *));
    // 理解第三个参数的含义
    qsort (a, i, sizeof(char *), compare);
    printf("strings after quick sorted!\n");
    printStrings(a , i);
    return 0;
}

void printStrings(char **arr, int count){
    int i = 0;
    for( ;i < count; i++){
        printf("%s\n",arr[i]);
    }
}

