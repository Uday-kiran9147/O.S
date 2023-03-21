#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the function to integrate
double f(double x)
{
    return pow(x, 2) - 3 * x + 2;
}

// Define the trapezoidal rule
double trapezoidal(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        sum += 2 * f(x);
    }
    return (h / 2) * sum;
}

// Define Simpson's 1/3 rule
double simpson13(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum1 = 0, sum2 = 0;
    for (int i = 1; i < n; i += 2)
    {
        double x = a + i * h;
        sum1 += f(x);
    }
    for (int i = 2; i < n; i += 2)
    {
        double x = a + i * h;
        sum2 += f(x);
    }
    return (h / 3) * (f(a) + 4 * sum1 + 2 * sum2 + f(b));
}

// Define Simpson's 3/8 rule
double simpson38(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum1 = 0, sum2 = 0;
    for (int i = 1; i < n; i += 3)
    {
        double x = a + i * h;
        sum1 += f(x);
    }
    for (int i = 2; i < n; i += 3)
    {
        double x = a + i * h;
        sum2 += f(x);
    }
    return (3 * h / 8) * (f(a) + 3 * sum1 + 3 * sum2 + 2 * f(b));
}

int main()
{
    // Define the integral limits
    double a = -10;
    double b = 10;

    // Define the exact value of the integral (for comparison)
    double exact = 666.6666666667;

    // Define a range of number of sampling points to test
    int n_max = 100;
    int n_range[n_max - 1];
    for (int i = 0; i < n_max - 1; i++)
    {
        n_range[i] = i + 2;
    }

    // Initialize arrays to store the absolute and relative errors for each method and each n
    double T_error[n_max - 1], T_rel_error[n_max - 1], S13_error[n_max - 1], S13_rel_error[n_max - 1], S38_error[n_max - 1], S38_rel_error[n_max - 1];

    // Compute the errors for each method and each n
    for (int i = 0; i < n_max - 1; i++)
    {
        int n = n_range[i];
        double T_approx = 9;
    }
}
