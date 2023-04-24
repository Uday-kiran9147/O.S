#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char character;

    // open input file for reading
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file!");
        return 1;
    }

    // open output file for writing
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file!");
        return 1;
    }

    // read input file character by character and write to output file
    while ((character = fgetc(inputFile)) != EOF) {
        fputc(character, outputFile);
    }

    // close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully!");

    return 0;
}
