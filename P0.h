//
// Created by lola on 13/09/23.
//


#include <stdbool.h>
#include "stdio.h"
#include "time.h"
#include <sys/utsname.h>
//#include <syscall.h>deprecade??
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "Log_list.h"
#ifndef PRACTICAS_SHELL_H
#define PRACTICAS_SHELL_H





# define MAXSIZE 50 //REVISAR VALORES
#define MAXENTRIES 250//
#define LNULL NULL


typedef struct tFile {
    int index;
    int df;
    char * CommandName;
    int mode;
} tFile;
typedef struct tLog {
    int index;
    char * CommandName;
} tLog;

//variables
int counterFiles = 0;
int counterProcesses = 0;
char out[3] = {'-','>', '>'};
char in[MAXSIZE];
void * buf_in = &in;
void * buf_out = &out;

//functions


//shell functions
void PrintPromt();// print "->" hint for the user to introduce a command
void ListOpenFiles();//Print on screen a list with the files that are open at thant time
void ProcessingEntry();//Redirect to the appropriate process
void ReadEntry();//get the input from the user
int SliceEntry(char * character, char * chain[], char * limit);// Split the input into tokens
int ActionList(char * command[], int parameter, void * archive[], void * logStorage[]);//Parse the entry and call the function
void PrintAuthor(char * command[], int com);//Command authors
void PrintPID(char * command[], int com);//Command PID
void PrintDate();//Command date
void PrintTime();//command time
void PrintHelp(char * command[], int com);//command help
void ChangeDir(char * command[], int com);//command chdir
void PrintLog(char * command[], int com, void * logStorage[]);//List all the executed command
void ExecuteN(char * command[], int com, void * archive[], void * logStorage[]);//Repeat the N command
void PrintInfoSystem(char * command[], int com);//print info for the machine
void ToClose(void * archive[], void * logStorage[]);//close shell
void Cmd_open (char * command[],void * archive[]);//command open, open a file or directory
void Cmd_close (char *tr[], void * archive[]);//command close, close a file
void Cmd_dup (char * tr[],void * archive[]);//command dup duplicate a file
void Initialize(void * archive[]);

void main(int argc, char * argv[]); //"Game loop"


#endif //PRACTICAS_SHELL_H
