//
// Created by lola on 7/10/23.
//

#include <sys/stat.h>
#include "p1.h"
#include "p0.h"

void ToCreate(char * command[], int com){
    if (com==1) {
        ChangeDir(command, 1);
    }else if (com == 2) {
        if(!strcmp(command[1], "-f")){
            ChangeDir(command, 1);
        }else{
            mkdir(command[1],);
        }


    }


}
void ShowStat(){}
void ToList(){}
void ToDelete(){}
void ToDeleteTree(){}
