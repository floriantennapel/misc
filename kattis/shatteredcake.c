#include <stdio.h>

int main()
{
    int n, w, wi, li;

    scanf("%d\n%d\n", &w, &n);

    int area = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d\n", &wi, &li);
        area += wi * li;
    }

    printf("%d\n", area / w);
}
