#include <stdio.h>

void create()
{
    FILE *file;
    file = fopen("INPUT.TXT", "r");
    fputs("INDIA IS MY COUNTRY", file);
    // fclose(file);

    int ft, i = 0;

    fseek(file, 0, SEEK_END);
    ft = ftell(file);
    while (i < ft)
    {
        i++;
        fseek(file, -i, SEEK_END);
        printf("%c", fgetc(file));
    }
    fclose(file);
}

int main()
{
    create();
    return 0;
}