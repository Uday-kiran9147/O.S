#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double dxdt(double x, double y, double sigma)
{
    return sigma * (y - x);
}
double dydt(double x, double y, double z, double r)
{
    return x * (r - z) - y;
}
double dzdt(double x, double y, double z, double b)
{
    return x * y - b * z;
}
void rk4(double x0, double y0, double z0, double sigma, double r, double b, double t, double h)
{
    FILE *ptr = NULL;
    ptr = fopen("q1.txt", "w");
    FILE *ptr2 = NULL;
    ptr2 = fopen("q2.txt", "w");
    FILE *ptr3 = NULL;
    ptr3 = fopen("q3.txt", "w");
    FILE *ptr4 = NULL;
    ptr4 = fopen("q4.txt", "w");
    double t0 = 0;
    int n = (int)(t - t0) / h;
    for (int i = 1; i <= n; i++)
    {
        fprintf(ptr, "%.20lf     %.20lf     %.20lf\n", x0, y0, z0);
        double k1x = h * dxdt(x0, y0, sigma);
        double k1y = h * dydt(x0, y0, z0, r);
        double k1z = h * dzdt(x0, y0, z0, b);
        double k2x = h * dxdt(x0 + k1x / 2, y0 + k1y / 2, sigma);
        double k2y = h * dydt(x0 + k1x / 2, y0 + k1y / 2, z0 + k1z / 2, r);
        double k2z = h * dzdt(x0 + k1x / 2, y0 + k1y / 2, z0 + k1z / 2, b);
        double k3x = h * dxdt(x0 + k2x / 2, y0 + k2y / 2, sigma);
        double k3y = h * dydt(x0 + k2x / 2, y0 + k2y / 2, z0 + k2z / 2, r);
        double k3z = h * dzdt(x0 + k2x / 2, y0 + k2y / 2, z0 + k2z / 2, b);
        double k4x = h * dxdt(x0 + k3x, y0 + k3y, sigma);
        double k4y = h * dydt(x0 + k3x, y0 + k3y, z0 + k3z, r);
        double k4z = h * dzdt(x0 + k3x, y0 + k3y, z0 + k3z, b);
        x0 = x0 + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
        y0 = y0 + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;
        z0 = z0 + (k1z + 2 * k2z + 2 * k3z + k4z) / 6;
        t0 = t0 + h;
    }
    fclose(ptr);
    fclose(ptr2);
    fclose(ptr3);
}
int main()
{
    double x0, y0, z0, sigma, r, b, t, h;
    printf("Enter the value of x0 : \n");
    scanf("%lf", &x0);
    printf("Enter the value of y0 : \n");
    scanf("%lf", &y0);
    printf("Enter the value of z0 : \n");
    scanf("%lf", &z0);
    printf("Enter the value of sigma : \n");
    scanf("%lf", &sigma);
    printf("Enter the value of r : \n");
    scanf("%lf", &r);
    printf("Enter the value of b : \n");
    scanf("%lf", &b);
    printf("Enter the time limit:\n");
    scanf("%lf", &t);
    printf("Enter the value of h (increments of time) \n");
    scanf("%lf", &h);
    rk4(x0, y0, z0, sigma, r, b, t, h);
}
