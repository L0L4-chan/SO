//
// Created by lola on 30/10/23.
//

#include <sys/stat.h>
#include <dirent.h>
#include "p0.h"


void Make_Malloc(char * command[], int com){
//https://man7.org/linux/man-pages/man2/brk.2.html
//https://man7.org/linux/man-pages/man2/mmap.2.html

    if (com == 2 ) { //tamño de memoria a reservar
        int increment;
        if (( increment = atoi (command[1])!=0)){
            void * ptr;
          if((ptr = malloc(increment))!=NULL){
              tMemList * block;
              block->addr = ptr;
              block->type = "malloc";
              block->size = increment;
              time_t t = time(NULL);
              struct tm tiempoLocal = *localtime(&t);
              char date[20];
              char *formato = "%H:%M:%S";
              int datebytes = strftime(date, sizeof date, formato, &tiempoLocal);
              if (datebytes != 0) {
                  block->date = date;
              } else {
                  perror("Output error\n");
              }
              insertItem(block, memLog);
              printf("%d of memory reserved at %p\n", increment,ptr);
          }
            perror("Reserve of memory could not be done\n");
        }
    }else if (com ==  3){// free y el espacio a liberar
        if(!strcmp(command[1],"-free")){

            tPos pos = first(memoryLog);
            while(pos!=NULL){
                tMemList * aux = (tMemList *)getItem(pos, memoryLog);
                int increment = atoi(
                        command[2]);
                if(increment==aux->size){
                    insertItem(aux,fLog);
                    free(aux->addr);
                    printf("%d of memory free at %p\n", increment,aux->addr);
                    deleteAtPosition(pos, memLog);
                    return;
                }else{
                pos = next(pos, memoryLog);
                }
            }
                perror("could not free memory");
            }
        }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");


}
void Make_Shared(char * command[], int com) {
//https://man7.org/linux/man-pages/man2/shmget.2.html

   if (com == 3) {  //create clave y tamaño
        if (!strcmp(command[1], "-free")) {
            tPos pos = first(memoryLog);
            while (pos != NULL) {
                tMemList *aux = (tMemList *) getItem(pos, memoryLog);
                if (!strcmp(command[2], aux->key)) {
                    printf("Shared memory at %p has been delete\n", aux->addr);
                    deleteAtPosition(pos, memLog);
                    return;
                }
                next(pos, memoryLog);
            }
        } else if (!strcmp(command[1], "-delkey")) {
            tPos pos = first(memoryLog);
            while (pos != NULL) {
                tMemList *aux = (tMemList *) getItem(pos, memoryLog);
                if (!strcmp(command[2], aux->key)) {
                    printf("Shared memory with key %p has been delete form map\n", aux->key);
                    free(aux->addr);
                    return;
                }
                next(pos, memoryLog);
            }
        }
    } else if (com == 4) {
        SharedCreate(command);
    }
}

void Make_Mmap(char * command [], int com){
//https://man7.org/linux/man-pages/man2/mmap.2.html
    CmdMmap(command);

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


void Make_Memdump(char * command[], int com){


}


void Make_Memfill(char * command[], int com){


}


void ToMem(char * command[], int com){


}


void ToRecurse(char * command[], int com){


}

