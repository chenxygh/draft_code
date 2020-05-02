#include <stdio.h>

int max (int a, int b) {
	return a > b? a: b;
}

// top-down
int pack (int *weight, int *value, int n, int capacity) {
	if (n <= 0 || capacity <= 0) return 0;
	return max (pack (weight, value, n - 1, capacity), capacity >= weight[n - 1]? value[n - 1] + pack (weight, value, n - 1, capacity - weight[n - 1]): 0);
}

// iteration with two one-dimensiom arrays
// int pack (int *weight, int *value, int n, int capacity) {
// 	int a[capacity + 1] = {0}, b[capacity + 1] = {0}, *res = a, *preResult = b;
// 	for (int i = 0; i <= capacity; ++i) {
// 		res[i] = i < weight[0]? 0: value[0];
// 	}
// 	for (int i = 1; i < n - 1; ++i) {
// 		int *temp = res;
// 		res = preResult;
// 		preResult = temp;
// 		for (int j = capacity; j >= weight[i]; --j) {
// 			res[j] = max (preResult[j], preResult[j - weight[i]] + value[i]);
// 		}
// 	}
// 	return max (res[capacity], res[capacity - weight[n - 1]] + value[n - 1]);
// }

// iteration with one one-dimensiom array
// int pack (int *weight, int *value, int n, int capacity) {
// 	int res[capacity + 1] = {0};
// 	for (int i = 0; i <= capacity; ++i) {
// 		res[i] = i < weight[0]? 0: value[0];
// 	}
// 	for (int i = 1; i < n - 1; ++i) {
// 		for (int j = capacity; j >= weight[i]; --j) {
// 			res[j] = max (res[j], res[j - weight[i]] + value[i]);
// 		}
// 	}
// 	return max (res[capacity], res[capacity - weight[n - 1]] + value[n - 1]);
// }


int main(int argc, char const *argv[])
{
	int weight[] = {2, 1, 3, 2}, value[] = {12, 10, 20, 15}, n = 4, capacity = 5;

    printf("%d\n", pack (weight, value, n, capacity));

	return 0;
}
