#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    return *((int*) a) - *((int*) b);
}

int max_items(int n, int x, const int* nums) {
    int prev = nums[0];

    for (int i = 1; i < n; i++) {
        int current = nums[i];
        if (current + prev > x) {
            return i;
        }
        prev = current;
    }

    return n;
}

int main()
{
    int n, x, tmp;
    scanf("%d %d", &n, &x);
    int nums[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &tmp);
        nums[i] = tmp;
    }
    
    qsort(nums, n, sizeof(int), cmp);

    printf("%d\n", max_items(n, x, nums));
}
