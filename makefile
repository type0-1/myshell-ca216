# Samson Oloruntola, 22714745 - Operating Systems Project 1
# CA216
# Declaration: I, Samson Oloruntola, acknowledge all consequences to violating the DCU Academic Integrity and Plagiarism Policy for assignment 1, MyShell in CA216.

myshell: src/myshell.c src/utility.c src/myshell.h
	mkdir -p bin
	gcc -Wall src/myshell.c src/utility.c -o bin/myshell
