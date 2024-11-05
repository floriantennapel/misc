#include <stdio.h>

int main()
{
    int n;
    char buf[102];
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        fgets(buf, 102, stdin);
        if (!(i % 2)) {
            printf("%s", buf);
        }
    }
}
