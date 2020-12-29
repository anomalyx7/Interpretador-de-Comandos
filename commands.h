
#ifndef COMMANDS_H_
#define COMMANDS_H_

    typedef struct _Inputs
    {
        char input[20];

        struct _Inputs *next;
    } Inputs;

    Inputs* ListAppend(Inputs* lst, char* word);
    Inputs* ParseInputIntoList(char* string, Inputs *lst);
    Inputs* FreeList(Inputs* lst);

    



    void PrintFileContent(char* fileName);
    int CountCharactersInAFile(char* fileName);
    void DeleteFile(char* fileName);
    void FileStat(char* fileName);
    void TruncateTwoFiles(char* fOrigin, char* fDest);
    void ListPath(char* path);

    void teste();

#endif