#include <stdio.h>
#include <stdlib.h>

#define EXPECTED_SIZE 100000000

int cycleLen(unsigned long long n, int* memo) {
    if (n >= EXPECTED_SIZE) {
        puts("oh boy");
        exit(1);
    }
    if (memo[n]) {
        return memo[n];
    }

    unsigned long long next;
    if (n % 2 == 0) {
        next = n / 2;
    } else {
        next = n * 3 + 1;
    }

    int count = 1 + cycleLen(next, memo);
    memo[n] = count;

    return count;
}

int maxCycle(int i, int j, int* memo) {
    int max = 0, result;
    for (; i <= j; i++) {
        result = cycleLen(i, memo);
        if (result > max) {
            max = result;
        }
    }

    return max;
}

int main() {
    int* memo = calloc(EXPECTED_SIZE, sizeof(int));
    memo[1] = 1;

    long long unsigned i, j;
    while (scanf("%lld %lld", &i, &j) != EOF) {
        printf("%lld %lld %d\n", i, j, maxCycle(i, j, memo));
    }

    return 0;
}
