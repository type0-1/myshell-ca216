# myshell: Manual


## *NAME*

**myshell** - A simple shell 


## *DESCRIPTION*

myshell is a simple shell/command line interpreter created in the C programming language, which enables you to interact with the computer's operating system by providing basic functionality for executing commands, managing different processes, and manipulating files. 


## *INTERNAL COMMANDS*

myshell supports a wide range of built-in commands for you to execute. These said commands are referred to as *'Internal Commands'*. 

When you enter one of these internal commands into `myshell`, myshell recognizes it as a built-in command and executes it using its own process. 

These internal commands are listed below and allow you to execute a range of useful commands.

* `cd`:-> Change the current directory or print the current directory if only 'cd' is invoked
*  `clr`:-> Clears the screen, equivalent to 'clear'
* `dir`:-> List directory contents, equivalent to 'ls -al [directory]' or 'ls al'. if only dir is invoked, it prints information on the current directory
* `environ`:-> List all environment variables
* `echo`:-> Print arguments to the screen
* `help`:-> Displays help information from the manual
* `pause`:-> Pauses the shell until 'Enter' is pressed
* `quit`:-> Exits the shell and terminates all shell processes.


### *EXAMPLES OF COMMAND OPERATION/EXECUTION*

Below are examples of command-line execution for the built in commands (the command will follow the format [command]):

- `cd`:  [cd] [directory] or [cd]
- `clr`: [clr]
- `dir`: [dir] or [dir] [directory]
- `environ`: [environ]
- `echo`: [echo] or [echo] [arg(s)]
- `help`: [help]
- `pause`: [pause]
- `quit`: [quit]


## *EXTERNAL COMMANDS*

Any command not built into myshell is considered as an *'External Command'*.

External commands can be commands, programs or scripts in which are located outside of myshell's pre-defined commands from its source code. These commands are separate executable files or scripts residing somewhere in your file system, when you enter an external command in the shell, the shell needs to locate the corresponding executable file, then fork a new process to execute it. 

Examples of external commands include system utilities like `ls`, `pwd`, `grep`, `cat`, and user-defined scripts or executables.

To provide an example, when you run `myshell` and invoke the following command `pwd`, myshell recognises that it is not a built-in command and treats it like an external command. 

This locates the `pwd` executable in the system and executes it as a separate process and shows the output back to you. This follows the same process as any other command.

## *PROGRAM ENVIRONMENT*

myshell provides access to the shell environment, and as so, to the environment variables. Environment variables store information about the system, and the program environment determines how the program will behave. Environment variables are utilized in my parts of the source code to display information about the system.

There are primarily two different types of environment variables.

* *System Variables*: These variables are pre-defined in your system and display information about the corresponding environment variable. `HOME`, `PWD`, `SHELL` etc.

- For example, when you run myshell, your user name associated with the device running myshell is displayed to you in the command-line prompt. This was achieved by retrieving the pre-defined system variable `USER` and displaying it.

* *User Variables*: These variables are defined by the user, which can also be customized according to your preferences/requirements. As they are user variables, they usually store user-specific information and/or settings that can have a varying level of impact with the behaviours of programs and the environment.

## *INPUT/OUTPUT REDIRECTION*

Input/Output (I/O) redirection is one of the many features in myshell, where I/O redirecton allows you to control where input for a command comes from, as well as where the output of the command goes to. myshell supports input/output redirection using the following operators:

* `<`: Redirects input from a file to a command. e.g., `[command] < [input_file]`
* `>`: Redirects output from a command to a file and overwrites the file if it exists. e.g., `[command] > [output_file]`
* `>>`: Append output from a command to a file. e.g., `[command] [args] < [input_file] >> [output_file]`.


## *PROCESSES, BACKGROUND & FOREGROUND PROGRAM EXECUTION*

* Processes in reference to computers are can be denoted as tasks that are done in the background of your computer which perform a task in which you assign the computer to handle. Processes are more commonly explained as an instance of your current program, and holds many resources in order to execute these processes for you **Memory**, **Files** etc.

### *BACKGROUND PROGRAM EXECUTION*
       
* Background program execution allows myshell to multitask, running commands asynchronously. You are able run commands in the background by appending the ampersand `&` symbol to the end of the command. myshell notifies you with a message displaying the command invoked and the PID (Process ID) of the background process.


### *FOREGROUND PROGRAM EXECUTION*

* Foreground program execution performs commands within myshell's main process ID itself, in a single-task basis, ideally for immediate execution of important commands. You can invoke foreground commands by simply disregarding the ampersand `&` symbol when invoking a command to execute them in the foreground. 

This way of executing a command is to be differentiated from background program execution because the behaviours from background & foreground execution are processed in a different way.


### *MAIN DIFFERENCE*
       

#### **Background Program Execution**: 

- Executes commands in a multi-task basis 
- Concurrently executes multiple commands using child processes.
- Is invoked using the `&` at the end of a command


#### **Foreground Program Execution**: 

- Executes commands in a single-task basis
- Uses myshell's main process itself for executing commands
- Is not invoked using `&` at the end of a command


## *REFERENCES*

1. King, K.N. (2008). C programming: a modern approach. W.W. Norton & Company.
2. Plauger, P.J. (1992). The Standard C Library.
3. Love, R. (2013). Linux System Programming. O'Reilly Media, Inc.
4. Molay, B. (2002). Understanding Unix Linux Programming. Turtleback.


## **ACKNOWLEDGEMENT TO DCU'S ACADEMIC INTEGRITY & PLAGIARISM POLICY**

- Name: **Samson Oloruntola**
- Student Number: **22714745**
- I, Samson Oloruntola, acknowledge all consequences for violating the DCU Academic Integrity and Plagiarism Policy and accept any penalties that are in place if I engage in any activity which breaches this policy for assignment 1 in CA216 - Operating Systems.
