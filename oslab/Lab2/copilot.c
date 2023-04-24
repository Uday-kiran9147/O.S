#include <stdio.h>

void createFile(char *str)
{
    FILE *fp;
    fp = fopen("file.txt", "w");
    fputs("uday", fp);
    fprintf(fp, "%s", str);

    fclose(fp);
}
int main()
{
    char buf[1024];
    createFile(&buf);
    return 0;
}

// write a function that adds two numbers and returns the result
int add(int a, int b)
{
    return a + b;
}
// write a function that swaps two numbers and returns the result
int swap(int a, int b)
{
    int temp = a;
    a = b;               
    b = temp;
    return a;
}
// write a function that creates a file.txt and writes a string to it

