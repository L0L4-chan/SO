//
// Created by lola on 30/10/23.
//

#include <sys/stat.h>
#include <dirent.h>
#include "p2.h"
#include "p1.h"
#include "p0.h"
#include "ayuda1.c"
#include "ayuda2.c"

void Make_Malloc(char * command[], int com){
//https://man7.org/linux/man-pages/man2/brk.2.html
//https://man7.org/linux/man-pages/man2/mmap.2.html
}
void Make_Sharec(char * command[], int com){
//https://man7.org/linux/man-pages/man2/shmget.2.html

}
void Make_Mmap(char * command [], int com){
//https://man7.org/linux/man-pages/man2/mmap.2.html
}
void ToRead(char * command[], int com){
    int df;
    ssize_t  rd;
    if (com != 4){
        perror("Not enough parameters");
    }else{
        if ((df = open(command[1], O_RDONLY)) == -1) {
            perror("Impossible to read file\n");
        }else{
            if((rd = read(df, command[2],(size_t) command[3]))== -1){
                close(df);
                perror("Impossible to read file\n");
            }else{
                close(df);
                printf("From file %s has been read %zd bytes into %s", command[1], rd, command[2]);
            }
        }
    }
}

void ToWrite(char * command[], int com){
    int df;
    ssize_t  rd;
    if (com == 4) {
        if ((df = open(command[1], O_WRONLY|O_CREAT|O_EXCL)) == -1) {
            perror("Impossible to write file\n");
        } else {
            if ((rd = write(df, command[2], (size_t) command[3])) == -1) {
                perror("Impossible to write file\n");
            } else {
                close(df);
                printf("From file %s has been written %zd bytes from %s", command[1], rd, command[2]);
            }
        }
    }else if(com == 5){
        if (!strcmp(command[1], "-o")){
            if ((df = open(command[2], O_CREAT | O_WRONLY | O_TRUNC)) == -1) {
                perror("Impossible to write file\n");
            }else if ((rd = write(df, command[3], (size_t) command[4])) == -1) {
                close(df);
                perror("Impossible to write file\n");
            } else {
                close(df);
                printf("From file %s has been re-written %zd bytes", command[2], rd);
            }





        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }

    }else{
        perror("Not enough parameters");

    }
}