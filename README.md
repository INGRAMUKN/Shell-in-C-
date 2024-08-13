# Shell-in-C-
Mshell is a basic shell implementation written in C that supports essential shell functionalities. It can handle built-in commands like cd, pwd, echo, help, and can execute external commands. This project demonstrates fundamental concepts in process control, memory management, and string manipulation.
Features
Command Prompt: Displays a custom prompt Mshell>- for user input.
Built-in Commands:
cd [directory]: Change the current working directory. If no directory is provided, change to the home directory.
pwd: Print the current working directory.
echo [text]: Print the provided text to the standard output.
help: Display information about available commands.
exit: Exit the shell.
External Command Execution: Execute commands not built into the shell.
Requirements
A C compiler (e.g., GCC)
POSIX-compliant operating system (Linux, macOS)
Compilation
To compile the shell, use the following command:

bash
Copy code
gcc -o mshell mshell.c
This will generate an executable file named mshell.

Usage
Run the Shell:

bash
Copy code
./mshell
Basic Commands:

To change the directory: cd /path/to/directory
To print the current directory: pwd
To print text: echo Hello World
To get help: help
To exit the shell: exit

Code Overview
display_prompt: Displays the custom shell prompt.
display_banner: Prints a decorative banner when the shell starts.
read_input: Reads input from the user.
dividing_input: Splits user input into command and arguments.
execution: Executes external commands.
myCD: Handles the cd command.
myPWD: Handles the pwd command.
myEcho: Handles the echo command.
builtin_help: Displays help information about built-in commands.
handler: Processes built-in commands and delegates external command execution.
Contribution
Contributions are welcome! Please fork the repository and submit a pull request with your changes
For more information or feedback, please contact: malakelkh734@gmail.com
Thank you.
