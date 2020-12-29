#include "commands.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char* argv[]) 
{   
    Inputs *lst = NULL; //create a list to store both the command and the arguments
    char command[1000];
    int pid;

    //Enters and stays in the loop until the user typer "Termina"
    while (strcmp(command, "Termina") != 0)
    {
        //Gets the input from the user
        printf(" %c", '%');
        fgets(command, sizeof command, stdin);

        if(command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        
        //Separates the command from the arguments and stores it on a list
        //The first position of the list is always the command and the rest
        //are arguments 
        lst = ParseInputIntoList(command, lst);

        if(strcmp(lst->input, "mostrar") == 0)//Enters if the user input command is equal to "mostrar"
        {
            pid = fork(); //Creates a fork
            //The child process enters and calls a function to print
            //the content of the file asked by the user into the terminal/console
            if(pid == 0) 
                PrintFileContent(lst->next->input);
            //The parent process will wait until the child process finnishes it's job 
            //since it's writing to the terminal/console
            else 
                wait(1);     
        }
        else if(strcmp(lst->input, "conta") == 0)//Enters if the user input command is equal to "conta"
        {
            int size = 0;

            pid = fork(); //Creates a fork
            
            //The child process enters the if statement and calls a function
            //to count the amount of characters in a file
            if(pid == 0)
            {
                size = CountCharactersInAFile(lst->next->input);
                printf("Tamanho: %d\n", size);
            }
            //The parent process will wait until the child process finnishes it's job
            //since it will write to the terminal/console
            else
                wait(1);
        }
        else if(strcmp(lst->input, "apaga") == 0)//Enters if the user input command is equal to "apaga"
        {
            pid = fork(); //Creates a fork

            //The child process enters the if statement and calls a function to
            //delete a file asked by the user
            if(pid == 0)
                DeleteFile(lst->next->input);
            //The parent process will wait until the child finnished it's job since there's
            //a chance of the user in the next command tries to do something with the file 
            //that is being deleted and that could cause problems
            else
                wait(1);
        }
        else if(strcmp(lst->input, "informa") == 0)
        {
            pid = fork(); //Creates a fork

            //The child process enters the if statement and calls a function to
            //print some information about a file
            if(pid == 0) //
                FileStat(lst->next->input);
            //The parent process will wait for the child to finnish it's job since
            //it will print to the terminal/console
            else
                wait(1);
        }
        else if(strcmp(lst->input, "acrescente") == 0)//Enters if the user input command is equal to "acrescente"
        {
            pid = fork(); //Creates a fork

            //The child process enters the if statement and calls a function to
            //append the content of a file to another
            if(pid == 0)
                TruncateTwoFiles(lst->next->input, lst->next->next->input);
            //The parent process will wait until the child finnishes it's job since there's a chance
            //that in the next command the user will use one of the files in use and that could cause
            //problems
            else
                wait(1);
        }
        
        //Erases the list from the parent process after each command executed
        if(pid != 0)
            lst = FreeList(lst);

        //End the life of the child process
        if(pid == 0)
            //strcmp(command, "Termina\n");
            exit(1);
    }

    return 0;
}