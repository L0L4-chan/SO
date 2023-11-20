//
// Created by lola on 30/10/23.
//

#include <dirent.h>
#include "p0.h"
#include "ayuda2.c"


void Make_Malloc(char * command[], int com){
//https://man7.org/linux/man-pages/man2/brk.2.html
//https://man7.org/linux/man-pages/man2/mmap.2.html

    if (com == 2 ) { //tamño de memoria a reservar
        int increment;
            increment = atoi (command[1]);
            void * ptr;
          if((ptr = malloc(increment))!=NULL){
              tMemList * block = malloc(sizeof( tMemList));
              block->addr = ptr;
              strcpy(block->type,"malloc");
              block->size = increment;
              time_t t = time(NULL);
              struct tm tiempoLocal = *localtime(&t);
              char date[20];
              char *formato = "%H:%M:%S";
              int datebytes = strftime(date, sizeof date, formato, &tiempoLocal);
              if (datebytes != 0) {
                  strcpy(block->date, date);
              } else {
                  perror("Output error\n");
              }
              insertItem(block, memLog);
              printf("%d of memory reserved at %p\n", increment,ptr);
              return;
          }else{
            perror("Reserve of memory could not be done\n");
            return;
          }
    }else if (com ==  3){// free y el espacio a liberar
        if(!strcmp(command[1],"-free")){

            tPos pos = first(memoryLog);
            while(pos!=NULL){
                tMemList * aux = (tMemList *)getItem(pos, memoryLog);
                int increment = atoi(
                        command[2]);
                if(increment==aux->size){
                    if((!strcmp(aux->type,"malloc"))){
                        insertItem(&aux,fLog);
                        free(aux->addr);
                        printf("%d of memory free at %p\n", increment,aux->addr);
                        deleteAtPosition(pos, memLog);
                    return;
                    }
                }else{
                pos = next(pos, memoryLog);
                }
            }
        }
                perror("could not free memory");
            return;
            }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }




void Make_Shared(char * command[], int com) {
//https://man7.org/linux/man-pages/man2/shmget.2.html

    if(com==2){
        int id;
        key_t clave = (key_t)  strtoul(command[1],NULL,10);
        if (( id=shmget(clave,0,0666))==-1){
            perror ("shmget: impossible to obtain shared memory\n");
            return;
        }else{
            int p = IPC_CREAT | IPC_EXCL;
            shmat(id,NULL, p);
        }

    }else if (com == 3) {  //create clave y tamaño
            if (!strcmp(command[1], "-free")) {
                tPos pos = first(memoryLog);
                while (pos != NULL) {
                    tMemList *aux = (tMemList *) getItem(pos, memoryLog);
                    if (!strcmp(command[2], aux->key)) {
                        shmdt(aux->addr);
                        printf("Shared memory at %p has been delete\n", aux->addr);
                        deleteAtPosition(pos, memLog);
                        return;
                    }
                    pos = next(pos, memoryLog);
                }
            } else if (!strcmp(command[1], "-delkey")) {
                tPos pos = first(memoryLog);
                while (pos != NULL) {
                    tMemList *aux = (tMemList *) getItem(pos, memoryLog);
                    if (!strcmp(command[2], aux->key)) {
                        SharedDelkey(command);
                        printf("Shared memory with key %s has been delete form map\n", aux->key);
                        return;
                    }
                    pos = next(pos, memoryLog);
                }
                perror("there is not share memory with this key \n");
            }
        } else if (com == 4) {
           if (!strcmp(command[1], "-create")){
            SharedCreate(command);
            return;
            }
       }
        printf("Unrecognized command, please try again or write \"help\" for help.\n");

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
    }
            size_t e =(size_t) atoi(command[3]);
            void * buff = cadtop(command[2]);
            if((rd = LeerFichero(command[1],buff,e))==-1){
                perror("Impossible to read file\n");
            }else{
                printf("From file %s has been read %zd bytes into %p\n", command[1], rd, buff);
            }

}

void ToWrite(char * command[], int com){
    ssize_t n;

    if (com == 4) {
        size_t  rd = (size_t) atoi(command [3]);
        void * buff = cadtop(command[2]);
        if ((n = EscribirFichero(command[1],buff,rd,0))==-1){
            perror("Impossible to write\n");
        }else{
            printf("%d b has been written on file %s\n", n,command[1]);
        }
        return;
    }else if(com == 5){
        if (!strcmp(command[1], "-o")){
        size_t  rd = (size_t) atoi(command [4]);
            void * buff = cadtop(command[3]);
            if ((n = EscribirFichero(command[2],buff,rd,1))==-1){
                perror("Impossible to write\n");
            }else{
                printf("%d b has been written on file %s\n", n,command[1]);
            }
            return;
        }
    }else{
        perror("Not enough parameters");
        return;
    }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");

}


void Make_Memdump(char * command[], int com){


}


void Make_Memfill(char * command[], int com){


}


void ToMem(char * command[], int com){


}


void ToRecurse(char * command[], int com){


}

