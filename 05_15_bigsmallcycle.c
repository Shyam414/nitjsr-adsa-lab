#include <stdio.h>

#define MAX 100

int V;
int graph[MAX][MAX];
int visited[MAX];
int stack[MAX], stackSize;
int minCycle = 1e9, maxCycle = -1;

void dfs(int u, int parent, int isDirected) {
    visited[u] = 1;
    stack[stackSize++] = u;

    for (int v = 0; v < V; v++) {
        if (!graph[u][v]) continue;

        if (!visited[v]) {
            dfs(v, u, isDirected);
        } else {
            if (!isDirected && v == parent) continue;

            int idx = -1;
            for (int i = 0; i < stackSize; i++)
                if (stack[i] == v) { idx = i; break; }

            if (idx != -1) {
                int cycleLen = stackSize - idx;
                if (cycleLen > 1) { 
                    if (cycleLen < minCycle) minCycle = cycleLen;
                    if (cycleLen > maxCycle) maxCycle = cycleLen;
                }
            }
        }
    }

    stackSize--;
    visited[u] = 0; 
}

void findCycles(int isDirected) {
    minCycle = 1e9;
    maxCycle = -1;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            visited[j] = 0;
        stackSize = 0;
        dfs(i, -1, isDirected);
    }

    if (maxCycle == -1)
        printf("No cycles found.\n");
    else {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length  = %d\n", maxCycle);
    }
}

int main() {
    V = 5;
    int temp[5][5] = {
        {0,1,1,0,0},
        {0,0,0,1,0},
        {0,0,0,1,0},
        {0,0,0,0,1},
        {1,0,0,0,0}
    };

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = temp[i][j];

    printf("Directed Graph:\n");
    findCycles(1);

    V = 4;
    int temp2[4][4] = {
        {0,1,1,0},
        {1,0,1,1},
        {1,1,0,1},
        {0,1,1,0}
    };

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = temp2[i][j];

    printf("\nUndirected Graph:\n");
    findCycles(0);

    return 0;
}
