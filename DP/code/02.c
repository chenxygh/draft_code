#include <stdio.h>

#define INT_MIN -2147483648

int max (int a, int b) {
	return a > b? a: b;
}

// simple recursion
// top-down
int CUT_ROD_1 (int *p, int n) {
	if (n == 0) return 0;
	int q = INT_MIN;
	for (int i = 1; i <= n; ++i) {
		q = max (q, p[i] + CUT_ROD_1 (p, n - i));
	}
	return q;
}

// top-down with memoization
int CUT_ROD_2 (int *p, int n, int *r) {
	if (n == 0) return r[n] = 0;
	if (r[n] >= 0) return r[n];

	int q = INT_MIN;
	for (int i = 1; i <= n; ++i) {
		q = max (q, p[i] + CUT_ROD_1 (p, n - i));
	}
	return r[n] = q;
}

// bottom-up with memoization
int CUT_ROD_3 (int *p, int n, int *r) {
	r[0] = 0;
	for (int i = 1; i <= n; ++i) {
		int q = INT_MIN;
		for (int j = 1; j <= i; ++j) {
			q = max (q, p[j] + r[i - j]);
		}
		r[i] = q;
	}
	return r[n];
}

// bottom-up with memoization and get solution
int CUT_ROD_4 (int *p, int n, int *r, int *s) {
	r[0] = 0;
	for (int i = 1; i <= n; ++i) {
		int q = INT_MIN;
		for (int j = 1; j <= i; ++j) {
			if (p[j] + r[i - j] > q) {
				q = p[j] + r[i - j];
				s[i] = j;
			}
		}
		r[i] = q;
	}
	return r[n];
}

void printSolution (int n, int *s) {
	while (n > 0) {
		printf("%d ", s[n]);
		n -= s[n];
	}
}

// f(n) = max (p[i] + f(n - i))

int main(int argc, char const *argv[])
{
	int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30}, pSize = 11;
	int s[11], r[11];
	for (int i = 0; i < pSize; ++i) r[i] = -1;

	CUT_ROD_4 (p, pSize - 1, r, s);
	printSolution (7, s);

	return 0;
}
