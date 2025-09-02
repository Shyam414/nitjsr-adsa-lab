#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Insertion sort for buckets
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Address Calculation Sort
void addressCalculationSort(int arr[], int n) {
    if (n <= 0) return;

    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    // number of buckets
    int range = max - min + 1;
    int bucketCount = n; // one bucket per element

    // create buckets
    int *buckets[bucketCount];
    int bucketSizes[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }

    // distribute elements
    for (int i = 0; i < n; i++) {
        int addr = (arr[i] - min) * bucketCount / range;
        if (addr >= bucketCount) addr = bucketCount - 1;
        buckets[addr][bucketSizes[addr]++] = arr[i];
    }

    // sort each bucket and merge back
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i], bucketSizes[i]);
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
        free(buckets[i]);
    }
}

// Utility function
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    addressCalculationSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
