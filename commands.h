
#ifndef COMMANDS_H_
#define COMMANDS_H_

    typedef struct _Inputs
    {
        char input[20];

        struct _Inputs *next;
    } Inputs;

    Inputs* ListAppend(Inputs* lst, char* word); //Divides the user input in commands and arguments
    Inputs* ParseInputIntoList(char* string, Inputs *lst); //Inserts command/argument in the list
    Inputs* FreeList(Inputs* lst); //Free list

    


    void PrintFileContent(char* fileName); //Prints the content of a given file
    int CountCharactersInAFile(char* fileName); //Count the characters in a file
    void DeleteFile(char* fileName); //Deletes a file given it's name
    void FileStat(char* fileName); //Prints information of the file system of a chosen file
    void TruncateTwoFiles(char* fOrigin, char* fDest); //Truncate two given Files
    void ListPath(char* path); //List all files and directories on the given path



#endif