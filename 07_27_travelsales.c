#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100

int tspCost(int city[MAX][MAX], int n, int pos, int visited, int cost, int start) {
    if (visited == (1<<n)-1) return cost + city[pos][start];
    int minCost = INT_MAX;
    for(int i=0; i<n; i++) {
        if(!(visited & (1<<i))) {
            int temp = tspCost(city, n, i, visited | (1<<i), cost + city[pos][i], start);
            if(temp < minCost) minCost = temp;
        }
    }
    return minCost;
}

int main() {
    int sizes[] = {10, 20, 40, 60, 100};  
    int numSizes = 5;

    printf("TSP Execution Time Table:\n");
    printf("Nodes\tTime (seconds)\n");

    for(int s=0; s<numSizes; s++){
        int n = sizes[s];
        int city[MAX][MAX];

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j) city[i][j] = 0;
                else if(i<j) city[i][j] = rand()%100 + 1;
                else city[i][j] = city[j][i];
            }
        }

        clock_t startTime = clock();

        int minCost = -1;
        if(n <= 10)
            minCost = tspCost(city, n, 0, 1, 0, 0);
        clock_t endTime = clock();
        double timeTaken = (double)(endTime - startTime)/CLOCKS_PER_SEC;

        printf("%d\t%.6f", n, timeTaken);
        if(minCost != -1) printf("\tMinCost=%d", minCost);
        else printf("\tSkipped (too large)");
        printf("\n");
    }

    return 0;
}
