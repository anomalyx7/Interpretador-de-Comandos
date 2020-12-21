
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

    
    int PrintFileContent(char* fileName);

    void teste();

#endif