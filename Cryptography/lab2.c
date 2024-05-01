// ----------------------------------------------------------------//
//-------------BEGARI UDAY KIRAN ---ID---> 202151039---------------//

#include <stdio.h>

// Function to perform the Feistel network round
unsigned int feistelRound(unsigned int data, unsigned int key) {
    // Example: XOR operation as a simple Feistel round
    return data ^ key;
}

// Function to perform the Feistel network
unsigned long long feistelNetwork(unsigned long long plaintext, unsigned int key, int numRounds) {
    unsigned int L, R, temp;
    
    // Initial permutation (if needed)
    // Example: L = (plaintext >> 32);
    L = (unsigned int)(plaintext >> 32);
    R = (unsigned int)plaintext;

    for (int i = 0; i < numRounds; ++i) {
        // Save the old value of R
        temp = R;
        
        // Feistel function (in this example, just XOR)
        R = L ^ feistelRound(R, key);

        // L becomes the old value of R
        L = temp;
    }

    // Final permutation (if needed)
    // Example: Result = ((unsigned long long)R << 32) | L;
    return ((unsigned long long)R << 32) | L;
}

int main() {
    unsigned long long plaintext = 0x0123456789ABCDEF; // 64-bit plaintext
    char alplabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,?;";
    unsigned int key = 0x0FEDCBA9; // 32-bit key
    int numRounds = 16;

    // Perform Feistel network 
    unsigned long long ciphertext = feistelNetwork(plaintext, key, numRounds);

    // Print results
    printf("Plaintext: %016llX\n", plaintext);
    printf("Ciphertext: %016llX\n", ciphertext);

    return 0;
}

void initializePlain(char plainText[])
{
    for (int i = 0; i < plainText[i] != '\0'; i++)
    {

    }
}