// func_ptr.c -- uses function pointers

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 1
//expected expression before ‘...’ token
// could not contain any white space between LOG_MSG and (...)
#ifdef DEBUG
#    define LOG_MSG printf
#else
#	define LOG_MSG(...)
#endif


char showmenu(void);
void eatline(void); // read through end of line
void show(void (*fp)(char *), char * str);
void ToUpper(char *); // convert string to uppercase
void ToLower(char *); // convert string to uppercase
void Transpose(char *); // transpose cases
void Dummy(char *); // leave string unaltered
int main(void) {
	char line[81];
	char copy[81];
	char choice;
	void (*pfun)(char *); // points a function having a
// char * argument and no
// return value
//	The reason for the removal of gets() is quite well known:
//	It can't protect against the buffer overrun.
//	As such, you should never use gets() and use fgets() instead and
//	take care of the trailing newline, if any.
	puts("Enter a string (empty line to quit):");
// @todo bug fix later
	while (fgets(line, sizeof(line), stdin)) {
		// if the first input char is '\n'
		if (*line == '\n')
			break;
//		line[strcspn(line,"\n")] = '\0';

		LOG_MSG("line is: %s\n", line);
		while ((choice = showmenu()) != 'n') {
			switch (choice) // switch sets pointer
			{
			case 'u':
				pfun = ToUpper;
				break;
			case 'l':
				pfun = ToLower;
				break;
			case 't':
				pfun = Transpose;
				break;
			case 'o':
				pfun = Dummy;
				break;
			}
			strcpy(copy, line); // make copy for show()
			show(pfun, copy); // use selected function
		}
		puts("Enter a string (empty line to quit):");
	}
	puts("Bye!");
	return 0;
}

char showmenu(void) {
	char ans;
	puts("Enter menu choice:");
	puts("u) uppercase l) lowercase");
	puts("t) transposed case o) original case");
	puts("n) next string");
	ans = getchar(); // get response
	ans = tolower(ans); // convert to lowercase
	eatline(); // dispose of rest of line
	while (strchr("ulton", ans) == NULL) {
		puts("Please enter a u, l, t, o, or n:");
		ans = tolower(getchar());
		eatline();
	}
	return ans;
}

void eatline(void) {
	while (getchar() != '\n')
		continue;
}

void ToUpper(char *str) {
	while (*str) {
		// Return the upper case version of C
		*str = toupper(*str);
		str++;
	}
}

void ToLower(char *str) {
	while (*str) {
		*str = tolower(*str);
		str++;
	}
}

void Transpose(char *str) {
	//		ulti-character character constant
//	LOG_MSG('%c',*str);
	LOG_MSG("first letter is:%c ",*str);
	while (*str) {
		if (isupper(*str))
			*str = tolower(*str);
		else if (islower(*str))
			*str = toupper(*str);
		str++;
	}
}

void Dummy(char * str) {
// leaves string unchanged
}

void show(void (*fp)(char *), char * str) {
	(*fp)(str); // apply chosen function to str
	puts(str); // display result
}