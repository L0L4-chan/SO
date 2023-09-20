//
// Created by lola on 13/09/23.
//


#include <stdbool.h>
#include "stdio.h"
//#include <syscall.h>deprecade??
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Log_list.h"
#ifndef PRACTICAS_SHELL_H
#define PRACTICAS_SHELL_H


# define MAXSIZE 50 //REVISAR VALORES


#define MAX_COMMAND_LENGHT 100
#define LNULL NULL


typedef struct tItem {
    int PID;
    int PPID; // father's PID
    char * CommandName;
} tItem;
typedef struct tNode *tPos;
typedef struct tNode {
    tItem item;
    tPos next;
} tNode;
typedef tNode *tList;

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
//variables
//enum valid_commands{
   // O_CREAT,O_EXCL,O_RDONLY, O_WRONLY,O_RDWR,O_APPEND, O_TRUNC
//};

char out[3] = {'-','>', '>'};
char in[MAXSIZE];
char * chunks[5];
void * buf_in = &in;
void * buf_out = &out;
tList logStorage;
tList * Historical_List = &logStorage;
int actives_process = 0;
//functions
void imprimirPront();// print "->" hint for the user to introduce a command
void ListOpenFiles();//Print on screen a list with the files that are open at thant time
void procesarEntrada();//Redirect to the appropriate process
void leerEntrada();//get the input from the user
int TrocearCadena(char * character, char * cadena[]);// Split the input into tokens
int ActionList(char * command[], int parameter, tList * Log);
void PrintAuthor(char * command[], int com);
void PrintPID(char * command[], int com, tList * Log);
void PrintHelp(char * command[], int com, tList * Log);
void main(int argc, char * argv[]); //"Game loop"
//TODO include the rest of the needed headers and functions that we will need.


#endif //PRACTICAS_SHELL_H
