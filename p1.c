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

            if(mkdir(command[1],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)==-1){
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


//función auxiliar printear path
void print_path (){
    char location[256]; //to store the location
    getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
    printf("%s\n", location);
}


void ShowStat(char * command[], int com) {
    bool lon = false;
    bool acc = false;
    bool link = false;
    struct dirent *entry;

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
    }

    if (com == 1) {
    print_path();
    }
    else if (com == 2){

        if (lon||acc||link){
            print_path();
        }
        else{
            const char *filename = command[1];
            struct stat file_info;
            if (lstat(filename, &file_info) == 0) { //https://linux.die.net/man/2/lstat
                printf("%ld bytes\t%s\n", file_info.st_size, command[1]);
            } else {
                perror("Unrecognised object\n");
            }
        }
    }
    else if(com>2){

        if (link == true) {
            print_path();
            char *document[] = {
                    "stat",
                    "-acc",
                    entry->d_name
            };
            ShowStat(document, 3);
        }

        int position;
        if (lon&&acc&&link)
            position = 4;
        else if ((lon&&acc&&!link)||(lon&&!acc&&link)||(!lon&&acc&&link))
            position = 3;
        else if ((lon&&!acc&&!link)||(!lon&&!acc&&link)||(!lon&&acc&&!link))
            position = 2;
        else
            position = 1;

        for (int i = position; i<com ; i++) {
            if (lon == true){
                const char *filename = command[i];
                struct stat file_info;
                if (lstat(filename, &file_info) == 0) {
                    printf("%ld\t%ld\t%ld\t%ld\t%o\t%o\t%o\t%ld\t%s\n", file_info.st_atim.tv_nsec,
                           file_info.st_mtim.tv_nsec, file_info.st_ino, file_info.st_dev, file_info.st_gid,
                           file_info.st_uid, file_info.st_mode, file_info.st_size, command[i]);
                }
            }
            else if((acc == true && lon == false)||(acc == false && lon == false)) {
                const char *filename = command[i];
                struct stat file_info;
                if (lstat(filename, &file_info) == 0) {
                    printf("%ld bytes\t%s\n", file_info.st_size, command[i]);
                }
            }
            else
                perror("access error. No such file or directory\n");
        }
    }
}


//función auxiliar para listar archivos directorio
void stat_directory(const char *path, bool longFormat, bool showHidden) {
    struct dirent *entry;
    struct stat info;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Error opening the directory\n");
    }
    while ((entry = readdir(dir)) != NULL) {//https://man7.org/linux/man-pages/man3/readdir.3.html
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);

        if (stat(fullpath, &info) == 0) {
            if ((info.st_mode & S_IFMT) == S_IFDIR) {
                if (showHidden || entry->d_name[0] != '.') {
                    if (longFormat) {
                        char *document[] = {
                                "stat",
                                "-long",
                                fullpath
                        };
                        ShowStat(document, 3);
                    } else {
                        char *document[] = {
                                "stat",
                                "-acc",
                                fullpath
                        };
                        ShowStat(document, 3);
                    }
                }
            } else if ((info.st_mode & S_IFMT) == S_IFREG) {
                if (showHidden || entry->d_name[0] != '.') {
                    if (longFormat) {
                        char *document[] = {
                                "stat",
                                "-long",
                                fullpath
                        };
                        ShowStat(document, 3);
                    } else {
                        char *document[] = {
                                "stat",
                                "-acc",
                                fullpath
                        };
                        ShowStat(document, 3);
                    }
                }
            }
        }
    }
    closedir(dir);
}

