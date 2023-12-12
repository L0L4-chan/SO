//
// Created by lola on 13/09/23.
//


#include <stdbool.h>
#include "stdio.h"
#include "time.h"
#include <sys/utsname.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#ifndef PRACTICAS_SHELL_H
#define PRACTICAS_SHELL_H


# define MAXSIZE 100 //REVISAR VALORES
#define MAXENTRIES 250//
#define LNULL NULL
//pendiente de revisar
typedef struct tMemList{
    char *addr;
    char type[MAXSIZE];
    char name[MAXSIZE];
    int size;
    char date[MAXSIZE];
    char key[MAXSIZE];
    int descriptors;
    char permit[MAXSIZE];
}tMemList;

typedef struct tItem {
    int index;
    char CommandName[MAXSIZE];
} tItem;

typedef struct tFile {
    int index;
    char CommandName[MAXSIZE];
    char permit[MAXSIZE];
} tFile;

typedef struct tNode *tPos;
typedef struct tNode {
    void * item; //void * data
    tPos next;
} tNode;
typedef tNode *tList;

typedef enum {
    FINISHED,
    STOPPED,
    SIGNALED,
    ACTIVE
} ProcessStatus;

typedef struct {
    int pid;
    char date[MAXSIZE];
    ProcessStatus status;
    int returnValue; // For exit status or signal number
    char *commandLine;
    bool foreground;
    bool priority;
} BackgroundProcess;

typedef struct tProcNode *tProccesPos;
typedef struct tProcNode {
    BackgroundProcess process;
    struct tProcNode *next;
} tBackgroundNode;

typedef tBackgroundNode *tBackgroundList;
tBackgroundList backgroundProcesses;


//variables
int counterFiles = 0;
int counterProcesses = 1;
char out[3] = {'-','>', '>'};
char in[MAXSIZE];
void * buf_in = &in;
void * buf_out = &out;
tList logStorage;
tList archive;
tList * Historical_List = &logStorage;
tList * Archive = &archive;
tList memoryLog;
tList * memLog = &memoryLog;
int actives_process = 0;
char **envi;
//functions

//List functions
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPos first(tList L);
tPos last(tList L);
tPos previous(tPos p, tList L);
tPos next(tPos p, tList L);
void * getItem(tPos p, tList L);
tPos findItem(int n, tList L);
//void updateItem(void * i, tPos p, tList *L);
void deleteAtPosition(tPos p, tList *L);
void deleteList(tList *L);
bool insertItem(void * i, tList *L);
//shell functions
void PrintPromt();// print "->" hint for the user to introduce a command
void ListOpenFiles(tList *list);//Print on screen a list with the files that are open at thant time
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
void Cmd_dup (char * tr[], tList * Log);//command dup duplicate a file
void Initialize(tNode * archive[]);

int main(int argc, char * argv[], char * envioroment[]); //"Game loop"


#endif //PRACTICAS_SHELL_H
