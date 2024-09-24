#include <stdio.h>

int main()
{
    int n, w, h, m;
    scanf("%d %d %d\n", &n, &w, &h);

    int hyp_square = w*w + h*h;

    for (int i = 0; i < n; i++) {
        scanf("%d\n", &m);
        if (m*m <= hyp_square) puts("DA");
        else puts("NE");
    }
}