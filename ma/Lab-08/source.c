#include <stdio.h>
#include <math.h>

int main()
{
    double A[2][2] = {{1, 0}, {0, 1}}; // the given matrix
    double eigval[2];                  // array to store the eigenvalues
    double eigvec[2][2];               // array to store the eigenvectors
    double norm;                       // variable to store the norm of the eigenvectors
    int i, j, k;

    // Step 1: Compute the characteristic polynomial and solve for eigenvalues
    double det = A[0][0] * A[1][1] - A[0][1] * A[1][0]; // determinant of A
    double tr = A[0][0] + A[1][1];                      // trace of A
    double delta = tr * tr - 4 * det;                   // discriminant of characteristic polynomial
    eigval[0] = (tr + sqrt(delta)) / 2;                 // first eigenvalue
    eigval[1] = (tr - sqrt(delta)) / 2;                 // second eigenvalue

    // Step 2: Compute the eigenvectors corresponding to each eigenvalue
    for (k = 0; k < 2; k++)
    {
        // solve the system of equations (A - λI)x = 0, where λ is the current eigenvalue
        double B[2][2] = {{A[0][0] - eigval[k], A[0][1]}, {A[1][0], A[1][1] - eigval[k]}};
        double detB = B[0][0] * B[1][1] - B[0][1] * B[1][0]; // determinant of B
        eigvec[k][0] = B[1][1] / detB;                       // first component of eigenvector
        eigvec[k][1] = -B[0][1] / detB;                      // second component of eigenvector

        // Step 3: Normalize the eigenvectors
        norm = sqrt(eigvec[k][0] * eigvec[k][0] + eigvec[k][1] * eigvec[k][1]);
        eigvec[k][0] /= norm;
        eigvec[k][1] /= norm;
    }

    // Step 4: Check if the eigenvectors are orthogonal
    double dot = eigvec[0][0] * eigvec[1][0] + eigvec[0][1] * eigvec[1][1];
    if (fabs(dot) < 1e-10)
    {
        printf("The eigenvectors are orthogonal.\n");
    }
    else
    {
        printf("The eigenvectors are not orthogonal.\n");
    }

    // Step 5: Print the results
    printf("The eigenvalues are %lf and %lf.\n", eigval[0], eigval[1]);
    printf("The eigenvectors are (%lf, %lf) and (%lf, %lf).\n", eigvec[0][0], eigvec[0][1], eigvec[1][0], eigvec[1][1]);

    return 0;
}
