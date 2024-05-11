#include <stdio.h>

unsigned long long countForeigners() {
    int current, prev;
    int sum = 0;
    
    prev = scanf("%d", &prev);
    while (1) {
        scanf("%d", &current);
        if (!current) {
            return sum;
        }
        
        if (current > prev * 2) {
            sum += current - prev * 2;
        }
        
        prev = current;
    }
}

int main() {
    int t;
    
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        printf("%llu\n", countForeigners());
    }
}
