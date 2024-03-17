# myshell User Manual

## *NAME*

myshell 

## *DESCRIPTION*

myshell is a simple shell/command line interpreter created in the C programming language, which enables you to interact with the computer's operating system by providing basic functionality for executing commands, managing different processes, and manipulating files. 

## *INTERNAL COMMANDS*

myshell supports a wide range of built-in commands for you to execute. These said commands are referred to as 'Internal Commands'. These internal commands are listed below and allow you to execute a range of useful commands.

* `cd`: Change the current directory, or print the current directory if only 'cd' is invoked
*  `clr`: Clear the screen -> equivalent to 'clear'
* `dir`: List directory contents -> equivalent to 'ls -al <directory>' or 'ls al'. if only dir is invoked, it prints information on the current directory
* `environ`: List all environment variables
* `echo`: Print arguments to the screen
* `help`: Displays help information from the manual
* `pause`: Pauses the shell until 'Enter' is pressed
* `quit`: Exits the shell and terminates all shell processes.

## *EXTERNAL COMMANDS*

Any command not built into myshell is considered as an 'External Command'. myshell allows the execution of these external commands, displaying the resulting output to you. 

For example, running 'pwd' will print the current working directory and display the output to you.

## *INPUT/OUTPUT REDIRECTION*

Input/Output (I/O) redirection is one of the many features in myshell, where I/O redirecton allows you to control where input for a command comes from, as well as where the output of the command goes to. myshell supports input/output redirection using the following operators:

* `<`: Redirects input from a file to a command. e.g., 'command < input_file'
* `>`: Redirects output from a command to a file and overwrites the file if it exists. e.g., 'command > output_file'
* `>>`: Append output from a command to a file. e.g., 'command < input_file > output_file'

## *PROGRAM ENVIRONMENT*

myshell provides access to the shell environment, and as so, to the environment variables. Environment variables store information about the system, and the program environment determines how te program will behave. Environment variables are utilized in my parts of the source code to display information and functionality.

## *BACKGROUND & FOREGROUND PROGRAM EXECUTION*

### *BACKGROUND PROGRAM EXECUTION*
       
* Background program execution allows myshell to multitask, running commands asynchronously. You are able run commands in the background by appending the ampersand (&) symbol to the end of the command. myshell notifies you with a message displaying the command invoked and the PID (Process ID) of the background process.

### *FOREGROUND PROGRAM EXECUTION*

* Foreground program execution performs commands within myshell's main process ID itself, in a single-task basis, ideally for immediate execution of important commands. You can invoke commands by simply disregarding the ampersand (&) symbol when invoking a command to execute them in the foreground. This way of executing a command is to be differentiated from background program execution because the behaviours from background & foreground execution are processed in a different way.

## *MAIN DIFFERENCE*
       
* **Background Program Execution**: Executes commands in a multi-task basis, allowing for concurrent execution of multiple commands using child processes.
       
* **Foreground Program Execution**: Executes commands in a single-task basis, within myshell's main process itself.

## *REFERENCES*

1. King, K.N. (2008). C programming: a modern approach. W.W. Norton & Company.
2. Plauger, P.J. (1992). The Standard C Library.
3. Love, R. (2013). Linux System Programming. O'Reilly Media, Inc.
4. Molay, B. (2002). Understanding Unix Linux Programming. Turtleback.

## ACKNOWLEDGEMENT TO DCU'S ACADEMIC INTEGRITY & PLAGIARISM POLICY

- Name: *Samson Oloruntola*
- Student Number: *22714745*
- I, Samson Oloruntola, acknowledge all consequences for violating the DCU Academic Integrity and Plagiarism Policy and accept any penalties that are in place if I engage in any activity which breaches this policy for assignment 1, myshell in CA216.
