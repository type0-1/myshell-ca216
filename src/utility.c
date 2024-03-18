/* 
    Name: Samson Oloruntola
    Student Number: 22714745

    I, Samson Oloruntola, acknowledge all consequences for violating the DCU Academic Integrity and Plagiarism Policy 
    and accept any penalties that are in place if I engage in any activity which breaches this policy for assignment 1, myshell in CA216.
*/

// Importing the C header file "myshell.h" to utilize functions, global variables and import libraries 
#include "myshell.h"

// Declaring global variables derived from myshell.h 
extern char **environ;
char cwd[MAX_DIR_LENGTH]; 
char command[MAX_BUFFER]; 
char *args[MAX_ARGS];
int argSize = 0;
bool runInBackground = false;
char *username;

/*  
    Function for executing the built-in "cd" command 
    This code is adapted from: https://iq.opengenus.org/chdir-fchdir-getcwd-in-c/ for using chdir() & getcwd()
    This code is adapted from: https://www.man7.org/linux/man-pages/man3/getenv.3.html for using get & set env()
*/

void executeCD() {
    // Get the current working directory, print it to the user and update the PWD environment variable.
    if (argSize == 1) { // Only "cd" was invoked
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
            setenv("PWD", cwd, 1);
        } 
    // Change directory, retrieve the current working directory and update the PWD, else display error.
    } else if (argSize == 2) { // A directory was included
        if (chdir(args[1]) == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                setenv("PWD", cwd, 1); 
            }
        }
    } else { // Invalid arguments
        fprintf(stderr, "Invalid arguments for cd\n"); // Invalid arguments invoked
    }
}

/* Function that executes the built-in "clr" command  */
void executeClr() {
    system("clear"); // Call "clear" on the system function
}

/* Function that executes the built in "help" command */
void executeHelp() {
    // Attempt to get the current working directory, and display an error if needed
    if (getcwd(cwd, sizeof(cwd)) == NULL) { 
        perror("Error getting current working directory"); 
        exit(EXIT_FAILURE);
    }

    // Allocate memory and create the absolute path to the manual
    char *manual_path = malloc(strlen(cwd) + strlen("/manual/readme.md") + 1);
    if (!manual_path) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Copy the cwd and concatenate the relative path to readme.md
    strcpy(manual_path, cwd);
    strcat(manual_path, "/manual/readme.md");

    // Get the absolute path of the manual and display error if appropriate.
    // This code is adapted from: https://stackoverflow.com/questions/229012/getting-absolute-path-of-a-file for retrieving absolute path

    char *ptr = realpath(manual_path, NULL);
    if (!ptr) {
        perror("Error getting absolute path of manual");
        free(manual_path);
        exit(EXIT_FAILURE);
    }

    // Alllocate memory and display error if appropriate 
    char *command = malloc(strlen("more -d ") + strlen(ptr) + 1);
    if (!command) {
        perror("Memory allocation failed");
        free(manual_path);
        free(ptr);
        exit(EXIT_FAILURE);
    }

    // This code is adapted from: https://overiq.com/c-programming-101/the-sprintf-function-in-c/ to handle string assignment.
    sprintf(command, "more -d %s", ptr);

    // Clear the screen before displaying the manual and execute the command afterwards.
    executeClr();
    
    system(command);
    free(manual_path);
    free(ptr);
    free(command);
}

/* Function that executes the built-in "pause" command */
void executePause() {
    printf("Press Enter to continue...");  // Display to the user to press enter to terminate pause, and loop until done so.
    while (getchar() != '\n');
}

/* Function that executes the built-in "quit" command */
void executeQuit(char *username) {
    // Display prompts, use sleep() and then clear screen before exiting.
    printf("\n==> See you later, "ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET"!\n", username);
    sleep(1);
    printf("==> Exiting "ANSI_COLOR_RED"myshell"ANSI_COLOR_RESET"...\n\n");
    sleep(2);
    executeClr();
    exit(EXIT_SUCCESS); // Exit success.
}

/* Function that executes the built-in "dir" command */
void executeDir() {
    if (argSize == 1) { // If "dir" is the only argument invoked, call "ls -al"  from the system
        system("ls -al"); 
    } else if (argSize == 2) { // If the directory is included, assign directory name to char pointer "dir"
        char *command = malloc(strlen("ls -al " + strlen(args[1]) + 1)); // Allocate memory to local variable command
        if(!command){ // If memory allocation has failed, print error
            perror("Memory allocation has failed!");
            exit(EXIT_FAILURE);
        } 
        // Copy the string "ls -al" to command, concatenate directory in args, call command and free memory 
        strcpy(command, "ls -al ");
        strcat(command, args[1]);
        system(command);
        free(command);
    } else { // Display invalid argument error to stderr
        fprintf(stderr, "Invalid arguments for dir\n");
    }
}

