#include <stdio.h>

int main()
{
    int map['v' - '.' + 1];
    map['.' - '.'] = 20;
    map['O' - '.'] = 10;
    map['\\' - '.'] = 25;
    map['/' - '.'] = 25;
    map['A' - '.'] = 35;
    map['^' - '.'] = 5;
    map['v' - '.'] = 22;

    int n, m;
    long sum = 0;

    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = getchar();
            sum += map[c - '.'];
        }
        getchar(); // newline
    }

    printf("%ld\n", sum);
}
