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
void rk4(double x0, double y0, double z0, double x1, double y1, double z1, double sigma, double r, double b, double t, double h)
{
    FILE *ptr = NULL;
    ptr = fopen("q10.txt", "w");
    FILE *ptr2 = NULL;
    ptr2 = fopen("q11.txt", "w");
    FILE *ptr3 = NULL;
    ptr3 = fopen("q12.txt", "w");
    FILE *ptr4 = NULL;
    ptr4 = fopen("q4.txt", "w");
    double t0 = 0;
    int n = (int)(t - t0) / h;
    for (int i = 1; i <= n; i++)
    {
        fprintf(ptr, "%.20lf     %.20lf     %.20lf\n", x0, y0, z0);
        fprintf(ptr2, "%.20lf     %.20lf     %.20lf\n", x1, y1, z1);
        double s = sqrt((pow((x1 - x0), 2)) + (pow((y1 - y0), 2)) + (pow((z1 - z0), 2)));
        fprintf(ptr3, "%.20lf     %.20lf\n", t0, s);
        double k1x = h * dxdt(x0, y0, sigma);
        double k1x1 = h * dxdt(x1, y1, sigma);
        double k1y = h * dydt(x0, y0, z0, r);
        double k1y1 = h * dydt(x1, y1, z1, r);
        double k1z = h * dzdt(x0, y0, z0, b);
        double k1z1 = h * dzdt(x1, y1, z1, b);
        double k2x = h * dxdt(x0 + k1x / 2, y0 + k1y / 2, sigma);
        double k2x1 = h * dxdt(x1 + k1x1 / 2, y1 + k1y1 / 2, sigma);
        double k2y = h * dydt(x0 + k1x / 2, y0 + k1y / 2, z0 + k1z / 2, r);
        double k2y1 = h * dydt(x1 + k1x1 / 2, y1 + k1y1 / 2, z1 + k1z1 / 2, r);
        double k2z = h * dzdt(x0 + k1x / 2, y0 + k1y / 2, z0 + k1z / 2, b);
        double k2z1 = h * dzdt(x1 + k1x1 / 2, y1 + k1y1 / 2, z1 + k1z1 / 2, b);
        double k3x = h * dxdt(x0 + k2x / 2, y0 + k2y / 2, sigma);
        double k3x1 = h * dxdt(x1 + k2x1 / 2, y1 + k2y1 / 2, sigma);
        double k3y = h * dydt(x0 + k2x / 2, y0 + k2y / 2, z0 + k2z / 2, r);
        double k3y1 = h * dydt(x1 + k2x1 / 2, y1 + k2y1 / 2, z1 + k2z1 / 2, r);
        double k3z = h * dzdt(x0 + k2x / 2, y0 + k2y / 2, z0 + k2z / 2, b);
        double k3z1 = h * dzdt(x1 + k2x1 / 2, y1 + k2y1 / 2, z1 + k2z1 / 2, b);
        double k4x = h * dxdt(x0 + k3x, y0 + k3y, sigma);
        double k4x1 = h * dxdt(x1 + k3x1, y1 + k3y1, sigma);
        double k4y = h * dydt(x0 + k3x, y0 + k3y, z0 + k3z, r);
        double k4y1 = h * dydt(x1 + k3x1, y1 + k3y1, z1 + k3z1, r);
        double k4z = h * dzdt(x0 + k3x, y0 + k3y, z0 + k3z, b);
        double k4z1 = h * dzdt(x1 + k3x1, y1 + k3y1, z1 + k3z1, b);
        x0 = x0 + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
        x1 = x1 + (k1x1 + 2 * k2x1 + 2 * k3x1 + k4x1) / 6;
        y0 = y0 + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;
        y1 = y1 + (k1y1 + 2 * k2y1 + 2 * k3y1 + k4y1) / 6;
        z0 = z0 + (k1z + 2 * k2z + 2 * k3z + k4z) / 6;
        z1 = z1 + (k1z1 + 2 * k2z1 + 2 * k3z1 + k4z1) / 6;
        t0 = t0 + h;
    }
    fclose(ptr);
    fclose(ptr2);
    fclose(ptr3);
}
int main()
{
    double x0, y0, z0, x1, y1, z1, sigma, r, b, t, h;
    x0 = 10;
    y0 = 1;
    z0 = 100;
    x1 = 10;
    y1 = 1;
    z1 = 100.01;
    sigma = 10;
    r = 99;
    b = 8.0 / 3.0;
    t = 40;
    h = 0.01;
    rk4(x0, y0, z0, x1, y1, z1, sigma, r, b, t, h);
}
