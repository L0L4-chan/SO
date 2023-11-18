//
// Created by lola on 30/10/23.
//

#ifndef PRACTICAS_P2_H
#define PRACTICAS_P2_H

#include <stdbool.h>
#include "p2.c"

//pendiente de revisar
typedef struct tMemList{
    char *addr;
    char *type;
    char *name;
    int size;
    char *date;
    int key;
    int descriptors;
}tMemList;

tList memoryLog;
tList * memLog = &memoryLog;

tList freeLog;
tList * fLog = &memoryLog;
void Make_Malloc(char * command[], int com);
void Make_Shared(char * command[], int com);
void Make_Mmap(char * command [], int com);
void ToRead(char * command[], int com);
void ToWrite(char * command[], int com);
void Make_Memdump(char * command[], int com);
void Make_Memfill(char * command[], int com);
void ToMem(char * command [], int com);
void ToRecurse(char * command[], int com);

#define SO_P2_H

#endif //SO_P2_H
