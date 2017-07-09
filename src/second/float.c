#include <stdlib.h>
#include "Num.h"
#include <time.h>
/*
 * 要产生真正的随机数是比较难的,利用这个函数可以产生一个简单的随机数,每秒种变化一次
 * 2017-04-04
 */
Number randNum() {
// 返回0~1 之间的浮点数
//	srand(time(0));
	return 1.0 * rand() / RAND_MAX;
}
