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
            return;
        }
    }
    char location[256]; //to store the location
    getcwd(location, sizeof(location));
    strcpy(location, command[1]);
    int mode, i; //to review the permits
    for (i = 2; command[i] != NULL; i++) {
        if (!strcmp(command[i], "cr")) {
            mode |= O_CREAT;
        } else if (!strcmp(command[i], "ex")) {
            mode |= O_EXCL;
        } else if (!strcmp(command[i], "ro")) {
            mode |= O_RDONLY;
        } else if (!strcmp(command[i], "wo")) {
            mode |= O_WRONLY;
        } else if (!strcmp(command[i], "rw")) {
            mode |= O_RDWR;
        } else if (!strcmp(command[i], "ap")) {
            mode |= O_APPEND;
        } else if (!strcmp(command[i], "command")) {
            mode |= O_TRUNC;
        }
    }
    mkdir(location,mode);//https://man7.org/linux/man-pages/man2/mkdir.2.html
}

void ShowStat(){
    printf("it works");
}
void ToList(){
    printf("it works");
}
void ToDelete(){
    printf("it works");
}
void ToDeleteTree(){
    printf("it works");
}
