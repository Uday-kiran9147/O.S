// square multiplier
#include <stdio.h>

long squareMultiply(int a, int x, int p)
{
    long result = 1;
    while (x > 0)
    {
        if (x % 2 == 1)
        {
            result = (result * a) % p;
        }
        a = (a * a);
        x = x >> 1;
    }
    return result;
}

// diffie key exchange
int diffieHellman(int g, int a, int b, int p)
{
    int A = squareMultiply(g, a, p);
    int B = squareMultiply(g, b, p);
    int keyA = squareMultiply(B, a, p);
    int keyB = squareMultiply(A, b, p);
    if (keyA == keyB)
    {
        return keyA;
    }
    return -1;
}
// g is a generator

// alice g^a --> a
// bob g^b --> b

// alice g^b^a
// bob g^a^b

// perform rsa encryption
long rsaEncrypt(int p, int q, int e, int m)
{
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int d = 0;
    for (int i = 1; i < n; i++)
    {
        if ((e * i) % phi == 1)
        {
            d = i;
            break;
        }
    }
    long c = squareMultiply(m, e, n);
    return c;
}

int main()
{
    int a = 26;
    int x = 6;
    int p = 31;
    long result = squareMultiply(a, x, p);
    printf("Result: %ld\n", result);

    // diffie
    int g = 2;
    int a1 = 3;
    int b1 = 5;
    int p2 = 23;
    int key = diffieHellman(g, a1, b1, p2);
    printf("Key: %d\n", key);

    int p1 = 61;
    int q1 = 53;
    int e1 = 17;
    int m1 = 65;
    long c1 = rsaEncrypt(p1, q1, e1, m1);
    printf("Encrypted message: %ld\n", c1);
    return 0;
}

// diff key exchange

// (((g^b)^a)^g)^a mod p
// g^(ab) mod p

// g = (Z,*) mod p

// RSA Enc

// n = p*q
// phi(n) = (p-1)(q-1)

// for (e=1; e<n; e++) {
//    if (gcd(e, phi(n)) == 1) {
//       return e;
//    }
// }

// ext euclid algo (e, phi(n)) = d
// x = e^d mod n
// c = x^e mod n