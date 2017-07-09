/* films3.c -- using an ADT-style linked list */
/* compile with list.c
 * TODO could the head file be include automatically ?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* prototype for exit() */
#include "newList.h"

/* defines List, Item
*/
void showmovies(Item item);

int main(void)
{
    List movies;
    // 结构体
    Item temp;

    InitializeList(&movies);

    if (ListIsFull(&movies))
    {
        fprintf(stderr,"No memory available! Bye!\n");
        exit(EXIT_FAILURE);
    }

    /* gather and store */
    puts("Enter first movie title:");

    // 如果输入空行,则结束输入
    while ((NULL != fgets(temp.title,sizeof(temp.title),stdin)) && (0 != strcmp(temp.title,"\n")))
    {
       // make the input as regular string:
       // lvalue required as left operand of assignment
       // 用 ==
       if('\n' == temp.title[strlen(temp.title) - 1]){
           temp.title[strlen(temp.title) -1] = '\0';
       }else{
           fprintf(stderr,"error when trying to accept input");
           exit(EXIT_FAILURE);
       }
        // use EOF to end user input while loop, for f gets does not trim the tailing \n
        // fprintf(stdout,"the first letter is %d",temp.title[0]);

        // 不行,这个程序到目前为止有逻辑上的错误,TODO take a rest, and think what to do;
        puts("Enter your rating <0-10>:");
        scanf("%d", &(temp.rating));
        // 这行的作用是将换行符号作为一次循环的的跳出条件,避免后续内存分配问题
        // getchar() is equivalent to getc(stdin)
        while(getchar() != '\n')
            continue;
        //printf("print 打法,debug");
        if (AddItem(temp, &movies) == 0)
        {
            fprintf(stderr,"Problem allocating memory\n");
            break;
        }

        if (ListIsFull(&movies))
        {
            puts("The list is now full.");
            exit(EXIT_FAILURE);
        }
        puts("Enter next movie title (empty line to stop):");
    }

    /*  display */
    if (ListIsEmpty(&movies)){
        printf("No data entered. ");
    }// if not empty
    else
    {
        printf ("Here is the movie list:\n");
        Traverse(&movies, showmovies);
    }
    exit(EXIT_FAILURE);
    printf("You entered %d movies.\n", ListItemCount(&movies));
    /* clean up */
    EmptyTheList(&movies);
    printf("Bye!\n");
    return 0;
}


void showmovies(Item item)
{
    printf("Movie: %s Rating: %d\n", item.title, item.rating);
}




