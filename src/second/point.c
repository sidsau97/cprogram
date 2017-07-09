#include "Point.h"
#include <math.h>
/*
 * 点距离计算公式 distance = sqrt((x1-x2)^2 + (y1-y2)^2)
 * math.h 编译需要加 -lm 编译条件
 */
float distance (point a, point b){
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}
