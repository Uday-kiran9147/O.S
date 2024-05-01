#include <stdio.h>
#include <stdlib.h>

// Structure to represent a point on the elliptic curve
typedef struct {
  long long x;
  long long y;
} point;

// Function to add two points on the curve (replace with efficient algorithm)
point add_points(point *p1, point *p2, long long p_prime, long long a) {
  point p3;
  if (p1->x == p2->x && p1->y != p2->y) {
    // Points are negatives of each other (infinite point)
    p3.x = 0;
    p3.y = 1;
    return p3;
  }

  long long lambda;
  if (p1->x == p2->x) {
    // Handle point doubling (replace with specific formula)
    lambda = (3 * p1->x * p1->x + a) % p_prime;
  } else {
    lambda = ((p2->y - p1->y) * ((p2->x - p1->x) % p_prime)) % p_prime;
  }

  long long x3 = (lambda * lambda - p1->x - p2->x) % p_prime;
  long long y3 = (lambda * (p1->x - x3) - p1->y) % p_prime;

  p3.x = x3;
  p3.y = (y3 + p_prime) % p_prime; // Ensure y3 is positive
  return p3;
}

int main() {
  // Elliptic curve parameters (replace with actual values)
  long long p_prime = 1021;
  long long a = 0;
  long long b = 7;

  // Two points on the curve
  point p1 = {2, 5};
  point p2 = {3, 8};

  // Add the points
  point p3 = add_points(&p1, &p2, p_prime, a);

  printf("Point 1: (%lld, %lld)\n", p1.x, p1.y);
  printf("Point 2: (%lld, %lld)\n", p2.x, p2.y);
  printf("Sum: (%lld, %lld)\n", p3.x, p3.y);

  return 0;
}
