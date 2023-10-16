//
// Created by lola on 7/10/23.
//

#include <sys/stat.h>
#include <dirent.h>
#include "p1.h"
#include "p0.h"
#include "ayuda1.c"

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
void ToList(char * command [], int com){
    DIR * directory;
    char * location[256]; //to store the location
    getcwd(*location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
    struct dirent *entry;
    int files = 0;

    if (command[1] == NULL){//Si no se especifica un directorio que hacemos??
        perror("A directory should be specified");
        /*
        getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
        while( (entry=readdir(location)) ){
            files++;
            printf("File %3d: %s\n", files, entry->d_name);
        }*/
    }
    else {
        directory = opendir(command[1]);
        if (realpath( command[1], * location)  == NULL){
            perror("Root directory incorrect\n");
        }
        else{
            if (location == NULL)
                perror("This directory is not available");
            else{
                while((entry=readdir(location)) != NULL){
                    files++;
                    printf("File %3d: %s\n", files, entry->d_name);
                }
            }

        }
        closedir(directory);
    }

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
    int status, copies;
    char * aux[MAXSIZE];
    if (com==1) {
        ChangeDir(command, 1);
    }else {
        for (int i = 2; i <= com; i++) {
            status = stat(command[i - 1], &info);
            if (status != 0) {
                perror("Impossible to delete \n");
                return;
            }
            if (LetraTF(info.st_mode) == '-') { //si es file entonces https://man7.org/linux/man-pages/man2/unlink.2.html
                if (unlink(command[i - 1]) == -1) {
                    perror("Impossible to delete \n");
                }else {
                    printf("File %s has been delete\n", command[i - 1]);
                }
            }else if (LetraTF(info.st_mode) == 'd') { //directory
                //comprobar si es directory entonces https://man7.org/linux/man-pages/man2/rmdir.2.html
                if (rmdir(command[i - 1]) == 0) {
                    printf("Directory %s has been delete\n", command[i - 1]);
                }else if (errno == ENOTEMPTY) {
                    copies = copyfiles(command[i-1], aux); //copiamos
                    if (chdir(command[i-1]) == 0) { // cambiamos de directorio
                        ToDeleteTree(aux, copies);// llamada recursiva
                        chdir("..");//volvemos al directorio anterior para eliminarlo (directorio original)
                        if (rmdir(command[i-1]) != 0) {
                            perror("Impossible to delete \n");
                        }else {
                            printf("Directory %s has been delete\n", command[i - 1]);
                        }
                    } else {
                        perror("Impossible to delete \n");
                    }
                    if (copies > 1) {
                        for (int j = 1; j < copies; j++) { //vaciamos el array y liberamos espacio
                            free(aux[j]);
                            aux[j] = NULL;
                        }
                    }
                } else {
                    perror("Impossible to delete \n");
                }
            } else {
                perror("Impossible to delete \n");
            }
        }
    }
}


