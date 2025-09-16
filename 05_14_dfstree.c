#include <stdio.h>

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

int V;
int graph[MAX][MAX];
int color[MAX], parent[MAX], disc[MAX], fin[MAX];
int timeDFS = 0;

void classifyEdge(int u, int v) {
    if (color[v] == WHITE) {
        printf("Tree Edge: %d -> %d\n", u, v);
    } else if (color[v] == GRAY) {
        printf("Back Edge: %d -> %d\n", u, v);
    } else if (color[v] == BLACK) {
        if (disc[u] < disc[v])
            printf("Forward Edge: %d -> %d\n", u, v);
        else
            printf("Cross Edge: %d -> %d\n", u, v);
    }
}

void DFSVisit(int u) {
    color[u] = GRAY;
    disc[u] = ++timeDFS;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            classifyEdge(u, v);
            if (color[v] == WHITE) {
                parent[v] = u;
                DFSVisit(v);
            }
        }
    }

    color[u] = BLACK;
    fin[u] = ++timeDFS;
}

void DFS() {
    for (int i = 0; i < V; i++) {
        color[i] = WHITE;
        parent[i] = -1;
    }
    timeDFS = 0;

    for (int u = 0; u < V; u++)
        if (color[u] == WHITE)
            DFSVisit(u);
}

int main() {
    V = 6;
    int temp[6][6] = {
        {0,1,1,0,0,0},
        {0,0,0,1,1,0},
        {0,1,0,0,1,0},
        {0,0,0,0,0,1},
        {0,0,0,1,0,1},
        {0,0,0,0,0,0}
    };

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = temp[i][j];

    DFS();

    printf("\nDiscovery/Finish times:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d: disc=%d, fin=%d\n", i, disc[i], fin[i]);

    return 0;
}
