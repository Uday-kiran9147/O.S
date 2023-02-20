#include <stdio.h>

void fileopen()
{
    // declearing file pointer.
    FILE *file;

    file = fopen("test.txt", "r"); //  (" r ") that means read.
    // to open a file in read mode we need to make sure the file is present in the location or directory we are opening.

    char content[1000]; // stores the content of the file in characters.

    if (file != NULL)
    {
        printf(" File open successfully");
        while (fgets(content, 1000, file))
        {
            // fgets reads the content of the file and stores it in the "content" variable we decleared.
            printf("%s", content);
        }
    }
    else
    {
        printf("file open failed");
    }
    fclose(file);
}

void write()
{ // To write content to file.
    FILE *file2;
    file2 = fopen("NewFile.txt", "w");       // fopen creates a new file if not exists already.
    fputs("I am creating new file ", file2); // fputs to add content to the file
    fputs("\nC programming series  on pointer and file handling", file2);

    fclose(file2);
}

void assignment()
{
    FILE *ptr;
    ptr = fopen("Newassignment.txt", "w"); // (" w ") is for writing content the file

    fputs(" C is a fun programming language.", ptr);
    fputs("\n And, I am using  C language", ptr);

    fclose(ptr);
}

void assignmentfilereading()
{

    FILE *fileread;
    fileread = fopen("Newassignment.txt", "r");

    char assignmentcontent[1000];

    if (fileread != NULL)
    {
        while (fgets(assignmentcontent, 1000, fileread)) // fscan() OR fgets().
        {
            printf("%s", assignmentcontent);
        }
    }
    else
    {
        printf(" file doesnot exist");
    }

    fclose(fileread);
}

int main()
{
    fileopen();
    write();
    assignment();
    assignmentfilereading();

    return 0;
}