//funcion auxiliar para imprimir los archivos de forma recursiva
void ListFilesRecursively(const char *path, bool longFormat, bool showHidden) {
    struct dirent *entry;
    struct stat info;
    DIR *dir = opendir(path);
    printf("%s\n", path);

    if (dir == NULL) {
        perror("Error opening the directory\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Se ignoran los directorios padres para evitar la recursión infinita
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        //se guarda el path con el nombre del archivo para evaluar
        //https://www.geeksforgeeks.org/snprintf-c-library/
        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);


        if (stat(fullpath, &info) == 0) {
            if ((info.st_mode& S_IFMT) == S_IFDIR) {
                //comprobar si es directory entonces https://man7.org/linux/man-pages/man2/rmdir.2.html)
                ListFilesRecursively(fullpath, longFormat, showHidden);
            } else if ((info.st_mode& S_IFMT)==S_IFREG){
                    //si es file entonces https://man7.org/linux/man-pages/man2/unlink.2.html
                if (showHidden || entry->d_name[0] != '.') {
                    if (longFormat) {
                        char *document[] = {
                                "stat",
                                "-long",
                                fullpath
                        };
                        ShowStat(document, 3);
                    } else {
                        char *document[] = {
                                "stat",
                                "-acc",
                                fullpath
                        };
                        ShowStat(document, 3);
                    }
                }
            }
        }
    }

    closedir(dir);
}

void ListFilesRecursivelyBackwards(const char *path, bool longFormat, bool showHidden) {
    //almacenamiento de directorio actual
    char currentDir[PATH_MAX];
    getcwd(currentDir, sizeof(currentDir));

    if (chdir(path) != 0) {
        perror("Error changing directory\n");
        return;
    }

    ListFilesRecursively(".", longFormat, showHidden);

    if (chdir(currentDir) != 0) {
        perror("Error changing directory back\n");
    }
}


void ToList(char * command [], int com){

    bool reca = false;
    bool recb = false;
    bool hid = false;
    bool lon = false;
    bool acc = false;
    bool link = false;
    struct stat info;
    int position = 1;
    int longitud=1;

    for(int i = 1; i<com; i++){
        longitud ++;
        if(!strcmp(command[i], "-hid")){
            hid=true;
            position++;
        }
        if(!strcmp(command[i], "-recb")&& !acc){
            recb=true;
            position++;
        }
        if( !strcmp(command[i], "-reca")&& !link){
            reca=true;
            position++;
        }
        if(!strcmp(command[i], "-long")){
            lon=true;
            position++;
        }
        if(!strcmp(command[i], "-acc")&& !acc){
            acc=true;
            position++;
        }
        if( !strcmp(command[i], "-link")&& !link){
            link=true;
            position++;
        }
    }

    if (com==1||((com >= 2) && (position == com))){
        print_path();
    }

    else if ((com == 2) && (position != com)){
        stat(command[position],&info);
        if ((info.st_mode& S_IFMT) == S_IFDIR) {
            //comprobar si es directory entonces https://man7.org/linux/man-pages/man2/rmdir.2.html)
            stat_directory(command[position], false, false);
        }
        else if((info.st_mode& S_IFMT)==S_IFREG){
            //si es file entonces https://man7.org/linux/man-pages/man2/unlink.2.html
            command[0]="stat";
            ShowStat(command, com);
        }
        else
            perror("error al acceder:No such file or directory\n");
    }

    else if ((com > 2)&&(position < com)){

        struct dirent *entry;
        DIR *dir;

        for (int i = 1; i < com; i++) {
            if(reca){
                ListFilesRecursively(command[i], lon, hid);
            }
            else if(recb&&!reca){
                ListFilesRecursivelyBackwards(command[i], lon, hid);
            }
            else if (!reca&&!recb){
                if(LetraTF(info.st_mode)== 'd'){
                    //comprobar si es directory entonces https://man7.org/linux/man-pages/man2/rmdir.2.html
                    stat_directory(command[position], lon, hid);
                }
                else if(LetraTF(info.st_mode)== '-'){
                    //si es file entonces https://man7.org/linux/man-pages/man2/unlink.2.html
                    ShowStat(command[i], com);
                }

            }
        }
    }
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

