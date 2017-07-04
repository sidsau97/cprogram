#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/**
 * @param char delimiter
 * @return return a array of strings
 */
char** explode(char delimiter, char* str) {
	int l = strlen(str), i=0, j=0, k=0;
	char x ;
	char** r = (char**)realloc(r, sizeof(char**));
	r[0] = (char*)malloc(l*sizeof(char));
	while ( i< l+1 ) {
		x = str[i++];
		if (x==delimiter || x=='\0') {
			r[j][k] = '\0';
			r[j] = (char*)realloc(r[j], k*sizeof(char));
			k = 0;
			r = (char**)realloc(r, (++j+1)*sizeof(char**));
			r[j] = (char*)malloc(l*sizeof(char));
		} else {
			r[j][k++] = x;
		}
	}
	return r;
}



int main (){
	char str[] = "hello world";
    int length = strlen(str);
	char ** r =  (char **)realloc(r,sizeof(char **));
	printf("the address of the realloc char** r is: %p\n",r);
	printf("the length of str is:%d\n",length);
	// put constant number lest the operand assignment will help to find the mistake  which use "="  as "=="lvalue required as left operand of assignment
	assert(11 == length);

}
