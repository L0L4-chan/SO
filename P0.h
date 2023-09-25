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


typedef struct tItem {
    int index;
    char * CommandName;
    int mode;
} tItem;
typedef struct tNode *tPos;
typedef struct tNode {
    tItem item;
    tPos next;
} tNode;
typedef tNode *tList;



//variables
int counterFiles = 0;
int counterProcesses = 0;
char out[3] = {'-','>', '>'};
char in[MAXSIZE];
void * buf_in = &in;
void * buf_out = &out;
tList logStorage;
tList archive;
tList * Historical_List = &logStorage;
tList * Archive = &archive;
int actives_process = 0;
//functions

//List functions
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPos first(tList L);
tPos last(tList L);
tPos previous(tPos p, tList L);
bool hasNext(tPos p, tList L);
tPos next(tPos p, tList L);
tItem getItem(tPos p, tList L);
tPos findItem(int n, tList L);
void updateItem(tItem i, tPos p, tList *L);
void deleteAtPosition(tPos p, tList *L);
void deleteList(tList *L);
bool insertItem(tItem i, tList *L);
//shell functions
void PrintPromt();// print "->" hint for the user to introduce a command
void ListOpenFiles(tList list);//Print on screen a list with the files that are open at thant time
void ProcessingEntry();//Redirect to the appropriate process
void ReadEntry();//get the input from the user
int SliceEntry(char * character, char * chain[], char * limit);// Split the input into tokens
int ActionList(char * command[], int parameter, tList * Log);//Parse the entry and call the function
void PrintAuthor(char * command[], int com);//Command authors
void PrintPID(char * command[], int com);//Command PID
void PrintDate();//Command date
void PrintTime();//command time
void PrintHelp(char * command[], int com);//command help
void ChangeDir(char * command[], int com);//command chdir
void PrintLog(char * command[], int com, tList * Log);//List all the executed command
void ExecuteN(char * command[], int com, tList * Log);//Repeat the N command
void PrintInfoSystem(char * command[], int com);//print info for the machine
void ToClose();//close shell
void Cmd_open (char * command[]);//command open, open a file or directory
void Cmd_close (char *tr[]);//command close, close a file
void Cmd_dup (char * tr[]);//command dup duplicate a file


void main(int argc, char * argv[]); //"Game loop"


#endif //PRACTICAS_SHELL_H
