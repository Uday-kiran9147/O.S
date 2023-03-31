#include <math.h>
#include <stdio.h>

int main()
{
    double A[2][2];
    double lambda1, lambda2;
    double x1[2], x2[2];
    double norm1, norm2;
    double dot_product;

    printf("Enter the elements of the 2x2 matrix A:\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }

    lambda1 = (A[0][0] + A[1][1] + sqrt((A[0][0] + A[1][1]) * (A[0][0] + A[1][1]) - 4 * (A[0][0] * A[1][1] - A[0][1] * A[1][0]))) / 2;
    lambda2 = (A[0][0] + A[1][1] - sqrt((A[0][0] + A[1][1]) * (A[0][0] + A[1][1]) - 4 * (A[0][0] * A[1][1] - A[0][1] * A[1][0]))) / 2;

    x1[0] = A[0][1];
    x1[1] = lambda1 - A[0][0];
    x2[0] = A[0][1];
    x2[1] = lambda2 - A[0][0];

    norm1 = sqrt(x1[0] * x1[0] + x1[1] * x1[1]);
    norm2 = sqrt(x2[0] * x2[0] + x2[1] * x2[1]);
    x1[0] = x1[0] / norm1;
    x1[1] = x1[1] / norm1;
    x2[0] = x2[0] / norm2;
    x2[1] = x2[1] / norm2;

    dot_product = x1[0] * x2[0] + x1[1] * x2[1];
    if (fabs(dot_product) < 1e-6)
    {
        // printf("The eigenvectors are orthogonal.\n");
    }
    else
    {
        // printf("The eigenvectors are not orthogonal.\n");
    }

    printf("The eigenvalues of A are \n%.2f and %.2f.\n", lambda1, lambda2);
    // printf("The corresponding eigenvectors are \n(%.3f, %.2f) and (%.3f, %.3f).\n", x1[0], x1[1], x2[0], x2[1]);

    return 0;
}