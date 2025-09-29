#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 99999

struct Edge {
    int u, v, w;
};

void bellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[MAX];
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].u, v = edges[j].v, w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("Bellman-Ford distances from %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("%d -> %d\n", i, dist[i]);
}

int main() {
    int V = 5, E = 8;
    struct Edge edges[] = {
        {0,1,-1}, {0,2,4},
        {1,2,3}, {1,3,2}, {1,4,2},
        {3,2,5}, {3,1,1}, {4,3,-3}
    };
    bellmanFord(edges, V, E, 0);
    return 0;
}
