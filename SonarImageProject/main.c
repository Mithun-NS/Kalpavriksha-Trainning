#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define MIN_SIZE 2

void generateMatrix(int n, int mat[n][n]);
void printMatrix(int n, int mat[n][n], const char *message);
void rotate90Clockwise(int n, int mat[n][n]);
void applySmoothingFilter(int n, int mat[n][n]);

int main() {
    int n;
    printf("Enter matrix size (%d-%d): ",MIN_SIZE, MAX_SIZE);
    scanf("%d", &n);

    if(n < MIN_SIZE || n > MAX_SIZE) {
        printf("Invalid size.\n");
        return 0;
    }

    int mat[n][n];
    int tempRow[n];
    srand(time(NULL));
    generateMatrix(n, mat);
    printMatrix(n, mat, "Original Randomly Generated Matrix:");

    rotate90Clockwise(n, mat);
    printMatrix(n, mat, "Matrix after 90-degree Clockwise Rotation:");

    applySmoothingFilter(n, mat);
    printMatrix(n, mat, "Matrix after Applying 3x3 Smoothing Filter:");

    return 0;
}
void generateMatrix(int n, int mat[n][n]){
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            *(*(mat + i) + j) = rand() % 256;
        }
    }
}
 void printMatrix(int n, int mat[n][n], const char *message) {
    printf("\n%s\n", message);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", *(*(mat + i)+j));
        printf("\n");
    }
}
void rotate90Clockwise(int n, int mat[n][n]){
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
}

void applySmoothingFilter(int n, int mat[n][n]) {
    int tempRow[n];
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
}
