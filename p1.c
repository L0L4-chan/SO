//
// Created by lola on 7/10/23.
//

#include <sys/stat.h>
#include "p1.h"
#include "p0.h"

void ToCreate(char * command[], int com){
    if (com==1) {
        ChangeDir(command, 1);
        return;
    }else if (com == 2) {
        if(!strcmp(command[1], "-f")){
            ChangeDir(command, 1);
        }else{
            char location[256]; //to store the location
            getcwd(location, sizeof(location));
            strcpy(location, command[1]);
            if(mkdir(location,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)==-1){
                perror("It has not been possible to create the file\n");
            }
            printf("Directory %s created \n", command[1] );
            }//https://man7.org/linux/man-pages/man2/mkdir.2.html
    }else if(com == 3){
        if(!strcmp(command[1], "-f")){
            if(creat(command[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)==-1){
                perror("It has not been possible to create the directory\n");
            }
            printf("File %s created \n", command[2] );
        }
    }
}



void ShowStat(){
    printf("it works\n");
}
void ToList(){
    printf("it works\n");
}
void ToDelete(){
    printf("it works\n");
}
void ToDeleteTree(){
    printf("it works\n");
}
