#include <ios>
#include <iostream>

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, q, a, b;
    char op;

    std::cin >> n >> q;

    int forest[n+1];
    for (int i = 0; i <= n; i++) {
        forest[i] = i;
    }
    
    for (int i = 0; i < q; i++) {
      std::cin >> op >> a >> b;
        if (op == '=') {
            forest[find(forest, a)] = find(forest, b);
        } else {
            std::cout << ((find(forest, a) == find(forest, b)) ? "yes\n" : "no\n");
        }
    }
}
