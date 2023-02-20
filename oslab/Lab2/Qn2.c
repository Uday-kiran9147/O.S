#include <stdio.h>

void createfile()
{
    FILE *file;
    file = fopen("Append.txt", "w");
    fputs(" This is Default text.",file);

    file = fopen("Append.txt", "a");
    fputs("\nnew  File Appended",file);
}

int main()
{
    createfile();

    return 0;
}