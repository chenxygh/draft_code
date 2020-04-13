#include <stdlib.h>
#include <stdio.h>

int max (int a, int b) {
	return a > b? a: b;
}

// bottom-up
// return value
// T: O(N * W), S: (W)
int goldMining_1 (int N, int W, int G[], int P[]) {
	int a[11], b[11];
	int *preResult = a;
	int *result = b;
	// 初始化边界行
	for (int i = 0; i <= W; ++i) {
		preResult[i] = i < P[0]? 0: G[0];
	}

	// dynamic programming
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j <= W; ++j) {
			result[j] = j < P[i]? preResult[j]: max (preResult[j], preResult[j - P[i]] + G[i]);
		}
		int *temp = result;
		result = preResult;
		preResult = temp;
	}

	for (int i = 0; i <= W; ++i) {
		printf("%d ", preResult[i]);
	}
	printf("\n");
	for (int i = 0; i <= W; ++i) {
		printf("%d ", result[i]);
	}

	return preResult[W];
}

// bottom-up with memoization
// T: O(N * W), S: (N * W)
int goldMining_2 (int N, int W, int G[], int P[], int **S) {
	int *preResult = S[0], *result = S[0];
	// 初始化边界行
	for (int i = 0; i <= W; ++i) {
		preResult[i] = i < P[0]? 0: G[0];
	}

	// dynamic programming
	for (int i = 1; i < N; ++i) {
		preResult = result;
		result = (++S)[0];
		for (int j = 0; j <= W; ++j) {
			result[j] = j < P[i]? preResult[j]: max (preResult[j], preResult[j - P[i]] + G[i]);
		}
	}

	return result[W];
}


// top-down with memoization
// T: < O(N * W), S: (N * W)
int goldMining_3 (int N, int W, int G[], int P[], int **S, int *res) {
	if (N == 1 && W < P[0]) return S[0][W] = 0;
	if (N == 1 && W >= P[0]) return S[0][W] = G[0];

	if (S[N - 1][W] >= 0) return S[N - 1][W];

	int val = goldMining_3 (N - 1, W, G, P, S);
	// TODO: res
	return S[N - 1][W] = W < P[N - 1]? val: max (goldMining_3 (N - 1, W - P[N - 1], G, P, S) + G[N - 1], val);
}

// 测试函数
// 在已知 S[][] 的情形下， 获得最优解
// 当然， 可以在带备忘的 _3 中，记录， 但是那样结构混乱
void test_2 (int N, int W, int P[], int **S) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= W; ++j) {
			printf("%5d ", S[i][j]);
		}
		printf("\n");
	}

	bool res[N];
	int cnt = W;
	for (int i = N - 1; i >= 1; --i) {
		if (S[i][cnt] == S[i - 1][cnt]) {
			res[i] = false;
		} else {
			res[i] = true;
			cnt -= P[i];
		}
	}
	res[0] = cnt >= P[0];

	printf("\n\n\nres:\n");
	for (int i = 0; i < N; ++i) {
		printf("%d ", res[i]);
	}
}

int main(int argc, char const *argv[])
{
	int N = 5, W = 10;
	int G[] = {400, 500, 200, 300, 350};
	int P[] = {5, 5, 3, 4, 3};
	int **S = (int **)malloc(sizeof (int *) * N);
	for (int i = 0; i < N; ++i) {
		S[i] = (int *)malloc(sizeof (int) * (W + 1));
		for (int j = 0; j <= W; ++j) S[i][j] = -1;
	}

	
	int (*goldMining_with_S) (int ,int , int *, int *, int **);
	goldMining_with_S = goldMining_3;
	goldMining_with_S (N, W, G, P, S);

	void (*test) (int , int , int *, int **);
	test = test_2;

	test (N, W, P, S);
	

	return 0;
}
