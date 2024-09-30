#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    int t, n;
    scanf("%d %d\n", &t, &n);
    int songs[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", songs+i);
        getchar();
    }

    qsort(songs, n, sizeof(int), cmp);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int s = songs[i];
        if ((sum + s) <= (t * 60)) sum += s;
        else break;
    }
    printf("%d\n", sum);
}