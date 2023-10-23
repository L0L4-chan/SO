//
// Created by lola on 7/10/23.
//

#ifndef PRACTICAS_P1_H
#define PRACTICAS_P1_H

#include "p1.c"


//functions for the shell p1
void ToCreate(char * command[], int com);
void ShowStat(char * command[], int com);
void ToList(char * command [], int com);
void ToDelete(char * command[], int com);
void ToDeleteTree(char * command[], int com);


//auxiliares
int copyfiles(char * path, char * command[]);
void print_path ();
void stat_directory(char * command [], int com, bool lon, bool hid);



#endif //PRACTICAS_P1_H
