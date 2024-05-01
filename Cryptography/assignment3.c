#include <stdio.h>

unsigned int F(unsigned int x) {
    // This is a dummy round function. In a real Feistel Network, this would be a cryptographic function.
    return (x ^ 12345);
}

void feistel(unsigned int *L, unsigned int *R, unsigned int num_rounds) {
    for (unsigned int i = 0; i < num_rounds; i++) {
        unsigned int temp = *R;
        *R = *L ^ F(*R);
        *L = temp;
    }
}

int main() {

    unsigned int L = 0x12345678;
    unsigned int R = 0x9abcdef0;
    unsigned int num_rounds = 16;

    printf("Before encryption: L=%08x, R=%08x\n", L, R);
    feistel(&L, &R, num_rounds);
    printf("After encryption: L=%08x, R=%08x\n", L, R);

    // To decrypt, we just run the Feistel Network again
    feistel(&L, &R, num_rounds);
    printf("After decryption: L=%08x, R=%08x\n", L, R);

    return 0;
}