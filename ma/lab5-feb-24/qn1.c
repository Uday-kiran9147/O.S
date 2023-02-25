#include <stdio.h>
#include <math.h>

int main()
{
    float x[4] = {654, 658, 659, 661};
    float y[4] = {2.8156, 2.8182, 2.8189, 2.8202};
    double z = 656;
    double p, q, sum1 = 0, sum2 = 0;
    int i, j;

    // Newton divided difference interpolation
    for (i = 0; i < 3; i++)
    {
        /* The divided differences are used to calculate the coefficients of the polynomial */
        p = y[i];
        q = 1;
        for (j = 0; j < 3; j++)
        {
            if (i != j)
            {
                q = (z - x[j]); // x-x[0] x-x[1] x-x[]
                p = (y[i] - y[j]) / q + p;
            }
        }
        sum1 = p;
    }

    printf("\n\nThe value of log 656 using Newton divided difference interpolation: %f", sum1);

    // Lagrange interpolation
    for (i = 0; i < 3; i++)
    {
        q = 1;
        for (j = 0; j < 3; j++)
        {
            /* inner loop iterates through each other data point to calculate the Lagrange basis polynomials. */
            if (i != j)
            {
                q = (z - x[j]) * q;
                p = (z - x[j]) / (x[i] - x[j]);
            }
        }
        sum2 = sum2 + (y[i] * p);
    }

    printf("\nThe value of log 656 using Lagrange interpolation: %f\n", sum2);

    // Comment upon accuracy
    // printf("The two results agree upto 3 decimal points, hence the accuracy is good.\n");

    return 0;
}