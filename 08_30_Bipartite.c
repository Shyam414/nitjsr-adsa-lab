#include <stdio.h>

#define MAX 100
#define QUEUE_SIZE 100

int graph[MAX][MAX];
int color[MAX];
int n, e;

int isBipartite() {
    int queue[QUEUE_SIZE], front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        color[i] = -1;

    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {
            color[start] = 0;
            queue[rear++] = start;

            while (front < rear) {
                int u = queue[front++];

                for (int v = 0; v < n; v++) {
                    if (graph[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        } else if (color[v] == color[u]) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    int u, v;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    if (isBipartite())
        printf("Graph is Bipartite\n");
    else
        printf("Graph is NOT Bipartite\n");

    return 0;
}
