#include <stdio.h>
#include <stdlib.h>

struct Job{ char id; int deadline, profit; };

int cmp(const void* a,const void* b){
    return ((struct Job*)b)->profit - ((struct Job*)a)->profit;
}

void jobSequencing(struct Job jobs[], int n){
    qsort(jobs,n,sizeof(jobs[0]),cmp);
    int slot[n]; for(int i=0;i<n;i++) slot[i]=-1;
    int totalProfit=0;
    printf("Selected jobs: ");
    for(int i=0;i<n;i++){
        for(int j=jobs[i].deadline-1;j>=0;j--){
            if(slot[j]==-1){
                slot[j]=i; totalProfit+=jobs[i].profit;
                printf("%c ", jobs[i].id); break;
            }
        }
    }
    printf("\nTotal Profit = %d\n", totalProfit);
}

int main(){
    struct Job jobs[]={{'a',2,100},{'b',1,19},{'c',2,27},{'d',1,25},{'e',3,15}};
    int n=5;
    jobSequencing(jobs,n);
    return 0;
}
