#include <stdio.h>

void getNext (char *t, int *next) {
	int i = 1, j = next[1] = 0;
	while (i < t[0]) {
		if (j == 0 || t[i] == t[j]) {
			++i;
			++j;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
}

int KMP (char *s, char *t, int *next) {
	int i = 1, j = 1;
	while (i <= s[0] && j <= t[0]) {
		if (j == 0 || s[i] == t[j]) {
			++i;
			++j;
		} else {
			j = next[j];
		}
	}
	return j > t[0]? i - t[0]: 0;
}

int main(int argc, char const *argv[])
{
	char s[] = {10, 'a', 'a', 'a', 'b', 'a', 'c', 'b', 'a', 'b', 'c', '\0'};
	char t[] = {3, 'a', 'b', 'c', '\0'};
	int next[4];
	getNext (t, next);
	printf("%d\n", KMP (s, t, next));

	return 0;
}
