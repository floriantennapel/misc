#include <stdio.h>

int main() {
    int x, y, n, wroteSomething;
    scanf("%d %d %d", &x, &y, &n);
    
    for (int i = 1; i <= n; i++) {
        wroteSomething = 0;
        
        if (i % x == 0) {
            printf("Fizz");
            wroteSomething = 1;
        }
        if (i % y == 0) {
            printf("Buzz");
            wroteSomething = 1;
        }
        
        if (!wroteSomething) {
            printf("%d", i);
        }
        puts("");
    }
}
