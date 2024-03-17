# MyShell User Manual

## DESCRIPTION
MyShell is a simple shell/command line interpreter similar to Unix, created in the C programming language. It allows users to interact with the computer's operating system by providing basic functionality for executing commands, managing different processes, and manipulating files.

## BUILT-IN INTERNAL COMMANDS
MyShell supports a series of built-in commands:

- `cd`: Change the current directory
- `clr`: Clear the screen, equivalent to 'clear'
- `dir`: List directory contents, equivalent to 'ls -al <directory>' or 'ls al'
- `environ`: List environment variables
- `echo`: Print arguments to the screen
- `help`: Displays help information from the manual
- `pause`: Pause shell operation
- `quit`: Exit the shell

## EXTERNAL COMMANDS 
Any command not built into MyShell is considered an external command. MyShell allows the execution of these external commands, displaying the resulting output to the user. For example, running 'pwd' will print the current working directory.

## INPUT/OUTPUT REDIRECTION
MyShell supports input/output redirection using the following operators:

- `<`: Redirects input from a file to a command. e.g., 'command < input_file'
- `>`: Redirects output from a command to a file, overwriting the file if it exists. e.g., 'command > output_file'
- `>>`: Append output from a command to a file. e.g., 'command < input_file > output_file'

## PROGRAM ENVIRONMENT
MyShell provides access to the shell environment and environment variables. These variables store information about the system and user preferences, determining the behavior of the program. MyShell utilizes predefined system variables and allows customization through user-defined variables.

## BACKGROUND & FOREGROUND PROGRAM EXECUTION

### BACKGROUND PROGRAM EXECUTION
Background program execution allows MyShell to multitask, running commands asynchronously. Users can execute commands in the background by appending the ampersand (&) symbol to the end of the command. MyShell notifies users with a message displaying the command invoked and the PID (Process ID) of the background process.

### FOREGROUND PROGRAM EXECUTION
Foreground program execution performs commands within MyShell's main process ID itself, in a single-task basis. Users invoke commands without the ampersand (&) symbol to execute them in the foreground. This mode of execution is differentiated from background program execution by its behavior.

#### MAIN DIFFERENCE
- **Background Program Execution**: Executes commands in a multi-task basis, allowing for concurrent execution of multiple commands using child processes.
- **Foreground Program Execution**: Executes commands in a single-task basis, within MyShell's main process itself.

## AUTHOR 
- **Samson Oloruntola**
- Email: samson.oloruntola2@mail.dcu.ie

## REFERENCES
1. King, K.N. (2008). *C programming: a modern approach*. W.W. Norton & Company.
2. Plauger, P.J. (1992). *The Standard C Library*.
3. Love, R. (2013). *Linux System Programming*. O'Reilly Media, Inc.
4. Molay, B. (2002). *Understanding Unix Linux Programming*. Turtleback.

## ACKNOWLEDGEMENT TO DCU'S ACADEMIC INTEGRITY & PLAGIARISM POLICY
- Name: Samson Oloruntola
- Student Number: 22714745
- I, Samson Oloruntola, acknowledge all consequences for violating the DCU Academic Integrity and Plagiarism Policy for assignment 1, MyShell in CA216.
