#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler()
{
	printf("hello\n");
}

int main(int argc, char ** argv) {
	int i;
	signal(SIGALRM, handler);
	alarm(5);
	for (i = 1; i < 7; i++)
			{
		printf("sleep %d ...\n", i);
		sleep(1);
	}
	return 0;
}

/*
 *sleep 1 ...
 sleep 2 ...
 sleep 3 ...
 sleep 4 ...
 sleep 5 ...
 hello
 sleep 6 ...
 */
