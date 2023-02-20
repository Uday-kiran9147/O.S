#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 10

int matrix1[MAX_SIZE][MAX_SIZE], matrix2[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
int row1, col1, row2, col2;

void *matrixAddition(void *arg)
{
    int *index = (int *)arg;
    int i = *index;
    for (int j = 0; j < col1; j++) {
        result[i][j] = matrix1[i][j] + matrix2[i][j];
    }
    pthread_exit(NULL);
}

void *matrixSubtraction(void *arg)
{
    int *index = (int *)arg;
    int i = *index;
    for (int j = 0; j < col1; j++) {
        result[i][j] = matrix1[i][j] - matrix2[i][j];
    }
    pthread_exit(NULL);
}

void *matrixMultiplication(void *arg)
{
    int *index = (int *)arg;
    int i = *index;
    for (int j = 0; j < col2; j++) {
        result[i][j] = 0;
        for (int k = 0; k < col1; k++) {
            result[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
    pthread_exit(NULL);
}

void *matrixTrace(void *arg)
{
    int *sum = (int *)arg;
    *sum = 0;
    for (int i = 0; i < row1; i++) {
        *sum += matrix1[i][i];
    }
    pthread_exit(NULL);
}

void *matrixEquality(void *arg)
{
    int *equal = (int *)arg;
    *equal = 1;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            int temp = 0;
            for (int k = 0; k < col1; k++) {
                temp += matrix1[i][k] * matrix2[k][j];
            }
            if (temp != matrix2[i][j]) {
                *equal = 0;
                pthread_exit(NULL);
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    int operation, sum = 0, equal = 0;
    pthread_t threads[MAX_SIZE];
    printf("Enter the number of rows and columns of matrix 1: ");
    scanf("%d %d", &row1, &col1);
    printf("Enter the elements of matrix 1: ");
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
    printf("Enter the number of rows and columns of matrix 2: ");
    scanf("%d %d", &row2, &col2);
    printf("Enter the elements of matrix 2: ");
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }
    matrixAddition(matrix1);
    return 0;
}

