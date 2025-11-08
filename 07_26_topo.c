#include <stdio.h>
#include <string.h>

#define MAX 100

int V;                  
int adj[MAX][MAX];     
int visited[MAX];
int stack[MAX], top = -1;

void topoDFS(int u){
    visited[u] = 1;
    for(int v=0; v<V; v++){
        if(adj[u][v] && !visited[v]){
            topoDFS(v);
        }
    }
    stack[++top] = u;  
}

void topologicalSort(){
    memset(visited, 0, sizeof(visited));
    top = -1;

    for(int i=0; i<V; i++){
        if(!visited[i]) topoDFS(i);
    }

    printf("Topological Order: ");
    for(int i=top; i>=0; i--) printf("%d ", stack[i]);
    printf("\n");
}

int main(){
    V = 6;  
    memset(adj, 0, sizeof(adj));

    adj[5][2] = 1;
    adj[5][0] = 1;
    adj[4][0] = 1;
    adj[4][1] = 1;
    adj[2][3] = 1;
    adj[3][1] = 1;

    topologicalSort();
    return 0;
}
