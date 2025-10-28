#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("Enter matrix size (2-10): ");
    scanf("%d", &n);

    if(n < 2 || n > 10) {
        printf("Invalid size.\n");
        return 0;
    }

    int mat[n][n];
    int tempRow[n];
    srand(time(NULL));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            *(*(mat + i) + j) = rand() % 256;
        }
    }

    printf("\nOriginal Randomly Generated Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%4d", *(*(mat + i) + j));
        }
        printf("\n");
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int *a = *(mat + i) + j;
            int *b = *(mat + j) + i;
            int temp = *a;
            *a = *b;
            *b = temp;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n / 2; j++) {
            int *left = *(mat + i) + j;
            int *right = *(mat + i) + (n - 1 - j);
            int temp = *left;
            *left = *right;
            *right = temp;
        }
    }

    printf("\nMatrix after 90-degree Clockwise Rotation:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%4d", *(*(mat + i) + j));
        }
        printf("\n");
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int sum = 0, count = 0;
            for(int x = i - 1; x <= i + 1; x++) {
                for(int y = j - 1; y <= j + 1; y++) {
                    if(x >= 0 && x < n && y >= 0 && y < n) {
                        sum += *(*(mat + x) + y);
                        count++;
                    }
                }
            }
            tempRow[j] = sum / count;
        }
        for(int j = 0; j < n; j++) {
            *(*(mat + i) + j) = tempRow[j];
        }
    }

    printf("\nMatrix after Applying 3x3 Smoothing Filter:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%4d", *(*(mat + i) + j));
        }
        printf("\n");
    }

    return 0;
}