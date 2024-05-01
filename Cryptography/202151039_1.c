/* 
        BEGARI UDAY KIRAN
        202151039
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define PLAIN_SPACE 30
#define CIPHER_SPACE 30

int mod_inverse(int a, int m);

char *adjust_plain(char plain[])
{
    char *adjusted_text = (char *)malloc(CIPHER_SPACE * sizeof(char));
    int i = 0;
    int j = 0;

    while (plain[i] != '\0')
    {
        if (plain[i] == plain[i + 1] && plain[i] != '\0')
        {
            adjusted_text[j++] = plain[i++];
            adjusted_text[j++] = 'X';
        }
        else
        {
            adjusted_text[j++] = plain[i++];
        }
    }
    adjusted_text[j] = '\0';

    return adjusted_text;
}

void generate_key_matrix(char key[], char matrix[5][6])
{
    int i, j, k = 0;
    int ascii[ALPHABET_SIZE] = {0};

    for (i = 0; i < strlen(key); i++)
    {
        if (key[i] != 'J')
        {
            ascii[key[i] - 'A'] = 1;
        }
    }

    for (i = 0; i < strlen(key); i++)
    {
        if (key[i] == 'J')
        {
            continue;
        }
        else
        {
            matrix[k / 6][k % 6] = key[i];
            k++;
        }
    }

    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (ascii[i] == 0 && i != ('J' - 'A'))
        {
            matrix[k / 6][k % 6] = i + 'A';
            k++;
        }
    }
}

void playfair_encrypt(char plain[], char matrix[5][6], char cipher[])
{
    int i, j, k = 0;

    for (i = 0; i < strlen(plain); i += 2)
    {
        char char1 = plain[i];
        char char2 = (plain[i + 1] != '\0') ? plain[i + 1] : 'X';

        int row1, col1, row2, col2;

        for (j = 0; j < 5; j++)
        {
            for (k = 0; k < 6; k++)
            {
                if (matrix[j][k] == char1)
                {
                    row1 = j;
                    col1 = k;
                }
                if (matrix[j][k] == char2)
                {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        if (row1 == row2)
        {
            cipher[i] = matrix[row1][(col1 + 1) % 6];
            cipher[i + 1] = matrix[row2][(col2 + 1) % 6];
        }
        else if (col1 == col2)
        {
            cipher[i] = matrix[(row1 + 1) % 5][col1];
            cipher[i + 1] = matrix[(row2 + 1) % 5][col2];
        }
        else
        {
            cipher[i] = matrix[row1][col2];
            cipher[i + 1] = matrix[row2][col1];
        }
    }
    cipher[i] = '\0';
}

void affine_encrypt(char cipher[], char affine_cipher[], int key[])
{
    int i, a_inv;
    for (i = 0; i < strlen(cipher); i++)
    {
        if (cipher[i] >= 'A' && cipher[i] <= 'Z')
        {
            affine_cipher[i] = ((key[0] * (cipher[i] - 'A') + key[1]) % PLAIN_SPACE) + 'A';
        }
        else
        {
            affine_cipher[i] = cipher[i];
        }
    }
    affine_cipher[i] = '\0';
}

void shift_encrypt(char cipher[], char shift_cipher[], int key)
{
    int i;
    for (i = 0; i < strlen(cipher); i++)
    {
        if (cipher[i] >= 'A' && cipher[i] <= 'Z')
        {
            shift_cipher[i] = ((cipher[i] - 'A' + key) % PLAIN_SPACE) + 'A';
        }
        else
        {
            shift_cipher[i] = cipher[i];
        }
    }
    shift_cipher[i] = '\0';
}

void affine_decrypt(char affine_cipher[], char affine_decrypted[], int key[])
{
    int i, a_inv;
    for (i = 0; i < strlen(affine_cipher); i++)
    {
        if (affine_cipher[i] >= 'A' && affine_cipher[i] <= 'Z')
        {
            a_inv = mod_inverse(key[0], PLAIN_SPACE);
            affine_decrypted[i] = (((affine_cipher[i] - 'A' - key[1]) * a_inv + PLAIN_SPACE) % PLAIN_SPACE) + 'A';
        }
        else
        {
            affine_decrypted[i] = affine_cipher[i];
        }
    }
    affine_decrypted[i] = '\0';
}

int mod_inverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

void shift_decrypt(char shift_cipher[], char shift_decrypted[], int key)
{
    int i;
    for (i = 0; i < strlen(shift_cipher); i++)
    {
        if (shift_cipher[i] >= 'A' && shift_cipher[i] <= 'Z')
        {
            shift_decrypted[i] = ((shift_cipher[i] - 'A' - key + PLAIN_SPACE) % PLAIN_SPACE) + 'A';
        }
        else
        {
            shift_decrypted[i] = shift_cipher[i];
        }
    }
    shift_decrypted[i] = '\0';
}

void playfair_decrypt(char cipher[], char matrix[5][6], char plain[])
{
    int i, j, k = 0;

    for (i = 0; i < strlen(cipher); i += 2)
    {
        char char1 = cipher[i];
        char char2 = cipher[i + 1];

        int row1, col1, row2, col2;

        for (j = 0; j < 5; j++)
        {
            for (k = 0; k < 6; k++)
            {
                if (matrix[j][k] == char1)
                {
                    row1 = j;
                    col1 = k;
                }
                if (matrix[j][k] == char2)
                {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        if (row1 == row2)
        {
            plain[i] = matrix[row1][(col1 - 1 + 6) % 6];
            plain[i + 1] = matrix[row2][(col2 - 1 + 6) % 6];
        }
        else if (col1 == col2)
        {
            plain[i] = matrix[(row1 - 1 + 5) % 5][col1];
            plain[i + 1] = matrix[(row2 - 1 + 5) % 5][col2];
        }
        else
        {
            plain[i] = matrix[row1][col2];
            plain[i + 1] = matrix[row2][col1];
        }
    }
    plain[i] = '\0';
}

int main()
{
    char input_text[] = "HELLO WORLD";
    char *adjusted_input_text;

    char key[] = "SOMEKEY";
    char matrix[5][6];

    char playfair_cipher[CIPHER_SPACE];
    char affine_cipher[CIPHER_SPACE];
    char shift_cipher[CIPHER_SPACE];

    char shift_decryption[CIPHER_SPACE];
    char affine_decryption[CIPHER_SPACE];
    char playfair_decryption[CIPHER_SPACE];

    int affine_key[] = {11, 15};
    int shift_key = 6;

    printf("Plain text: %s\n", input_text);

    adjusted_input_text = adjust_plain(input_text);
    printf("Adjusted plaintext: %s\n", adjusted_input_text);

    generate_key_matrix(key, matrix);
    printf("Key Matrix:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    playfair_encrypt(adjusted_input_text, matrix, playfair_cipher);
    printf("Playfair-Ciphertext : %s\n", playfair_cipher);

    affine_encrypt(playfair_cipher, affine_cipher, affine_key);
    printf("Affine-Ciphertext : %s\n", affine_cipher);

    shift_encrypt(affine_cipher, shift_cipher, shift_key);
    printf("Shift-Ciphertext (): %s\n", shift_cipher);

    shift_decrypt(shift_cipher, shift_decryption, shift_key);
    printf("Deciphertext (Shift): %s\n", shift_decryption);

    affine_decrypt(shift_decryption, affine_decryption, affine_key);
    printf("Deciphertext (Affine): %s\n", affine_decryption);

    playfair_decrypt(affine_decryption, matrix, playfair_decryption);
    printf("Deciphertext (Playfair): %s\n", playfair_decryption);

    return 0;
}
