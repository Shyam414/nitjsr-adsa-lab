#include<stdio.h>
#include<stdlib.h>

typedef struct Edge {
    int src, dest, weight;
}Edge;

typedef struct Subset {
    int parent;
    int rank;
}Subset;

int find(Subset set[], int i){
    if(set[i].parent!=i){
        set[i].parent=find(set,set[i].parent);
    }
    return set[i].parent;
}

void Union(struct Subset set[], int x, int y) {
    int xroot = find(set, x);
    int yroot = find(set, y);

    if (set[xroot].rank < set[yroot].rank)
        set[xroot].parent = yroot;
    else if (set[xroot].rank > set[yroot].rank)
        set[yroot].parent = xroot;
    else {
        set[yroot].parent = xroot;
        set[xroot].rank++;
    }
}

int cmpEdge(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void Kruskal(struct Edge edges[], int V, int E) {
    qsort(edges, E, sizeof(edges[0]), cmpEdge);

    struct Subset* set = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        set[v].parent = v;
        set[v].rank = 0;
    }

    struct Edge result[V]; 
    int e = 0; 
    int i = 0; 

    while (e < V - 1 && i < E) {
        struct Edge next = edges[i++];

        int x = find(set, next.src);
        int y = find(set, next.dest);

        if (x != y) {
            result[e++] = next;
            Union(set, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    int minCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d  weight = %d\n",
               result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Total cost of MST = %d\n", minCost);

    free(set);
}

int main() {
    int V = 4;  
    int E = 5; 

    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    Kruskal(edges, V, E);
    return 0;
}