#include <stdio.h>
#include <stdlib.h>
#include "Num.h"
int main(int argc, char *argv[])
  { int i, N = atoi(argv[1]);
    float m1 = 0.0;
    Number x;
    for (i = 0; i < N; i++)
      {
        x = randNum();
        m1 += ((float) x)/N;
      }
    printf("       Average: %f\n", m1);
    return 0;
 }
