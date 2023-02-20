#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int determinant(int **matrix, int size) {
    int det = 0, sign = 1;
    if (size == 1) {
        return matrix[0][0];
    }
    int **sub_matrix = (int **)malloc((size - 1) * sizeof(int *));
    for (int i = 0; i < size - 1; i++) {
        sub_matrix[i] = (int *)malloc((size - 1) * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        int sub_i = 0;
        for (int j = 1; j < size; j++) {
            int sub_j = 0;
            for (int k = 0; k < size; k++) {
                if (k == i) {
                    continue;
                }
                sub_matrix[sub_i][sub_j] = matrix[j][k];
                sub_j++;
            }
            sub_i++;
        }
        det += sign * matrix[0][i] * determinant(sub_matrix, size - 1);
        sign = -sign;
    }
    for (int i = 0; i < size - 1; i++) {
        free(sub_matrix[i]);
    }
    free(sub_matrix);
    return det;
}

int main() {
    int size = 3, Ⲗ=1;
    printf("size of the square matrix: %d\n",size);
//   scanf("%d", &size);
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    printf("Enter the elements:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Ⲗ: %d \n",Ⲗ);
   // scanf("%d", &Ⲗ);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(i==j){
            matrix[i][j] = matrix[i][j] - Ⲗ;
            }
        }
    }
    int result = determinant(matrix, size);
    printf("The determinant of the matrix A-ⲖI is: %d\n", result);
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}













// #include <stdio.h>

// int determinant(int matrix[3][3])
// {
//     int a = matrix[0][0];
//     int b = matrix[0][1];
//     int c = matrix[0][2];
//     int d = matrix[1][0];
//     int e = matrix[1][1];
//     int f = matrix[1][2];
//     int g = matrix[2][0];
//     int h = matrix[2][1];
//     int i = matrix[2][2];

//     int determinant = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

//     return determinant;
// }
// int main()
// {
//     int matrix[3][3]; // = {{1, 0, 0}, {0, 0, 1}, {0, 1, 0}};
//     printf("Enter matrix input\n");

//     for (int i = 1; i <= 3; i++)
//     {
//         for (int j = 1; j <= 3.; j++)
//         {
//             scanf("%f   ", &matrix[i][j]);
//         }
//     }
//     int result = determinant(matrix);

//     printf("The determinant of the matrix is: %d\n", result);

//     return 0;
// }
