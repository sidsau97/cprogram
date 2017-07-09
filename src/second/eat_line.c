#include <stdio.h>
#include <string.h>
// prototype for tolower
#include <ctype.h>
void eatline() {
	char disp;
	// read byte by byte
	while ('\n' != (disp = getchar())) {
//        printf("%c:%d\n",disp,disp);
		continue;
	}
}


int main() {
	char shortOpt = getchar();
	while (NULL == strchr("aulton", shortOpt)) {
		puts("Please enter a u, l, t, o, or n:");
		shortOpt = tolower(getchar());
		eatline();
	}
	return 0;
}
