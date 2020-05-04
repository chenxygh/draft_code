#include <stdio.h>

#define INT_MIN -2147483648
#define INT_MAX 2147483647

void countSort (int *nums, int numsSize) {
	int min = INT_MAX, max = INT_MIN, copy[numsSize];
	for (int i = 0; i < numsSize; ++i) {
		if (nums[i] < min) min = nums[i];
		if (nums[i] > max) max = nums[i];
		copy[i] = nums[i];
	}
	int length = max - min + 1, count[length];
	for (int i = 0; i < length; ++i) count[i] = 0;
	for (int i = 0; i < numsSize; ++i) ++count[nums[i] - min];
	for (int i = 1; i < length; ++i) count[i] += count[i - 1];
	for (int i = 0; i < numsSize; ++i) {
		nums[--count[copy[i] - min]] = copy[i];
	}
}

int main(int argc, char const *argv[])
{
	int nums[] = {3, 6, 7, 8, 4, 5, 11, 23, 34, 88}, numsSize = 10;
    countSort (nums, numsSize);
    for (int i = 0; i < numsSize; ++i) printf("%5d", nums[i]);
    printf("\n");
	return 0;
}
