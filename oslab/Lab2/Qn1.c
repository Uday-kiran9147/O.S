#include <stdio.h>

void createANDwrite()
{
    FILE *file;
    //writing to file
    file = fopen("new1.txt", "w");
    fputs("I am adding new text in the file every time when writing in new file it starts writing from the scratch", file);
    fclose(file);
    //reading from file
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