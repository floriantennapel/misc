#include <stdio.h>

int main()
{
    int n, k, s;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &s);
        if (s == k) {
            switch (i) {
            case 0:
                puts("fyrst");
                return 0;
            case 1:
                puts("naestfyrst");
                return 0;
            default:
                printf("%d fyrst\n", i+1);
                return 0;
            }
        }
    }
}
