#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int v; // vertex
    double w; // weight
} Edge;

typedef struct
{
    unsigned valid: 1;
    double w;
} Cost;

// w is in this context distance from source to v, not the weight of an edge
typedef Edge PotentialDist;

void add_neighbors(PotentialDist* to_search, int* size, const Edge* neighbors, int n_neighbors, double dist_to_source);
void swap_buffers(PotentialDist** current, PotentialDist** next, int* cs, int* ns);
void invalidate(Cost* costs, const Edge* graph, int v, const int* n_neighbors, int vertex);

int main()
{
    int v, e;
    scanf("%d %d", &v, &e);

    Edge (*graph)[v] = malloc(sizeof(Edge)*v*v); // can be indexed like 2d array
    int n_neighbors[v]; // size of each adjacency list
    memset(n_neighbors, 0, sizeof(int)*v);
    
    // reading graph from file
    int a, b;
    double w;
    for (int i = 0; i < e; i++) {
        scanf("%d %d %lf", &a, &b, &w);
        Edge* e = graph[a] + n_neighbors[a]++;
        e->v = b;
        e->w = w;
    }

    PotentialDist buf1[e];
    PotentialDist buf2[e];

    Cost costs[v];
    memset(costs, 0, sizeof(Cost)*v);

    PotentialDist* current_to_search = buf1;
    PotentialDist* next_to_search    = buf2;
    int cs = 0; // size of current_to_search
    int ns = 0; // size of next_to_search
    
    costs[0].valid = 1;
    add_neighbors(current_to_search, &cs, graph[0], n_neighbors[0], 0);

    // relax all edges v-1 times
    for (int i = 0; i < v; i++) {
        // only edges in current_to_search could have changed
        for (int j = 0; j < cs; j++) {
            PotentialDist* pd = current_to_search + j;
            if (!costs[pd->v].valid || pd->w < costs[pd->v].w) {
                costs[pd->v].w = pd->w;
                costs[pd->v].valid = 1;
                add_neighbors(next_to_search, &ns, graph[pd->v], n_neighbors[pd->v], costs[pd->v].w);
            }
        } 
        swap_buffers(&current_to_search, &next_to_search, &cs, &ns);
    }

    // invalidating vertices that can still be relaxed
    for (int i = 0; i < cs; i++) {
        invalidate(costs, graph[0], v, n_neighbors, current_to_search[i].v);
    }

    for (int i = 0; i < v; i++) {
        Cost* c = costs + i;
        if (c->valid)
            printf("%d %.2lf\n", i, c->w);
        else  
            printf("%d not valid\n", i);
    }
}

void add_neighbors(PotentialDist* to_search, int* size, const Edge* neighbors, int n_neighbors, double dist_to_source)
{
    for (int i = 0; i < n_neighbors; i++) {
        const Edge* e = neighbors + i;
        PotentialDist* pd = to_search + (*size)++;
        pd->v = e->v;
        pd->w = dist_to_source + e->w;
    }
}

void swap_buffers(PotentialDist** current, PotentialDist** next, int* cs, int* ns)
{
    PotentialDist* tmp = *current;
    *current = *next;
    *next = tmp;
    *cs = *ns;
    *ns = 0;
}

void invalidate(Cost* costs, const Edge* graph, int v, const int* n_neighbors, int vertex)
{
    Cost* c = costs + vertex;
    if (!c->valid) return;
    c->valid = 0;

    const Edge* neighbors = graph + v*(vertex);
    for (int i = 0; i < n_neighbors[vertex]; i++) {
        invalidate(costs, graph, v, n_neighbors, neighbors[i].v);
    }
}
