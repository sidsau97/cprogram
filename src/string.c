#include <assert.h>
#include <stdio.h>
#include "my_stdio.h"
#include "my_string.h"
#include "../test/my_string.c"
int main(int argc, char *argv[]) {
	test_bk_strcat();
	test_bk_strncmp();
	test_my_strncmp();
	test_my_strpos();
	test_my_strcpy();
	printf("\n");
	return 0;
}
