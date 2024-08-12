#include <stdio.h>//used for input and ouput operations
#include <stdlib.h>//we will use the malloc() free() and exit()
#include <string.h>//for string manipulation
#include <unistd.h>//provides access to POSIX operating system API for process control we will use fork()and execvp()
#include <sys/wait.h>// we will use wait() and waitpid() functions to make the parent process wait for child processes to complete 

#define MAX_INPUT_SIZE 1024 // max size input
#define MAX_ARG_COUNT 64 // max number of arguments a command can have



/*this function will print a prompt "Mshell>- "
the use of fflush is to ensure that the prompt is 
displayed immediatly after the openning of the shell*/
void display_prompt() {
    printf("Mshell>- ");
    fflush(stdout);
}

void display_banner() {
    printf("\033[38;5;129m");  // Set color to a deep purple
    printf("███╗   ███╗ █████╗ ██╗      █████╗ ██╗  ██╗███████╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
    printf("████╗ ████║██╔══██╗██║     ██╔══██╗██║ ██╔╝██╔════╝    ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
    printf("██╔████╔██║███████║██║     ███████║█████╔╝ ███████╗    ███████╗███████║█████╗  ██║     ██║     \n");
    printf("██║╚██╔╝██║██╔══██║██║     ██╔══██║██╔═██╗ ╚════██║    ╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
    printf("██║ ╚═╝ ██║██║  ██║███████╗██║  ██║██║  ██╗███████║    ███████║██║  ██║███████╗███████╗███████╗\n");
    printf("╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
    printf("\033[38;5;159m");  // Change to a cyan color for vaporwave effect
    printf("▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄\n");
    printf("\033[38;5;218m");  // Change to a pink color
    printf("                    ♡ ♡ ♡ Ｍａｌａｋ Ｅｌｋｈｏｕｌｉ＇ｓ Ｃｒｅａｔｉｏｎ ♡ ♡ ♡ \n");
    printf("\033[38;5;159m");  // Back to cyan
    printf("▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄\n");
    printf("\033[38;5;213m");  // Light purple again
    printf("                              【﻿THANK YOU AND ENJOY ! 】\n");
    printf("\033[0m");  // Reset color
    printf("\n                 Type 'help' for more info about this shell's commands.\n\n");
}

/*this function reads the user input, deals with cases where the input is NULL
it also removes the newline from the input*/
char* read_input()
{
    char* input= malloc(MAX_INPUT_SIZE);//allocating memory for storing the input from the user
    if(!input)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);//terminating the program with failure status
    }

    // in case fgets fails to read input 
    if(fgets(input,MAX_INPUT_SIZE,stdin)==NULL)
    {
        free(input);
        return NULL;
    }
    //removing the newline
    //we will use strcspn to find the position of newline character
    input[strcspn(input,"\n")]='\0';
    return input;

}

char** dividing_input(char* input)
{
    //allocating memory for the arguments
    char** arguments=malloc(MAX_ARG_COUNT * sizeof(char*));
    if(!arguments)
    {
        perror("MALLOC ERROR");
        exit(EXIT_FAILURE);
    }

//tokenization 
    char* token = strtok(input," ");
//tokenization process
    int i=0;
    while(token!= NULL&& i<MAX_ARG_COUNT-1)
    {
        arguments[i]=token;
        token= strtok(NULL," ");//continue tokenizinf from where it left off 
        i++;
    }
    arguments[i]=NULL; //adding sentinel
    return arguments;
}

//executing the command
void execution(char** arguments)
{
    pid_t pid=fork();//creating a new process (duplicating the current process)
    //in case fork() failed
    if(pid==-1)
    {
        perror("fork error!");
    }
    else if(pid==0)
    {
    //replacing the current process 
        if(execvp(arguments[0], arguments)==-1)
        {
            perror("execvp error!");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);//waiting for child process to terminate
    }
}

//temporary main function
int main() {
    char* input;
    char** args;
    display_banner();

    
    while (1) {
        display_prompt();
        input = read_input();
        
        if (input == NULL) {
            printf("\n");
            break;
        }
        
        if (strlen(input) == 0) {
            free(input);
            continue;
        }
        
        args = dividing_input(input);
        
        if (strcmp(args[0], "exit") == 0) {
            free(input);
            free(args);
            break;
        }
        
        execution(args);
        
        free(input);
        free(args);
    }
    
    return 0;
}
// still need to add commands to my shell

