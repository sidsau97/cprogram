#include <stdio.h>
void eatline(){
    char disp;
    while((disp = getchar()) != '\n'){
        printf("%c:%d\n",disp,disp);
        continue;
    }
}

int main (){
    eatline();
}
