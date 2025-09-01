#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

void printArray(int arr[ROWS][COLS]) {
    printf("\nCurrent Array:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[ROWS][COLS] = {0}; // Initialize all elements to 0
    char choice;

    while (1) {
        printArray(arr);

        printf("\nDo you want to insert into a row (r) or column (c)? (q to quit): ");
        scanf(" %c", &choice);  // space before %c avoids newline issues

        if (choice == 'q') {
            break;
        }

        if (choice == 'r') {
            int rowIndex;
            printf("Enter row index (0 to %d): ", ROWS - 1);
            scanf("%d", &rowIndex);

            if (rowIndex < 0 || rowIndex >= ROWS) {
                printf("Invalid row index!\n");
                continue;
            }

            printf("Enter %d values for row %d: ", COLS, rowIndex);
            for (int j = 0; j < COLS; j++) {
                scanf("%d", &arr[rowIndex][j]);
            }
        }
        else if (choice == 'c') {
            int colIndex;
            printf("Enter column index (0 to %d): ", COLS - 1);
            scanf("%d", &colIndex);

            if (colIndex < 0 || colIndex >= COLS) {
                printf("Invalid column index!\n");
                continue;
            }

            printf("Enter %d values for column %d: ", ROWS, colIndex);
            for (int i = 0; i < ROWS; i++) {
                scanf("%d", &arr[i][colIndex]);
            }
        }
        else {
            printf("Invalid choice! Please enter 'r' or 'c'.\n");
        }
    }

    printf("\nFinal Array State:\n");
    printArray(arr);

    return 0;
}
