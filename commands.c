#include "commands.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PrintFileContent(char* fileName)
{
    char buffer[21];
    int fd, didRead;
    
    fd = open(fileName, O_RDONLY);

    if(fd < 0)
    {
        perror("There was an error trying to open the file.");
        exit(1);
    }


    didRead = read(fd, buffer, sizeof(buffer) - 1);
    
    while(didRead > 0)
    {
        buffer[didRead] = '\0';
        write(1, buffer, sizeof(buffer));
    
        didRead = read(fd, buffer, sizeof(buffer) - 1);    
    }

    if(didRead == -1)
    {
        perror("There was an error trying to read the file.");
    }
    else    // didRead = 0
    {
        write(1, "\nFim do ficheiro\n", sizeof("\nFim do ficheiro\n"));
    }

    close(fd);
    
    return 1; 
}

int CountCharactersInAFile(char* fileName)
{
    char buffer[21];
    int fd, didRead;
    int size = 0;

    fd = open(fileName, O_RDONLY);

    if(fd < 0)
    {
        perror("There was an error trying to open the file.");
        exit(1);
    }

    didRead = read(fd, buffer, sizeof(buffer) - 1);

    while(didRead > 0)
    {
        buffer[didRead] = '\0';
    
        for(int i = 0; i < strlen(buffer); i++)
        {
            if(buffer[i] != '\n' && buffer[i] != ' ')
            {              
                size++;
            }
        }
        
        didRead = read(fd, buffer, sizeof(buffer) - 1);          
    }

    if(didRead == -1)
    {
        perror("There was an error trying to read the file.");
    }

    close(fd);

    return size;
}

void DeleteFile(char* fileName)
{
    if(unlink(fileName) == -1)
    {
        perror("File doesn't exist!");
    }
}












void teste()
{
    puts("testado");
}

Inputs* ListAppend(Inputs* lst, char* word)
{
    if(lst) lst->next = ListAppend(lst->next, word);
    else
    {
        lst = (Inputs*)malloc(sizeof(Inputs));
        strcpy(lst->input, word);
        lst->next = NULL;
    }
    return lst;
}

Inputs* ParseInputIntoList(char* string, Inputs *lst)
{
    int i = 0, j = 0;
    char word[20] = " ";

    while(i <= strlen(string))
    {
        if(string[i] == ' ' || string[i] == '\0')
        {
            lst = ListAppend(lst, word);
            j = 0;
        }
        else
        {
            word[j] = string[i];
            j++;
        }
        i++;
    }

    return lst;
}

Inputs* FreeList(Inputs* lst)
{
    if(lst) lst = FreeList(lst->next);
    else
    {
        free(lst);
        return lst;
    }
}
