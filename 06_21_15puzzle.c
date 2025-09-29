#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
#define INF 999999

typedef struct Node {
    int mat[N][N];
    int x, y;        
    int cost;         
    int level;       
    struct Node* parent;
} Node;

int final[N][N] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,0}
};

int row[] = {1,0,-1,0};
int col[] = {0,-1,0,1};

int calculateCost(int mat[N][N]) {
    int cost = 0;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (mat[i][j] && mat[i][j] != final[i][j]) {
                int val = mat[i][j];
                int targetX = (val-1)/N;
                int targetY = (val-1)%N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
    return cost;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            node->mat[i][j] = mat[i][j];

    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->parent = parent;
    node->level = level;
    node->cost = calculateCost(node->mat);
    return node;
}

void printMatrix(int mat[N][N]) {
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void solve(int init[N][N], int x, int y) {
    Node* root = newNode(init, x, y, x, y, 0, NULL);
    root->cost = calculateCost(root->mat);

    printf("Initial state (heuristic=%d):\n", root->cost);
    printMatrix(root->mat);

    printf("Final state:\n");
    printMatrix(final);
    printf("(Full branch & bound requires a PQ for expansions)\n");
}

int main() {
    int init[N][N] = {
        {1,2,3,4},
        {5,6,0,8},
        {9,10,7,12},
        {13,14,11,15}
    };
    int x=1, y=2; 
    solve(init,x,y);
    return 0;
}
