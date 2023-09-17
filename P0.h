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


# define MAXSIZE 256 //REVISAR VALORES
# define MAXNAME 540 //REVISAR VALORES


//variables
enum valid_commands{
    O_CREAT,O_EXCL,O_RDONLY, O_WRONLY,O_RDWR,O_APPEND, O_TRUNC
};

char out[3] = {'-','>', '>'};
char in[MAXSIZE];
char chuncks[MAXSIZE];
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
void main(int argc, char * argv[]); //"Game loop"
//TODO include the rest of the needed headers and functions that we will need.


#endif //PRACTICAS_SHELL_H
