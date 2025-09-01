#include <stdio.h>

int main() {
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int arr[50][50] = {0};  // initialized with 0

    char choice;
    do {
        int r, c, val;
        printf("Enter row index (0 to %d): ", rows - 1);
        scanf("%d", &r);
        printf("Enter column index (0 to %d): ", cols - 1);
        scanf("%d", &c);
        printf("Enter value: ");
        scanf("%d", &val);

        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            arr[r][c] = val;
            printf("Value inserted at (%d,%d)\n", r, c);
        } else {
            printf("Invalid position!\n");
        }

        printf("Do you want to insert another value? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    // Print array
    printf("\nFinal 2D Array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
