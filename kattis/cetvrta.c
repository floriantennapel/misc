#include <stdio.h>

int main()
{
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int counters[] = {0, 0, 0, 0};

    int d1, d2;
    for (int i = 0; i < 3; i++) {
        scanf("%d %d\n", &d1, &d2);

        if (x1 == 0 || d1 == x1) {
            x1 = d1;
            ++(counters[0]);
        }
        else {
            x2 = d1;
            ++(counters[1]);
        }
    
        if (y1 == 0 || d2 == y1) {
            y1 = d2;
            ++(counters[2]);
        }
        else {
            y2 = d2;
            ++(counters[3]);
        }
    }

    printf("%d ", (counters[0] != 2) ? x1 : x2);
    printf("%d\n", (counters[2] != 2) ? y1 : y2);
}