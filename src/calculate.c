#include <stdio.h>
#include <string.h>
#include "STACK.h"
int main(int argc, char *argv[]) {
	/**
	 * "1 2 3 + 4 5 * * +"
	 * 测试用例在终端输入的时候,一定要用引号扩起来,避免出问题
	 */
	char *a = argv[1];
	int i;
	int N = strlen(a);
	int temp;
	STACKinit(N);
	for (i = 0; i < N; i++) {
		if (a[i] == '+') {
			STACKpush(STACKpop() + STACKpop());
		}
		if (a[i] == '*') {
			STACKpush(STACKpop() * STACKpop());
		}
		if ((a[i] >= '0') && (a[i] <= '9')) {
			STACKpush(0);
		}
		while ((a[i] >= '0') && (a[i] <= '9')) {
			STACKpush(10 * STACKpop() + (a[i++] - '0'));
		}
	}
	printf("%d \n", STACKpop());

}
