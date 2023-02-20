#include <stdio.h>

void createANDwrite()
{
    FILE *file;
    file = fopen("new1.txt", "w");
    fputs("I am adding new texchist in the file every time when writing in new file it starts writing from the fscratch", file);
    fclose(file);

    char ch[1000];
    file = fopen("new1.txt", "r");
    if (file != NULL)
    {
        printf("Reading file\n");
        while (fgets(ch, 1000, file)) // fscan() OR fgets().
        {
            printf("%s", ch);
        }
    }
    fclose(file);
}

int main()
{
    createANDwrite();
    return 0;
}