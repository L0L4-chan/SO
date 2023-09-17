//
// Created by lola on 17/09/2023.
//
/*
#ifndef P0_LOG_LIST_H
#define P0_LOG_LIST_H
#include<stdlib.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGHT 100
#define LNULL NULL

typedef char tCommandName[MAX_COMMAND_LENGHT];
typedef struct tItem {
    int PID;
    tCommandName CommandName;
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

tPos next(tPos p, tList L);

tItem getItem(tPos p, tList L);

tPos findItem(int n, tList L);

void updateItem(tItem i, tPos p, tList *L);

void deleteAtPosition(tPos p, tList *L);

void deleteList(tList *L);

bool insertItem(tItem i, tList *L);
#endif //P0_LOG_LIST_H
*/