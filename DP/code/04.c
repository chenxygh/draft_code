#include <stdio.h>

int max (int a, int b) {
    return a > b? a: b;
}

void zeroOnePack (int weight, int value, int capacity, int *dp) {
	for (int i = capacity; i >= weight; --i) {
		dp[i] = max (dp[i], dp[i - weight] + value);
	}
}

void completePack (int weight, int value, int capacity, int *dp) {
	for (int i = weight; i <= capacity; ++i) {
		dp[i] = max (dp[i], dp[i - weight] + value);
	}
}

int pack (int *weight, int *value, int n, int capacity) {
	int dp[capacity + 1];
	for (int i = 0; i <= capacity; ++i) dp[i] = i >= weight[0]? value[0]: 0;
	for (int i = 1; i < n; ++i) {
		completePack (weight[i], value[i], capacity, dp);
	}
	return dp[capacity];
}

void multiplePack (int weight, int value, int count, int capacity, int *dp) {
	if (count * weight >= capacity) {
		completePack (weight, value, capacity, dp);
		return;
	}
	int n = count;
	for (int i = 1; i < count; i *= 2) {
		zeroOnePack (weight * i, value * i, capacity, dp);
		n -= i;
	}
	zeroOnePack (weight * n, value * n, capacity, dp);
}

int multiple (int *weight, int *value, int *count, int n, int capacity) {
	int dp[capacity + 1];
	for (int i = 0; i <= capacity; ++i) dp[i] = 0;
	for (int i = 0; i < n; ++i) {
		multiplePack (weight[i], value[i], count[i], capacity, dp);
	}
	return dp[capacity];
}

int main(int argc, char const *argv[])
{
    int weight[] = {2, 1, 3, 2}, value[] = {12, 10, 20, 15}, count[] = {2, 3, 1, 2}, n = 4, capacity = 5;

    printf("%d\n", multiple (weight, value, count, n, capacity));

    return 0;
}
