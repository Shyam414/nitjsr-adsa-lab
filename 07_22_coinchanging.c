#include <stdio.h>

void coinChange(int coins[], int n, int amount){
    printf("Change for %d:\n", amount);
    for(int i=0;i<n;i++){
        while(amount >= coins[i]){
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
}

int main(){
    int coins[] = {25, 10, 5, 1};  
    int n = sizeof(coins)/sizeof(coins[0]);
    int amount = 63;
    coinChange(coins, n, amount);
    return 0;
}
