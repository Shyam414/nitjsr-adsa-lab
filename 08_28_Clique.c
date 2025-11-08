#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int n, e, m;

int isClique(int vertices[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (graph[vertices[i]][vertices[j]] == 0)
                return 0;
        }
    }
    return 1;
}

int checkClique(int index, int start, int vertices[]) {
    if (index == m) {
        return isClique(vertices, m);
    }
    for (int i = start; i < n; i++) {
        vertices[index] = i;
        if (checkClique(index + 1, i + 1, vertices))
            return 1;
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

    printf("Enter clique size m: ");
    scanf("%d", &m);

    int vertices[MAX];
    if (checkClique(0, 0, vertices))
        printf("Graph contains a clique of size %d\n", m);
    else
        printf("No clique of size %d found\n", m);

    return 0;
}
