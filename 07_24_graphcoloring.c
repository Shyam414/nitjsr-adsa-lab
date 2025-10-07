#include <stdio.h>
#define V 4

int graph[V][V]={{0,1,1,1},{1,0,1,0},{1,1,0,1},{1,0,1,0}};
int colors[V];

int isSafe(int v,int c){
    for(int i=0;i<V;i++)
        if(graph[v][i] && colors[i]==c) return 0;
    return 1;
}

int graphColoringUtil(int m,int v){
    if(v==V) return 1;
    for(int c=1;c<=m;c++){
        if(isSafe(v,c)){
            colors[v]=c;
            if(graphColoringUtil(m,v+1)) return 1;
            colors[v]=0;
        }
    }
    return 0;
}

void graphColoring(int m){
    for(int i=0;i<V;i++) colors[i]=0;
    if(!graphColoringUtil(m,0)) printf("No solution\n");
    else{
        printf("Colors: ");
        for(int i=0;i<V;i++) printf("%d ",colors[i]);
        printf("\n");
    }
}

int main(){
    int m=3;
    graphColoring(m);
    return 0;
}
