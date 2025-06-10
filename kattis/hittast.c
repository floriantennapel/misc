#include <stdio.h>
#include <stdbool.h>
#include "c_macros/datastructures/vec.h"
#include "c_macros/datastructures/heap.h"

typedef unsigned long ul;
typedef struct
{
    int node;
    ul cost;
} PQNode;

typedef struct
{
    int p[3];
} Triple;

#define PQ_CMP(A, B) ((A)->cost < (B)->cost ? -1 : ((A)->cost > (B)->cost ? 1 : 0))

VEC_DEFINE(Vec, Triple)
HEAP_DEFINE(PQ, PQNode, PQ_CMP)

int main()
{
    int n, m, u, v, a, b;
    scanf("%d %d", &n, &m);

    int lodging[n+1];
    Vec graph[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", lodging+i);
        graph[i] = Vec_new(0);
    }

    while (m--) {
        scanf("%d %d %d %d", &u, &v, &a, &b);
        Vec_push(graph+u, (Triple){{a, b, v}});
        Vec_push(graph+v, (Triple){{a, b, u}});
    }
    
    ul travel_costs[n+1];
    ul min_cost = -1;
    for (int i = 0; i < 2; i++) {
        int not_found = n;
        int visited[100001] = {};
        PQ q = PQ_new();
        PQ_push(&q, (PQNode) {!i ? 1 : n, 0});
        while (q.size > 0 && not_found > 0) {
            PQNode current = PQ_pop(&q);
            if (visited[current.node])
                continue;
            visited[current.node] = true;
            --not_found;
            if (i == 0) {
                travel_costs[current.node] = current.cost;
            } else {
                ul cost = travel_costs[current.node] + current.cost + lodging[current.node];
                if (cost < min_cost)
                    min_cost = cost;
            }
            Vec* adj = graph+current.node;
            for (int j = 0; j < adj->size; j++) {
                Triple next = adj->arr[j];
                if (!visited[next.p[2]])
                    PQ_push(&q, (PQNode){next.p[2], next.p[i]+current.cost});
            }
        }
    }
    printf("%lu\n", min_cost);
}
