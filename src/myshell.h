/* 
    Name: Samson Oloruntola
    Student Number: 22714745

    I, Samson Oloruntola, acknowledge all consequences for violating the DCU Academic Integrity and Plagiarism Policy 
    and accept any penalties that are in place if I engage in any activity which breaches this policy for assignment 1, myshell in CA216.
*/

// Importing necessary libraries to run the shell

#include <stdio.h> // Stdin & Output
#include <stdlib.h> // Library functions
#include <string.h> // String manipulation
#include <unistd.h> // Types & function use.
#include <fcntl.h> // File processing controls
#include <errno.h> // Error handling
#include <sys/types.h>  // Data types
#include <sys/wait.h> // Process Management
#include <stdbool.h> // Boolean data type

// Define maximum buffer size for input
#define MAX_BUFFER 1024
// Define maximum directory length
#define MAX_DIR_LENGTH 512
// Define maximum number of command-line arguments
#define MAX_ARGS 50


// Declare global variables to be used for the shell program

extern char **environ; // Environment variables
extern char cwd[MAX_DIR_LENGTH]; // Current working directory
extern char command[MAX_BUFFER]; // Buffer to store command input
extern char *args[MAX_ARGS]; // Array to store command-line arguments
extern int argSize; // Number of command-line arguments
extern bool runInBackground; // Flag indicating background execution
extern char *username; // Username from the users device


// Function prototypes for internal commands

void executeCD(); // Change directory command
void executeClr(); // Clear screen command
void executeDir(); // List directory contents command
void executeEnviron(); // List environment variables command
void executeEcho(); // Print arguments command
void executeHelp(); // Display help information command
void executePause(); // Pause shell operation command
void executeQuit(char *username); // Exit the shell command

// Function prototypes for external commands & I/O redirection:

void executeExternal(bool runInBackground); // Execute external command
void IORedirection(); // Handle input/output redirection

// Function prototypes to run the shell, depending if a file exists or not:

void runShell();
void runShellFromFile(FILE *file); // Run the shell from a file

// Function prototype to set necessary environment variables:
void setEnv(char *programName); // Set parent environment variable

// Function prototype to parse arguments
void parseArgs(); // Parse both file and shell-executed commands

// Function prototype to welcome the user booting up shell
void welcomeUser(); // Welcome the user 