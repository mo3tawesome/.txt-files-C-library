#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char returns[50];
void printfile(char filename[50])  // this function can print any file with the entered name + .txt
{
    FILE *fptr; // file pointer
    fptr = fopen(filename,"r"); // open the file for read
    const size_t line_size = 250; /// assumes max line size of 250 chars
    char* line = malloc(line_size); //dynamic allocation of a string to hold the line of mac length
    while (fgets(line, line_size, fptr) != NULL)    //while there are still lines to get, get the line
    {
        printf("%s",line); //print the line
    }
    free(line); //free the string allocated from the memory
    fclose(fptr); // close the file
}

char* searchFile1(char filename[50], char keyword[50]) //searches for any keyword in any file
{

    FILE *fptr;
    fptr = fopen(filename,"r"); // open the file for read
    const size_t line_size = 250; ///assumed line size
    char* line = malloc(line_size); //allocation
    while (fgets(line, line_size, fptr) != NULL)    //get the line
    {
        char *ret;
        ret = strstr(line, keyword); // check if the line has the keyword
        if (ret != NULL)
        {
            strcpy(returns,line); //copy the line to returns if it has the keyword
        }
    }
    free(line); // free the dynamic allocation
    fclose(fptr); // close the file
    return returns; // return the line
}

char* searchFile2(char filename[50], char keyword1[50], char keyword2[50]) // get a line containing two keywords from any file
{
    int FLAAAG =0;
    FILE *fptr;
    fptr = fopen(filename,"r"); // open the file for read
    const size_t line_size = 250; /// assumed line size of 250
    char* line = malloc(line_size);
    char* output = malloc(line_size); // variable to hold the function output
    while (fgets(line, line_size, fptr) != NULL)    //get the line
    {
        char *ret1;
        ret1 = strstr(line, keyword1); // check if the line has the keyword1
        char *ret2;
        ret2 = strstr(line, keyword2); // check if the line has the keyword2
        if (ret1 != NULL && ret2 != NULL) // if both keywords are found in a line
        {
            strcpy(output, line);  // put that line in the output variable
            FLAAAG = 1;

        }
    }
    free(line);
    fclose(fptr);
    if(FLAAAG ==1){return output;}
    else{return "s";}

}
void modifyFile(char filename[50], char lineToRemove[250], char lineToAdd[250]) // removes, adds or modify lines in a file
{
    FILE *fptr;
    fptr = fopen(filename,"r"); // open for read
    int deleteFlag=0; // flag for checking if there's something to delete
    const size_t line_size = 250; ///assumed max line size of 250 chars
    char* line = malloc(line_size); // dynamic allocation of the line
    const size_t file_size = 5000; ///assumed max file size of 250 chars
    char* file = malloc(file_size);
    file[0] = '\0'; // remove anything in the string that will hold the file
    while (fgets(line, line_size, fptr) != NULL)    //get the line
    {
        char *ret; // variable to hold the line to remove if it exists (holds null if it doesn't)
        ret = strstr(line, lineToRemove); // check if the line exists
        if (ret != NULL)
        {
            strcat(file, lineToAdd); //add the line to add in its place
            strcat(file, "\n"); //add a new line
            deleteFlag=1; // indicate that deletion has happened
        }
        else  //fill the rest of the file as it is
        {
            strcat(file, line);
        }
    }
    if (deleteFlag!=1)  // if there was nothing to remove
    {
        strcat(file, lineToAdd); // add the new line at the end
        strcat(file, "\n");
    }
    free(line); //free allocation
    fclose(fptr); //close file

    fptr = fopen(filename,"w"); // open the file for write (deletes what's already in the file)
    int w =0; // loop counter
    int len = strlen(file); //get file length
    for(w=0; w<len; w++)
    {
        fprintf(fptr,"%c",file[w]);//print the file
    }
    fclose(fptr); //close file

}
