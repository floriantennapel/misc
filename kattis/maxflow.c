#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../datastructure/hashmap.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct 
{
    int capacity;
    int used;
    char is_helper;
} Edge;

typedef struct PathEdge
{
    struct PathEdge* pred;
    int a, b;
    Edge* edge;
    int flow;
} PathEdge;

int eq(const int* a, const int* b) 
{ 
    return *a == *b; 
}

size_t hash(const int* k)
{
    return *k;
}

DECLARE_HASHMAP(Edges, int, Edge, eq, hash)

typedef struct
{
    Edges* g;
    int n;
    int s;
    int t;
} Graph;


void insert(Graph* graph, int a, int b, int cap)
{
    Edges_insert(graph->g + a, b, (Edge) {cap, 0, 0});
    Edges_insert(graph->g + b, a, (Edge) {0, 0, 1});
}

PathEdge* queue;
const int** keybuf;
char* visited;
int modify(Graph* graph)
{
    memset(visited, 0, graph->n);
    int qh = 0;
    int qt = 0; 
    PathEdge* res = NULL;

    visited[graph->s] = 1;
    Edges_all_keys(graph->g + graph->s, keybuf);
    for (int i = 0; i < (graph->g + graph->s)->size; i++) {
        const int* key = keybuf[i];
        Edge* e = Edges_get(graph->g + graph->s, key);
        if (e->capacity > e->used) {
            visited[*key] = 1;
            queue[qt++] = (PathEdge) { NULL, graph->s, *key, e, e->capacity - e->used };
            if (*key == graph->t) {
                res = queue + qt - 1;
                break;
            }
        }
    }
    
    while (qt != qh && !res) {
        PathEdge* current = queue + qh++;
        Edges_all_keys(graph->g + current->b, keybuf);     
        for (int i = 0; i < (graph->g + current->b)->size; i++) {
            const int* key = keybuf[i];
            if (visited[*key]) continue;

            Edge* e = Edges_get(graph->g + current->b, key);
            if (e->capacity <= e->used)
                continue;

            visited[*key] = 1;
            queue[qt++] = (PathEdge) { current, current->b, *key, e, MIN(current->flow, e->capacity - e->used) };
            if (*key == graph->t) {
                res = queue + qt-1; 
                break;
            }
        }
    }

    if (!res)
        return 0;

    for (PathEdge* current = res; current; current = current->pred) {
        current->edge->used += current->flow;
        Edges_get(graph->g + current->b, &current->a)->used -= current->flow;
        if (current->pred)
            current->pred->flow = current->flow;
    }
    return 1;
}

Graph new_graph(int n, int s, int t)
{
    Edges* edges = malloc(sizeof(Edges) * n);
    for (int i = 0; i < n; i++)
        edges[i] = Edges_new(0);
    return (Graph) {edges, n, s, t};
}

typedef struct
{
    int a, b, c;
} Triple;

int cmp(const void* a, const void* b) {
    if (!memcmp(a, b, sizeof(Triple)))
        return 0;

    const Triple* at = (Triple*) a; 
    const Triple* bt = (Triple*) b; 
    if (at->a != bt->a) {
        return (at->a < bt->a) ? -1 : 1;
    }
    return (at->b < bt->b) ? -1 : 1;
}

int main()
{
    int n, m, s, t, a, b, c;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    Graph g = new_graph(n, s, t);
    queue = malloc(n * sizeof(PathEdge));
    keybuf = malloc(n * sizeof(void*));
    visited = malloc(n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        insert(&g, a, b, c);
    }

    while (modify(&g)) {}

    Triple* edges = malloc(sizeof(Triple) * m);
    int stack_top = 0;
    int flow_sum = 0;
    for (int i = 0; i < n; i++) {
        Edges_all_keys(g.g + i, keybuf);
        for (int j = 0; j < (g.g + i)->size; j++) {
            Edge* e = Edges_get(g.g + i, keybuf[j]);
            if (!e->is_helper && (e->used != 0)) {
                if (i == g.s)
                    flow_sum += e->used;
                edges[stack_top++] = (Triple) {i, *keybuf[j], e->used};
            }
        }
    }
    qsort(edges, stack_top, sizeof(Triple), cmp);
    printf("%d %d %d\n", n, flow_sum, stack_top);
    for (int i = 0; i < stack_top; i++) {
        Triple* t = edges + i;
        printf("%d %d %d\n", t->a, t->b, t->c);
    }
}
