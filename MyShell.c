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
//built in commands 
//CHANGE THE CURRENT WORKING DIRECTORY
//arguments[0] is the command ('cd').
// arguments[1] is the target directory (if provided).
void myCD(char** arguments)
{
    if (arguments[1] == NULL)
    {
        // Change to home directory if no argument is provided
        // Retrieve the path of the home directory from the environment variable i used getenv/
        char* home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            fprintf(stderr, "cd: HOME environment variable not set\n");
            return;
        }
        if (chdir(home_dir) != 0)
        {
            perror("cd");
        }
    }
    else
    {
        // User provided a directory argument; change to the specified directory
        // Attempt to change to the specified directory
        if (chdir(arguments[1]) != 0)
        {
            perror("cd");
        }
    }
}

//PRINT WORKING DIRECTORY
//I used getcwd
void myPWD()
{
  char cwd[MAX_INPUT_SIZE];
  if(getcwd(cwd,sizeof(cwd))!=NULL){
    printf("%s\n",cwd);
}else{
   perror("pwd");
}
}

//HELP COMMAND
//Just printing all the commands and their function
void myHelp() {
    printf("Mshell - A simple shell implementation -\n");
    printf("Available commands:\n");
    printf("  cd [directory] - Change the current directory\n");
    printf("  pwd - Print the current working directory\n");
    printf("  help - For information about the commands\n");
    printf("  echo [text] - Print the given text\n");
    printf("  exit - Exit the shell\n");
}

//ECHO COMMAND
//prints the user's input
void myEcho(char** arguments)
{
  for(int i=1;arguments[i]!=NULL;i++){
     printf("%s",arguments[i]);
     if(arguments[i+1]!=NULL){
       printf(" ");
     }
    }
   printf("\n");
}
 
//function that will be in charge of the commands
//this function checks the user input and decides which command to call
int handler(char** arguments){
    if(arguments[0]==NULL){
        return 1; // No command 
    }
    if (strcmp(arguments[0], "cd") == 0) {
        myCD(arguments);
        return 1;
    } else if (strcmp(arguments[0], "pwd") == 0) {
        myPWD();
        return 1;
    } else if (strcmp(arguments[0], "help") == 0) {
        myHelp();
        return 1;
    } else if (strcmp(arguments[0], "echo") == 0) {
        myEcho(arguments);
        return 1;
    }
    return 0; // Not a built-in command
}        
// main function
int main() {
    char* input;//user input 
    char** args;//holding the command and its argument as an array of strings

    //we first display the banner :)
    display_banner();

    while (1) {
        //we display the prompt 
        display_prompt();
        //getting user input
        input = read_input();

        //handling cases where input is NULL
        if (input == NULL) {
            printf("\n");
            break;
        }

        if (strlen(input) == 0) {
            free(input);
            continue;
        }

        //dividing input into commands and arguments
        args = dividing_input(input);

        //if the command is exit we free the memory and exit the loo[
        if (strcmp(args[0], "exit") == 0) {
            free(input);
            free(args);
            break;
        }

        if (!handler(args)) {
            // If handler returns 0, it means it's not a built-in command
            // So we execute it as an external command
            execution(args);
        }

        free(input);
        free(args);
    }
    return 0;
}

