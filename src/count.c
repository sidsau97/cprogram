#include <stdio.h>
// exit()  need this header file
#include<stdlib.h>

int main (int argc, char ** argv){
    FILE *fp;
    char ch;
    int count = 0;
    if(argc != 2){
        // argv[0] is the running file name
        printf("Usage: %s filename\n",argv[0]);
        exit(1);
    }
    // read from argv[1], send to the stdout char by char
    if((fp = fopen(argv[1],"r")) != NULL){
        printf("can not open %s \n",argv[1]);
        exit(1);
    }
      
    while ( (ch = getc(fp)) != EOF ){
            putc(ch,stdout);
            count++;
    }

    fclose(fp);
}


