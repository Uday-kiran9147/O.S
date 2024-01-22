#include <stdio.h>

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

void encrypt(int a, int b, char message[])
{
    for (int i = 0; message[i] != '\0'; i++)
    {
        if (message[i] != ' ')
        {
            message[i] = (char)((((a * (message[i] - 'A')) + b) % 26) + 'A');
        }
    }
}

void decrypt(int a, int b, char cipher[])
{
    int a_inv = modInverse(a, 26);
    for (int i = 0; cipher[i] != '\0'; i++)
    {
        if (cipher[i] != ' ')
        {
            cipher[i] = (char)(((a_inv * ((cipher[i] + 'A' - b)) % 26)) + 'A');
        }
    }
}

int main()
{
    char message[] = "HELLO";
    int a = 5, b = 8;

    encrypt(a, b, message);
    printf("Encrypted message: %s\n", message);

    decrypt(a, b, message);
    printf("Decrypted message: %s\n", message);

    return 0;
}