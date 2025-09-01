#include <stdio.h>

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;

    int i = left, j = right;
    while (i <= j) {
        // check if bit is set (1 or 0)
        while (i <= right && ((arr[i] >> bit) & 1) == 0) i++;
        while (j >= left && ((arr[j] >> bit) & 1) == 1) j--;

        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Recursive calls for next bit
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    // Find the maximum number to determine highest bit
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    int bit = 0;
    while ((max >> bit) > 0) bit++;  // number of bits needed
    bit--; // MSB index

    radixExchangeSort(arr, 0, n - 1, bit);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
