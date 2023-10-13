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
            }else {
                printf("Directory %s created \n", command[1]);
            }
        }//https://man7.org/linux/man-pages/man2/mkdir.2.html
    }else if(com == 3){
        if(!strcmp(command[1], "-f")){
            if(creat(command[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)==-1){
                perror("It has not been possible to create the file\n");
            }else{
            printf("File %s created \n", command[2] );
            }
        }
    }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");
}



void ShowStat(){
    printf("it works\n"); //lstat
}
void ToList(){
    printf("it works\n");
}
void ToDelete(char * command[], int com){
    struct stat info;
    if (com==1) {
        ChangeDir(command, 1);
    }else {
        for (int i = 2; i<=com; i++){
            stat(command[i-1],&info);
            if((info.st_mode& S_IFMT) == S_IFDIR) {
                //comprobar si es directory entonces https://man7.org/linux/man-pages/man2/rmdir.2.html
                if (rmdir(command[i - 1]) == -1) {
                    perror("Impossible to delete \n");
                } else {
                    printf("Directory %s has been delete\n", command[i - 1]);
                }
            }else if((info.st_mode& S_IFMT)==S_IFREG){
                //si es file entonces https://man7.org/linux/man-pages/man2/unlink.2.html
                if(unlink(command[i-1])==-1){
                    perror("Impossible to delete \n");
                }else {
                    printf("File %s has been delete\n", command[i - 1]);
                }
            }
        }
    }
}
void ToDeleteTree(char * command[], int com) {
    struct stat info;
    if (com==1) {
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
    }else{
        for (int i = 2; i<=com; i++){
            stat(command[i-1],&info);
            if((info.st_mode& S_IFMT) == S_IFDIR) {
                //comprobar si es directory entonces https://man7.org/linux/man-pages/man2/rmdir.2.html
                if (rmdir(command[i - 1]) == -1) {
                    //haldle how to remove the content of the directory
                    while (rmdir(command[i - 1]) == -1){


                    }
                }else {
                    printf("Directory %s has been delete\n", command[i - 1]);
                }
            }else if((info.st_mode& S_IFMT)==S_IFREG){
                //si es file entonces https://man7.org/linux/man-pages/man2/unlink.2.html
                if(unlink(command[i-1])==-1){
                    perror("Impossible to delete \n");
                }else {
                    printf("File %s has been delete\n", command[i - 1]);
                })

        }
    }

    // usar delete de forma recursiva
}
