#include <stdio.h>
/* the prototype of exit()*/
#include<stdlib.h>

/**
 * return -1 on failure or the total counts of the words of the files
 * **note** the count total characters include the one occupied by EOF
 */
int wordsCount(char * filename);
int wordsCount(char * filename) {
	FILE *fp;
	char ch;
	int count = 0;
	if (NULL == (fp = fopen(filename, "r"))) {
		return -1;
	}
	// read from argv[1], send to the stdout char by char
	// FILE *fopen(const char *path, const char *mode);
	// read lines byte by byte, for ACSII words, one character occupies one bite, for utf8 word, one chinese
	// character occupies three bytes,so  print a chinese words byte by bite will result in messy code
	//[utf8 字节处理原理](http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html)
	while (EOF != (ch = getc(fp))) {
//      puts() writes the string s and a trailing newline to stdout.
//		putc(ch,stdout);
//		printf("%c\n",ch);
		count++;
	}
	fclose(fp);
	return count;
}

int main(int argc, char ** argv) {
	int count = 0;
	if (argc != 2) {
		// argv[0] is the running file name
		printf("Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (-1 == (count = wordsCount(argv[1]))) {
		printf("can not open %s \n", argv[1]);
		exit(EXIT_FAILURE);
	} else {
		printf("there are %d characters in file: %s\n", count, argv[1]);
	}
}

