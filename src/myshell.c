/* 
    Name: Samson Oloruntola
    Student Number: 22714745

        I, Samson Oloruntola, acknowledge all consequences for violating the DCU Academic Integrity and Plagiarism Policy 
    and accept any penalties that are in place if I engage in any activity which breaches this policy for assignment 1, myshell in CA216.
*/

// Importing the C header file "myshell.h" to utilize functions and libraries
#include "myshell.h"

int main(int argc, char *argv[]) {
    // Set the shell environment variable shell to the shell path.
    setEnv(argv[0]);

    if (argc == 2) {
        FILE *file = fopen(argv[1], "r"); // Attempt to open the file in read mode
        if (file == NULL) { // If opening the file has failed, display an error and exit.
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        runShellFromFile(file); // Run the shell from a file
    } else {
        runShell(); // Run the shell without a file
    }
    return 0;
}
