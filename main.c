#include "commands.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) 
{   
    Inputs *lst = NULL;
    char command[1000] = " ";

    while (strcmp(command, "Termina") != 0)
    {
        printf(" %c", '%');
        fgets(command, sizeof command, stdin);

        if(command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        
        lst = ParseInputIntoList(command, lst);


        if(strcmp(lst->input, "Mostrar") == 0)
        {
            PrintFileContent(lst->next->input);
        }
        
        if(strcmp(lst->input, "conta") == 0)
        {
            int size = CountCharactersInAFile(lst->next->input);
            printf("Tamanho: %d\n", size);
        }

        if(strcmp(lst->input, "apaga") == 0)
        {
            DeleteFile(lst->next->input);
        }
        
        //Apagar lista
        lst = FreeList(lst);
    }
    
}