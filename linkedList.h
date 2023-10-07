//
// Created by lola on 7/10/23.
//

#ifndef PRACTICAS_SHELL_H
#define PRACTICAS_SHELL_H


#define MAXSIZE 50 //REVISAR VALORES
#define MAXENTRIES 250//
#define LNULL NULL

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

#endif //PRACTICAS_SHELL-H