#include <stdio.h>

int stack[1000000];

int find(int* forest, int node)
{
    stack[0] = node;
    int top = 0;

    int current = node;
    int parent;
    while ((parent = forest[current]) != current) {
        current = parent;
        stack[++top] = current;
    }

    for (int i = top; i >= 0; i--) {
        forest[stack[i]] = current;
    }
    return current;
}

int main()
{
    int n, q, a, b;
    char op;

    scanf("%d %d\n", &n, &q);

    int forest[n+1];
    for (int i = 0; i <= n; i++) {
        forest[i] = i;
    }

    for (int i = 0; i < q; i++) {
        scanf("%c %d %d\n", &op, &a, &b);
        if (op == '=') {
            forest[find(forest, a)] = find(forest, b);
        } else {
            printf("%s\n", (find(forest, a) == find(forest, b)) ? "yes" : "no");
        }
    }
}
