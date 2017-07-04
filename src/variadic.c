#include <stdio.h>
#include <math.h>
// '#' is not followed by a macro parameter
// 原因未X 写成了小写 x
#define PR(X, ...) printf("Message " #X ": " __VA_ARGS__) /*注意书上直接粘贴过来有错误*/
int main()
{
    double x = 48;
    double y;
    y = sqrt(x);
    PR(1, "x = %g\n", x);
    PR(2, "x = %.2f, y = %.4f\n", x, y);
    return 0;
}
