
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 30                   // Number of sampling points
#define f(x) (sqrt(1 - x * x)) // Function for which integral is calculated

// Trapezoidal Rule
double Trap_int(double a, double b, int n)
{
    int i;
    long x[n + 1], y[n + 1], h, s;
    h = (b - a) / n;
    for (i = 0; i <= n; i++)
    {
        x[i] = a + i * h;
        y[i] = f(x[i]);
    }
    s = 0;
    for (i = 0; i < n; i++)
        s = s + (y[i] + y[i + 1]) * h / 2;
    return s;
}

// Simpson's 1/3 Rule
double Simp13_int(double a, double b, int n)
{
    int i;
    long x[n + 1], y[n + 1], h, s;
    h = (b - a) / n;
    for (i = 0; i <= n; i++)
    {
        x[i] = a + i * h;
        y[i] = f(x[i]);
    }
    s = 0;
    for (i = 0; i < n; i++)
    {
        s = s + (y[i] + 4 * y[i + 1] + y[i + 2]) * h / 6;
    }
    return s;
}

// Simpson's 3/8 Rule
double Simp38_int(double a, double b, int n)
{
    int i;
    long x[n + 1], y[n + 1], h, s;
    h = (b - a) / n;
    for (i = 0; i <= n; i++)
    {
        x[i] = a + i * h;
        y[i] = f(x[i]);
    }
    s = 0;
    for (i = 0; i < n; i++)
    {
        s = s + (y[i] + 3 * y[i + 1] + 3 * y[i + 2] + y[i + 3]) * h * 3 / 8;
    }
    return s;
}

// Main Function
int main()
{
    double a = -10, b = 10;
    int n;
    long Trap_int_val, Simp13_int_val, Simp38_int_val;

    printf("\n\n");

    // Trapezoidal Rule
    printf("Trapezoidal Rule\n");
    printf("n\tIntegral Value\n");
    for (n = 2; n <= N; n = n + 2)
    {
        Trap_int_val = Trap_int(a, b, n);
        printf("%d\t%lf\n", n, Trap_int_val);
    }

    // Simpson's 1/3 Rule
    printf("\nSimpson's 1/3 Rule\n");
    printf("n\tIntegral Value\n");
    for (n = 3; n <= N; n = n + 3)
    {
        Simp13_int_val = Simp13_int(a, b, n);
        printf("%d\t%lf\n", n, Simp13_int_val);
    }

    // Simpson's 3/8 Rule
    printf("\nSimpson's 3/8 Rule\n");
    printf("n\tIntegral Value\n");
    for (n = 4; n <= N; n = n + 4)
    {
        Simp38_int_val = Simp38_int(a, b, n);
        printf("%d\t%lf\n", n, Simp38_int_val);
    }

    printf("\n\n");

    return 0;
}
