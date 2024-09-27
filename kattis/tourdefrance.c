#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    double diff = *((double*)a) - *((double*)b);
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0; // will probably never happen
}

int main()
{
    int r, f;

    while (1) {
        scanf("%d", &r);
        if (!r) {
            break;
        }
        scanf(" %d\n", &f);

        int rear[r];
        int front[f];
        double ratios[r*f];

        for (int i = 0; i < r; i++) {
            scanf("%d", rear+i);
            getchar();
        }
        for (int i = 0; i < f; i++) {
            scanf("%d", front+i);
            getchar();
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < f; j++) {
                ratios[i*f + j] = rear[i] / (double) front[j];
            }
        }
        qsort(ratios, r*f, sizeof(double), cmp);

        double max_spread = 0;
        for (int i = 0; i < r*f-1; i++) {
            double spread = ratios[i+1] / ratios[i];
            if (spread > max_spread) {
                max_spread = spread;
            }
        }

        printf("%.2lf\n", max_spread);
    }
}