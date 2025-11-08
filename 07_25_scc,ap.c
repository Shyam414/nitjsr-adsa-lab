#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int V;                     
int adj[MAX][MAX];         
int timeDFS;

//SCC (Kosaraju)
int vis[MAX], stack[MAX], top;

void DFS1(int u){
    vis[u] = 1;
    for(int v=0; v<V; v++)
        if(adj[u][v] && !vis[v]) DFS1(v);
    stack[top++] = u;
}

void DFS2(int u, int transpose[MAX][MAX]){
    vis[u] = 1;
    printf("%d ", u);
    for(int v=0; v<V; v++)
        if(transpose[u][v] && !vis[v]) DFS2(v, transpose);
}

void SCC(){
    top = 0;
    memset(vis, 0, sizeof(vis));
    for(int i=0; i<V; i++)
        if(!vis[i]) DFS1(i);

    int transpose[MAX][MAX];
    for(int i=0; i<V; i++)
        for(int j=0; j<V; j++)
            transpose[i][j] = adj[j][i];

    memset(vis, 0, sizeof(vis));
    printf("Strongly Connected Components:\n");
    for(int i=top-1; i>=0; i--){
        int v = stack[i];
        if(!vis[v]){
            DFS2(v, transpose);
            printf("\n");
        }
    }
}

// Biconnected Components
int disc[MAX], low[MAX], parent[MAX], visited[MAX];

void BCCUtil(int u){
    static int time = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++time;
    int children = 0;

    for(int v=0; v<V; v++){
        if(!adj[u][v]) continue;
        if(!visited[v]){
            children++;
            parent[v] = u;
            BCCUtil(v);

            low[u] = (low[u]<low[v])?low[u]:low[v];

            // Articulation Point
            if(parent[u]==-1 && children>1) printf("AP: %d\n", u);
            if(parent[u]!=-1 && low[v]>=disc[u]) printf("AP: %d\n", u);

            // Bridge
            if(low[v] > disc[u]) printf("Bridge: %d-%d\n", u, v);
        }
        else if(v != parent[u]){
            low[u] = (low[u]<disc[v])?low[u]:disc[v];
        }
    }
}

void BiconnectedComponents(){
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    for(int i=0; i<V; i++)
        if(!visited[i]) BCCUtil(i);
}


int main(){
    V = 5;
    memset(adj, 0, sizeof(adj));
    int edges[][2] = {{1,0},{0,2},{2,1},{0,3},{3,4}};
    int E = 5;
    for(int i=0; i<E; i++)
        adj[edges[i][0]][edges[i][1]] = 1;

    // SCC
    SCC();

    printf("\nArticulation Points and Bridges (Undirected):\n");

    memset(visited,0,sizeof(visited));
    int undirected[MAX][MAX];
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            undirected[i][j] = adj[i][j] || adj[j][i];

    memcpy(adj, undirected, sizeof(undirected));
    BiconnectedComponents();

    return 0;
}
