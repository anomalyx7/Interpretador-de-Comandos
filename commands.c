#include "commands.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h> 

//Prints the content of a given file
void PrintFileContent(char* fileName)
{
    char buffer[21]; 
    int fd, didRead;
    
    //Opens the file in read only mode
    fd = open(fileName, O_RDONLY);

    //If there was any error trying to open the file
    //prints an error message and closes the program
    if(fd < 0)
    {
        perror("The file doesn't exist.");
        exit(1);
    }

    //Reads the first 20 characters of the file
    didRead = read(fd, buffer, sizeof(buffer) - 1);
    
    //If the file isn't empty enters the loop
    //The loop will continue until the file is empty or an error occurs
    while(didRead > 0)
    {   
        //Writes a '\0' at the end of the buffer just to be sure no binary trash will be written
        //in the console/terminal
        buffer[didRead] = '\0';  

        //Writes the biffer in the terminal/console
        write(1, buffer, sizeof(buffer));

        //Reads the next 20 characters of the file
        didRead = read(fd, buffer, sizeof(buffer) - 1);    
    }

    //If something goes wrong, prints an error message and closes the program
    if(didRead == -1)
    {
        perror("There was an error trying to read the file.");
        exit(1);
    }
    else // didRead = 0
    {
        write(1, "\nFim do ficheiro\n", sizeof("\nFim do ficheiro\n"));
    }

    close(fd); //close the file
}

//Count the characters in a file
//It will ignore the '\n', '\0' and spaces
int CountCharactersInAFile(char* fileName)
{
    char buffer[21];
    int fd, didRead;
    int size = 0;

    //Opens the file in read only mode
    fd = open(fileName, O_RDONLY);

    //If there was any error trying to open the file
    //prints an error message and closes the program
    if(fd < 0)
    {
        perror("There was an error trying to open the file.");
        exit(1);
    }

    //Reads the first 20 characters of the file
    didRead = read(fd, buffer, sizeof(buffer) - 1);
     
    //If the file isn't empty enters the loop
    //The loop will continue until the file is empty or an error occurs
    while(didRead > 0)
    {
        //Writes a '\0' at the end of the buffer just to be sure
        buffer[didRead] = '\0';

        //Goes through every character in buffer
        for(int i = 0; i < strlen(buffer); i++)
        {
            //Increments 1 to the size variable if the character is no a \n and a space
            if(buffer[i] != '\n' && buffer[i] != ' ')
            {              
                size++;
            }
        }
        
        //Reads the following 20 characters
        didRead = read(fd, buffer, sizeof(buffer) - 1);          
    }

    //If something goes wrong, prints an error message and closes the program
    if(didRead == -1)
    {
        perror("There was an error trying to read the file.");
        exit(1);
    }

    close(fd); //Closes the file

    return size;
}

//Deletes a file given it's name
void DeleteFile(char* fileName)
{
    //If the file doen's exist, print error message to the terminal
    //and closes the program
    if(unlink(fileName) == -1)
    {
        perror("File doesn't exist!");
        exit(1);
    }
}

//Prints information of the file system of a choosen file
void FileStat(char* fileName)
{
    struct stat sb;
    struct passwd *pwuser;

    //If file does exists, saves file information in struct sb
    //If the file doen's exist, print error message to the terminal 
    //and closes the program
    if (stat(fileName, &sb) == -1) {
        perror("Error");
        exit(1);
    }


    //Search owner's name by his id
    //if it does exist save him
    //if it doen's exist, print error message to the terminal
    //and closes the program
    if (NULL == (pwuser = getpwuid(sb.st_uid)))
		{
			perror("getpwuid()");
			exit(1);
		}

    printf("File type: ");

    //Checks what type of file is and print
    switch (sb.st_mode & S_IFMT) 
    {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }

    printf("I-node: %ld\n", (long) sb.st_ino); //Print I-node
    printf("Ownership: %s\n", pwuser->pw_name);//Print ownership name
}

//Truncate two given Files
void TruncateTwoFiles(char* fOrigin, char* fDest)
{
    char buffer[21];
    int fo, fd, didRead;
    
    //Opens the file in read only mode
    fo = open(fOrigin, O_RDONLY);
    //Opens the file in append and write only mode
    fd = open(fDest, O_APPEND | O_WRONLY);
    
    //If there was any error trying to open the file
    //prints an error message and closes the program
    if(fd < 0 || fo < 0)
    {
        perror("There was an error trying to open the file.");
        exit(1);
    }

    //Reads the following 20 characters
    didRead = read(fo, buffer, sizeof(buffer) - 1);
    

    //If the file isn't empty enters the loop
    //The loop will continue until the file is empty or an error occurs
    while(didRead > 0)
    {
        //Writes a '\0' at the end of the buffer just to be sure
        buffer[didRead] = '\0';

        //Writes the biffer in the terminal/console
        write(fd, buffer, sizeof(buffer));

        //Reads the next 20 characters of the file
        didRead = read(fo, buffer, sizeof(buffer) - 1);    
    }

    //If something goes wrong, prints an error message and closes the program
     if(didRead == -1)
    {
        perror("There was an error trying to read the file.");
    }

    //close files
    fclose(fd);
    fclose(fo);
}

//List all files and directories on the given path
//if no path has been given, list all files and directories on the current path
void ListPath(char* path)
{
    struct dirent *dts;

    //Opens directory
    DIR *directory = opendir(path);
    
    //If the directory does not exist
    //prints an error message and closes the program
    if (directory == NULL)
    {
        perror("There was an error trying to open the directory");
        exit(1);
    }

    printf("Files on the inserted path\n");
    
    //while there are files and directories to read
    //prints directories and regular files
    while ((dts = readdir(directory)) != NULL) 
        switch (dts->d_type)
        {
            case DT_REG:
                printf ("Regular File: %s\n", dts->d_name);
                break;
            case DT_DIR:
                printf ("Directory: %s\n", dts->d_name);
                break;
            default:
                break;
        }

    //close directory
    closedir(directory);
}

//Divides the user input in commands and arguments
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

//Inserts command/argument in the list
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

//Free list
Inputs* FreeList(Inputs* lst)
{
    if(lst) lst = FreeList(lst->next);
    else
    {
        free(lst);
        return lst;
    }
}
