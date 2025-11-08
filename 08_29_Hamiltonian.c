#include <stdio.h>

#define MAX 20

int n, e;
int graph[MAX][MAX];
int path[MAX];

int isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return 0;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;
    return 1;
}

int hamiltonianUtil(int pos) {
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        return 0;
    }
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamiltonianUtil(pos + 1))
                return 1;
            path[pos] = -1;
        }
    }
    return 0;
}

int main() {
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    int u, v;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++) path[i] = -1;
    path[0] = 0;

    if (hamiltonianUtil(1)) {
        printf("Hamiltonian Cycle exists:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]);
    } else {
        printf("No Hamiltonian Cycle exists.\n");
    }

    return 0;
}
