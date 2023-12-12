//
// Created by lola on 25/11/23.
//

#ifndef SO_P3_H
#define SO_P3_H

#include "p3.c"




void SetUID(char* command[], int index);
void ToShowVar(char* command[], int index);
void ToChangeVar(char* command[], int index);
void SetFork();
void ToSubVar(char* command[], int index);
void ToShowEnv(char* command[], int index);
void SetEXEC(char* command[], int index);
void ToJobS(char* command[], int index);
void ToDelJobs(char* command[], int index);
void ToJob(char* command[], int index);
void ToUnknow1(char* command[], int index);
void ToUnknow2(char* command[], int index);
#endif //SO_P3_H
