#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void lowertoupper()
{
    FILE *file;
    file = fopen("lowertoupper.txt", "r");

    char content[100];
    // fopen(content, "r");
    if (file != NULL)
    {
        printf("file opened succesfully\n");
        while (fgets(content, 100, file))
        {
            printf("%s", content);
        }
        printf("everything is printed from lowertoupper.txt file\n");
    }
    else
    {
        printf("file not found");
    }
    fclose(file);

    convert(file, content);
}

void convert(FILE *file,const char content)
{
    FILE *dest;
    char ch;
    dest = fopen("convert.tmp", "w");
    if (dest == NULL)
    {
        printf("error: cannot open");
    }
    else
    {
        while (ch = fgetc(file) != EOF)
        {
            if (isupper(ch))
            {
                ch = tolower(ch);
            }
            else if (islower(ch))
            {
                ch = toupper(ch);
            }
            fputc(ch, dest);
        }
        fclose(file);
        fclose(dest);
        remove(content);
        rename("convert.tmp", content);
    }
}

int main()
{
    lowertoupper();

    return 0;
}