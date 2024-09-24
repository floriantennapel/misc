#include <stdio.h>
#include <string.h>

int main()
{
    int n, m, k, r, c;
    scanf("%d %d %d\n", &n, &m, &k);

    char board[n*(m+1)];
    memset(board, '.', n*(m+1));

    for (int i = 0; i < k; i++) {
        scanf("%d %d\n", &r, &c);
        board[(r-1)*(m+1) + c-1] = '*';
    }

    for (int i = 0; i < n; i++) {
        board[i*(m+1) + m] = '\0';
        printf("%s\n", board + i*(m+1));
    }
}