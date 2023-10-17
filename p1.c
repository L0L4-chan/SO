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



void ShowStat(char * command[], int com) {
    bool lon = false;
    bool acc = false;
    bool link = false;

    if (com == 1) {
    char location[256]; //to store the location
    getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
    printf("%s\n", location);
    }
    else if (com == 2){
        for(int i = 1; i<com; i++){
            if(!strcmp(command[i], "-long")){
                lon=true;
            }
            if(!strcmp(command[i], "-acc")&& !acc){
                acc=true;
            }
            if( !strcmp(command[i], "-link")&& !link){
                link=true;
            }
        }
        if (lon||acc||link){
            char location[256]; //to store the location
            getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
            printf("%s\n", location);
        }
        else{
            const char *filename = command[1];
            struct stat file_info;
            if (lstat(filename, &file_info) == 0) {
                printf("%lld bytes\t%o\t%o\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\n", (long long)file_info.st_size,
                       file_info.st_mode, file_info.st_uid, file_info.st_blksize, file_info.st_blocks,
                       file_info.st_size, file_info.st_ino, file_info.st_dev, file_info.st_atim.tv_nsec,
                       file_info.st_atim.tv_nsec);
            } else {
                perror("Unrecognised object\n");
            }
        }
    }
    else if(com>2){
        int posicion;
        for(int i = 1; i<com; i++){
            if(!strcmp(command[i], "-long")&& !lon){
                lon=true;
            }
            if(!strcmp(command[i], "-acc")&& !acc){
                acc=true;
            }
            if( !strcmp(command[i], "-link")&& !link){
                link=true;
            }
           posicion = i+1;
        }
        for (int i = posicion; i<com ; i++) {
            if (lon == true){
                const char *filename = command[i];
                struct stat file_info;
                if (lstat(filename, &file_info) == 0) {
                    printf("%s\t%lld bytes\t%o\t%o\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\n", command[i],
                           (long long) file_info.st_size, file_info.st_mode, file_info.st_uid, file_info.st_blksize,
                           file_info.st_blocks, file_info.st_size, file_info.st_ino, file_info.st_dev,
                           file_info.st_atim.tv_nsec, file_info.st_atim.tv_nsec);
                }
            }
            else if(acc == true) {
                const char *filename = command[i];
                struct stat file_info;
                if (lstat(filename, &file_info) == 0) {
                    printf("%s\t%lld bytes", command[i],
                           (long long) file_info.st_size);
                }
            }
            else if (link == true){
                char location[256]; //to store the location
                getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
                printf("%s\n", location);
            }
            else
                perror("Unrecognised object\n");
        }
    }
    printf("it works\n"); //lstat
}

void ToList(char * command []){
    DIR * directory;
    char * location[256]; //to store the location
    struct dirent *entry;
    int files = 0;

    if (command[1] == NULL){//Si no se especifica un directorio que hacemos??
        getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
        while( (entry=readdir(location)) ){
            files++;
            printf("File %3d: %s\n", files, entry->d_name);
        }
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


//funcion auxiliar copiada
int copyfiles(char * path, char * command[]) {
    DIR *d;
    struct dirent *dir;
    int c = 1;

    d = opendir(path); // revisar si estamos consiguiendo el inodo
    if (d) { //si existe
        while ((dir = readdir(d)) != NULL) { //mientras haya contenido https://man7.org/linux/man-pages/man2/readdir.2.html
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) { //no queremos ni el propio ni el padre
                continue;
            } else {
                command[c] = (char *)malloc(strlen(dir->d_name) + 1); //reserva de memoria para el espacio del nombre
                strcpy(command[c], dir->d_name); // añadimos el nombre del contenido a la lista
                c++;//aumentamos el contador porque estamos en un while
            }
        }
        closedir(d); // se cierra
    }
    return c; //devolvemos el numero de elementos en la lista.
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


