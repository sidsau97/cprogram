#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifndef EPSILON
#define EPSILON 0.01
#endif

// error: expected ‘)’ before ‘;’ token
// do not use ; for define ,it is just macro for preprocessor, not for c compiler
typedef struct {
	double x;
	double y;
} rect;

double distance(rect a, rect b) {
	// a->x is use only if a is a pointer that point to rect
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

int main() {
	rect a = { 3.0, 6.0 };
    rect b = { 2.5, -0.7};
    //called object ‘distance’ is not a function or function pointer
    // the name of variable could not be the same with function
    double dist = distance(a,b);
    //[](http://blog.csdn.net/jk110333/article/details/8902707)
    assert( dist - 6.71 < EPSILON );
    printf("the distance between a and b is:%f\n",dist);
}
