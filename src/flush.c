#include <stdio.h>
int main() {
	char buf[5];
	while (fgets (buf, sizeof(buf), stdin)){
		if(*buf == '\n'){
			break;
		}else{
			printf("ok");
		}
	}
	return 0;
}
