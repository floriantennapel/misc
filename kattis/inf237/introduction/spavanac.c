#include <stdio.h>

int main() {
    int h, m;
    scanf("%d %d", &h, &m);
    
    printf("%d ", m < 45 ? (h + 23) % 24 : h);
    printf("%d\n", (m + 15) % 60);
}
