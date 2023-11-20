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

    if (com == 2 ) { //tamño de memoria a reservar
        int increment;
        if (( increment = atoi (command[1])!=0)){
            void * ptr;
          if((ptr = malloc(increment))!=NULL){
              tMemList block;
              block.addr = ptr;
              block.type = "malloc";
              block.size = increment;
              time_t t = time(NULL);
              struct tm tiempoLocal = *localtime(&t);
              char date[20];
              char *formato = "%H:%M:%S";
              int datebytes = strftime(date, sizeof date, formato, &tiempoLocal);
              if (datebytes != 0) {
                  block.date = date;
              } else {
                  perror("Output error\n");
              }
              insertItem(block, memLog);
              printf("%d of memory reserved at %p\n", increment,ptr);
          }
            perror("Reserve of memory could not be done\n");
       /* intptr_t increment = atoi(
                command[1]); //obtenemos el tamaño a incrementar, pendiente comprobar que esto no da error
        if ((f_address = sbrk(increment)) == -1) {
            perror("We could not reserve memory ");
        } else {

        tMemList block;
        block.addr = f_address;
        block.type = "malloc";
        block.size = increment;
        time_t t = time(NULL);
        struct tm tiempoLocal = *localtime(&t);
        char date[20];
        char *formato = "%H:%M:%S";
        int datebytes = strftime(date, sizeof date, formato, &tiempoLocal);
        if (datebytes != 0) {
            block.date = date;
        } else {
            perror("Output error\n");
        }
        insertItem(block, memLog);
    }*/
        }
    }else if (com ==  3){// free y el espacio a liberar
        if(!strcmp(command[1],"-free")){

            tPos pos = first(*memoryLog);
            while(pos!=NULL){
                tMemList * aux = (tMemList *)getItem(pos, *memoryLog);
                int increment = atoi(
                        command[2]);
                if(increment==aux->size){
                    insertItem(aux,fLog);
                    free(aux->addr);
                    printf("%d of memory free at %p\n", increment,aux->addr);
                    deleteAtPosition(pos, memoryLog);
                    return;
                }else{
                pos = next(pos, *memoryLog);
                }
            }
                perror("could not free memory");
            }
        }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");


}
void Make_Shared(char * command[], int com){
//https://man7.org/linux/man-pages/man2/shmget.2.html

    if (com == 2 ){ //free delkey  y la clave

    }else if (com ==  3){  //create clave y tamaño

    }else{

    }


}
void Make_Mmap(char * command [], int com){
//https://man7.org/linux/man-pages/man2/mmap.2.html

    if (com == 3 ){// -free y nombre del fichero  sera mayor y la otra son el nombre del fichero y los permisos

    }else{

    }

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

//"memdump addr cont\tDump on screen contents (cont bytes) of memory position addr
void Make_Memdump(char * command[], int com){
    int cont;
    if (com == 1)
        return;
    else if(com == 2){
        cont = 25;

    }
    else{
        cont = (int) command[2];


    }

}


void Make_Memfill(char * command[], int com){
    size_t tam = (size_t) command[2];
    unsigned char bytefill = (unsigned char) command[3];
    if (com==1)
        return;
    else {
        if (com==2)
            LlenarMemoria(command[1], 25, 41);
        else if (com == 3)
            LlenarMemoria(command[1], tam, 41);
        else
            LlenarMemoria(command[1], tam, bytefill);
    }
}

//"mem [-blocks|-funcs|-vars|all|-pmap]...\tShows processs memory detalils\n"
//                   "\t-blocks: memory blocks allocated\n"
//                   "\t-funcs: function adresses\n"
//                   "\t-vars: variable addresses\n"
//                   "\t-all: all information available\n"
//                   "\t-pmap: shows the pmap command output (or similar)\n");
void ToMem(char * command[], int com){
    bool blocks = false;
    bool funcs = false;
    bool vars = false;
    bool pmap = false;

    for(int i = 1; i<com; i++){
        if(!strcmp(command[i], "-blocks")&& !blocks){
            blocks=true;
        }
        if(!strcmp(command[i], "-funcs")&& !funcs){
            funcs=true;
        }
        if( !strcmp(command[i], "-vars")&& !vars){
            vars=true;
        }
        if( !strcmp(command[i], "-pmap")&& !pmap){
            pmap=true;
        }
        if( !strcmp(command[i], "-all")){
            blocks=true;
            funcs=true;
            vars=true;
        }
    }

    if (blocks){

    }
    if (funcs){

    }
    if (vars){

    }
    if (pmap){
        Do_MemPmap();
    }
}


void ToRecurse(char * command[], int com){
    if (com == 1)
        return;
    else if (com > 1){
        if (command[1]>=0)
            Recursiva((int) command[1]);
        else
            Recursiva(0);
    }
}

