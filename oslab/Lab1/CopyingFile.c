#include <stdio.h>

void copyFile()
{
    FILE *SOURCE;           // declearing source file
    FILE *DESTINATION;  // declearing destination file

    char sourcePath[1000];          // characher ARRAY[] (sourcePath) stores the source-content of the file.
    char destinationPath[1000];   // characher ARRAY[] (destinationPath) stores the destination-content.

    char ch;   //character ch to copy the characters from the source file and pastes in destination file.

    SOURCE = fopen("new.txt", "r");                   
    DESTINATION = fopen("newdest.txt", "w");     // open/creates destination file  " w " is for writing content.

    if (SOURCE == NULL || DESTINATION == NULL)
    {
        printf("File Does not exist");
    }

    else
    {

        ch = fgetc(SOURCE);   //copies each character from source file.
        while (ch != EOF)
        {
            fputc(ch, DESTINATION);         // copying to destination.

            ch = fgetc(SOURCE);                // after copying to destination copy another character from the file till file is completely copied.

            /* code */
        }
        printf("\nfiles copied successfully");

        fclose(SOURCE);
        fclose(DESTINATION);
    }
}

void add_to_newfile(){
    FILE *file;
    file=fopen("new.txt", "w"); // ( " w " ) to write and edit the file.


    fputs("new 1st line is added to file ", file);   // function puts() helps us to add content to the file.
    fputs("\nnew 2st line is added to file ", file);
    printf("Line added successfully");
    fclose(file);   // it is good practice to close every file after usage.

}
    int main()
    {
        // FILE *p;
        // p=fopen("new.txt","w");

        add_to_newfile();
        copyFile();
        return 0;
    }