/* Function that executes the built-in "environ" command */
void executeEnviron() {
    // Loop through each one printing out information.
    for(char **env = environ; *env; env++){
        printf("%s\n", *env);
    }
}

/* Function that executes the built-in "echo" command */
void executeEcho() {
    // Print a newline if "echo" is the only argument, else print each environment variable followed by a newline
    if (argSize == 1) {
        printf("\n");
    } else {
        for (int i = 1; i < argSize; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");
    }   
}

/* Function that handles IO redirection */
void IORedirection() { 
    pid_t pid = fork(); // Fork the process ID

    if (pid == -1) {
        perror("A forking error has occured in regards to I/O redirection\n"); // Display fork error
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 
        setenv("PARENT", getenv("SHELL"), 1); // Set the PARENT environment to the SHELL variable value
        // Initialize input & output index to -1 (flags for redirection)
        int input_index = -1, output_index = -1;
        for (int i = 0; i < argSize; ++i) { // Find the indices of input and/or output files
            if (!strcmp(">", args[i]) || !strcmp(">>", args[i])) {
                output_index = i; // Set the output redirection index
            } else if (!strcmp("<", args[i])) {
                input_index = i; // Set the input redirection index
            }
        }

        // This code is adapted from: https://cplusplus.com/reference/cstdio/freopen/ for file I/O redirection
        
        // Handle output redirection
        if (output_index != -1) { 
            // Determine the file open mode based on the redirection symbol and try to receive and open the output file.
            const char *mode = (!strcmp(">>", args[output_index]) ? "a" : "w");
            FILE *output_file = freopen(args[output_index + 1], mode, stdout);
            if (output_file == NULL) {  // Display error if opening isn't successful
                perror("A freopen error has occured in opening the output file\n");
                exit(EXIT_FAILURE);
            }
            // Remove the redirection operator and output filename from arguments
            args[output_index] = NULL;
            args[output_index + 1] = NULL;
        }

        // Handle input redirection
        if (input_index != -1) {
            FILE *input_file = freopen(args[input_index + 1], "r", stdin); // Try retrieve input_file and open it
            if (input_file == NULL) {
                perror("A freopen error has occured in opening the input file\n"); // Display error
                exit(EXIT_FAILURE);
            }
            // Remove the redirection operator and input filename from arguments
            args[input_index] = NULL;
            args[input_index + 1] = NULL;
        }

        // Check if the command is "environ" or "help" and execute them directly
        if (strcmp(args[0], "environ") == 0) {
            executeEnviron(); // Call the executeEnviron() function
            exit(EXIT_SUCCESS);
        } else if (strcmp(args[0], "help") == 0) {
            executeHelp(); // Call the executeHelp() function
            exit(EXIT_SUCCESS);
        }

        // Execute the command with modified stdin/stdout streams
        execvp(args[0], args);
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

/*
    Function that executes external commands (takes in background process)
    This code is adapted from: https://dev.to/wahomethegeek/building-your-own-shell-in-c-a-journey-into-command-line-magic-2lon
*/

void executeExternal(bool runInBackground) {
    pid_t pid = fork(); // Fork the process ID

    if (pid == -1) {
        perror("A forking error has occured in regards to external command execution\n"); 
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Run the child process, set the PARENT env to the shell environment value and execute args
        setenv("PARENT", getenv("SHELL"), 1); 
        execvp(args[0], args);
        perror("A execvp error has occured in trying to execute external commands\n");
        exit(EXIT_FAILURE);
    } else { // Parent process: continue with the shell prompt
        if (runInBackground == 0) { // Check for background processing
            int status;
            waitpid(pid, &status, 0); // Wait for child process if not running in background
        } else {
            if (command != NULL) { // Check if the command is available
                printf("\n==> The command: [%s] with PID [%d] is now running in the background!\n\n", command, pid);
            }
        }
    }
}

/* Function to check commands */
void checkCommands() {
    // Check for I/O redirection, if redirection symbols are present, execute I/O function
    for(int i = 0; i < argSize; ++i){ 
        if ((strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)) { 
            IORedirection(); 
            return;
        } else if ((strcmp(args[i], "<") == 0)) {
            IORedirection();
            return;
        }
    }

    // Check if we want to run the command in the background
    // Set flag to indicate background execution, remove ampersand from args and decrement argument size
    
    if (argSize > 0 && strcmp(args[argSize - 1], "&") == 0) {
        runInBackground = true;
        args[argSize - 1] = NULL; 
        argSize--;
    } else {
        runInBackground = false; // Ensure background flag is set to false for foreground processes
    }

    // Execute internal commands or handle external commands accordingly
    if (strcmp(args[0], "cd") == 0) {
        executeCD(); // "cd" function
    } else if (strcmp(args[0], "clr") == 0) {
        executeClr(); // "clr" function
    } else if (strcmp(args[0], "dir") == 0) {
        executeDir(); // "dir" function
    } else if (strcmp(args[0], "environ") == 0) {
        executeEnviron(); // "environ" function
    } else if (strcmp(args[0], "echo") == 0) {
        executeEcho(); // "echo" function
    } else if (strcmp(args[0], "help") == 0) {
        executeHelp(); // "help" function
    } else if (strcmp(args[0], "pause") == 0) {
        executePause(); // "pause" function
    } else if (strcmp(args[0], "quit") == 0) {
        executeQuit(username); // "quit" function (pass username in for visuals)
    } else {
        executeExternal(runInBackground); // external commands (pass in background to check for background processing)
    }
}

/* Function that sets the shell environment */
void setEnv(char *programName){
    // Get the real path of the program name, and display an error if retrieval was unsuccessful
    char *shell_path = realpath(programName, NULL); 

    if (shell_path == NULL) { 
        perror("Realpath error has occured in setting the PARENT environment variable\n");
        exit(EXIT_FAILURE);
    }

    // Set the PARENT and SHELL environment variable values to shell_path, and free memory.
    setenv("SHELL", shell_path, 1); 
    free(shell_path);
}

/* Function that runs the shell */
void runShell() {
    username = getenv("USER"); // Get the user associated with the operating system, and display an error if needed
    welcomeUser(username); // Welcome the user
    while (1) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) { // Try retrieving the cwd, display error if it fails
            perror("A getcwd error has occured\n");
        } else { // Display prompt with colour coding
            printf("["ANSI_COLOR_YELLOW"myshell"ANSI_COLOR_RESET":"ANSI_COLOR_MAGENTA" %s"ANSI_COLOR_RESET"] ~"ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"> ", username, cwd); 
        }
        fgets(command, MAX_BUFFER, stdin); // Read command from stdin
        command[strcspn(command, "\n")] = '\0'; // Find the first occurence of the newline character and set it to the null terminator.

        if(!strlen(command)){ // If the command is empty, skip to the next iteration.
            continue;
        }
        parseArgs(); // Parse commands
        checkCommands();  // Check commands and handle redirection
    }
}

/* Function that runs the shell based off the file */
void runShellFromFile(FILE *file) {
    username = getenv("USER"); // Get the user associated with the operating system, and display an error if needed
    while (fgets(command, MAX_BUFFER, file) != NULL) { // Run until the command is NULL, getting each command from our file.
        if (strcmp(command, "\n") == 0) { // Skip empty lines
            continue;
        }
        command[strcspn(command, "\n")] = '\0';  // Find the first occurence of the newline character and set it to the null terminator.
        parseArgs(); // Parse commands
        checkCommands(); // Check commands and handle redirection
    }
}

/*
    Function below is to parse command-line arguments
    This code is adapted from: https://dev.to/wahomethegeek/building-your-own-shell-in-c-a-journey-into-command-line-magic-2lon
*/

void parseArgs(){
    // Set initial arg size to 0 and begin tokenization on command, based on separators.
    argSize = 0; 
    char *ptr = strtok(command, " \t\n");

    // Tokenize arguments until we have met a NULL argument, or have reacehed size limit (argSize < MAX_ARGS - 1).
    while (ptr != NULL && argSize < MAX_ARGS - 1) {
        // Set the value at position argSize to ptr, and move to the next token
        args[argSize++] = ptr;
        ptr = strtok(NULL, " \t\n");
    }
    args[argSize] = NULL; // Terminate the args array with NULL
}

/* 
Function to welcome the user 
This welcome screen was inspired by: https://termcast.computing.dcu.ie/
*/

void welcomeUser(char *username){
    // Clear the screen
    executeClr(); 
    // Introductory text displayed to the user
    printf("=====:[ Welcome to myshell, ");

    // Display welcome screen, colour functionality was sourced from: https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
    printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET "! ]:=====\n\n" , username);

    printf("@---o--o--o--o--o--o[:" ANSI_COLOR_YELLOW " Info :" ANSI_COLOR_RESET "]o--o--o--o--o--o---@\n");
    printf("|                                                |\n");
    printf("|       Run " ANSI_COLOR_MAGENTA "`help`" ANSI_COLOR_RESET " to view the user manual       |\n");
    printf("|       To exit the program, run "ANSI_COLOR_MAGENTA"`quit`"ANSI_COLOR_RESET"          |\n");
    printf("|       To clear this screen, run "ANSI_COLOR_MAGENTA"`clr`"ANSI_COLOR_RESET"          |\n");
    printf("|                                                |\n");
    printf("@--o--o--o--o--o--o[==========]o--o--o--o--o--o--@\n\n");

    // Sleep for 3 seconds total.
    sleep(1);
    printf("==> Displaying prompt..\n\n");
    sleep(2);
}