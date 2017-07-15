#include <stdio.h>

#define TSIZE 45

typedef struct film {
    char title[TSIZE];
    int rating;
} Item;

int main (int argc, char **argv){
    Item film = {
        .title = "master algorithm with C",
        // 豆瓣评分
        .rating = 90
    };

    printf("one{\n\"title\":%s,\n\"rating\":%d\n}\n",film.title,film.rating);
    return 0;
}

