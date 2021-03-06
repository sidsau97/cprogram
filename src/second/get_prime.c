#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	int *a = malloc(N * sizeof(int));
	if (a == NULL) {
		printf("Insufficient memory.\n");
		return 1;
	}

	/**
	 * In mathematics, the sieve of Eratosthenes is a simple, ancient algorithm for finding all prime numbers up to any given limit.
	 * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
	 *
	 * (1) Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
	 * (2) Initially, let p equal 2, the smallest prime number.
	 * Enumerate the multiples of p by counting to n from 2p in increments of p, and mark them in the list (these will be 2p, 3p, 4p, ...;
	 * the p itself should not be marked
	 */

	/**
	 * 埃拉托色尼筛选法
	 * sieve of Eratosthenes  get primes lower than N
	 */
	int i, j;

	/*
	 * 假定所有数都是素数,用1标记
	 */
	for (i = 2; i < N; i++) {
		a[i] = 1;
	}

	for (i = 2; i < N; i++) {
		// 找到第一个未被标记的数
		if (a[i]) {
			// 至少从　i＊i 开始
			for (j = i; i * j < N; j++) {
				if (a[i * j]) {
					a[i * j] = 0;
				}
			}
		}
	}

	for (i = 2; i < N; i++) {
		if (a[i]) {
			printf(" %4d", i);
		}
	}
	printf("\n");
	return 0;
}
