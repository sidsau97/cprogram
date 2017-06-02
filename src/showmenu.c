#include <stdio.h>
#include <ctype.h>
#include <string.h>

#ifdef DEBUG
#   define LOG_MSG printf
#else
#   define LOG_MSG(...)
#endif

void eatline(){
    while(getchar() != '\n')
        continue;
}

int main (){
    char ans;
    puts("Enter menu choice:");
    puts("u) uppercase l) lowercase");
    puts("t) transposed case o) original case");
    puts("n) next string");
    ans = getchar();
    ans = tolower(ans);
    eatline();
    while(strchr("ulton",ans) == NULL){
        puts("please enter u l t o or n");
        // bug: tolower(ans) will always be the same, so the while loop could never stopped if so,
        // just deal with the input char
        ans = tolower(getchar());
        eatline();
    }
    LOG_MSG("%c\n",ans);
    return ans;
}
