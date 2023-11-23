//
// Created by lola on 30/10/23.
//

#include <dirent.h>
#include <ctype.h>
#include "p0.h"
#include "ayuda2.c"

int globalVar1, globalVar2, globalVar3;
int globalVar4=1, globalVar5 = 23, globalVar6 = 435;


void Make_Malloc(char * command[], int com) {
//https://man7.org/linux/man-pages/man2/brk.2.html
//https://man7.org/linux/man-pages/man2/mmap.2.html
      if(com == 1){

          ImprimirListaMalloc();

      }else if (com == 2 ) { //tamño de memoria a reservar
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
            printf("%ld b has been written on file %s\n", n,command[1]);
        }
        return;
    }else if(com == 5){
        if (!strcmp(command[1], "-o")){
        size_t  rd = (size_t) atoi(command [4]);
            void * buff = cadtop(command[3]);
            if ((n = EscribirFichero(command[2],buff,rd,1))==-1){
                perror("Impossible to write\n");
            }else{
                printf("%ld b has been written on file %s\n", n,command[1]);
            }
            return;
        }
    }else{
        perror("Not enough parameters\n");
        return;
    }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");

}


void Make_Memdump(char * command[], int com){

    if (com==1){
        return;
    }
    if (com == 2){
        char *addr_str = command[1];
        void *addr = (void *)strtoul(addr_str, NULL, 16);
        size_t cont = 25;

        printf("Dumping %ld bytes from address %p\n", cont, addr);

        unsigned char *ptr = (unsigned char *)addr;
        size_t i;
        for (i = 0; i < cont; ++i) {
            // Imprimir el valor en formato hexadecimal
            printf("%X ", ptr[i]);

            // Imprimir el valor como carácter si es imprimible
            if (isprint(ptr[i])) {
                printf("%c ", ptr[i]);
            } else {
                // Mostrar caracteres de control comunes de manera amigable
                switch (ptr[i]) {
                    case '\n':
                        printf("\\n ");
                        break;
                    case '\r':
                        printf("\\r ");
                        break;
                    case '\t':
                        printf("\\t ");
                        break;
                    case '\0':
                        printf("\\0 ");
                        break;
                    default:
                        printf("   "); // Si no es imprimible, imprimir espacio en blanco
                        break;
                }
            }
        }
        printf("\n");
    }
    if (com>2){
        char *addr_str = command[1];
        char *cont_str = command[2];
        void *addr = (void *)strtoul(addr_str, NULL, 16);
        size_t cont = strtoul(cont_str, NULL, 10);

        printf("Dumping %ld bytes from address %p\n", cont, addr);

        unsigned char *ptr = (unsigned char *)addr;
        size_t i;
        for (i = 0; i < cont; ++i) {
            // Imprimir el valor en formato hexadecimal
            printf("%X ", ptr[i]);

            // Imprimir el valor como carácter si es imprimible
            if (isprint(ptr[i])) {
                printf("%c ", ptr[i]);
            } else {
                // Mostrar caracteres de control comunes de manera amigable
                switch (ptr[i]) {
                    case '\n':
                        printf("\\n ");
                        break;
                    case '\r':
                        printf("\\r ");
                        break;
                    case '\t':
                        printf("\\t ");
                        break;
                    case '\0':
                        printf("\\0 ");
                        break;
                    default:
                        printf("   "); // Si no es imprimible, imprimir espacio en blanco
                        break;
                }
            }
            if ((i + 1) % 25 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
}


void Make_Memfill(char * command[], int com){

    char *addr_str = command[1];
    char *cont_str = command[2];
    char *byte_str = command[3];

    if (com == 1) {
        return;
    }

    if (com == 2){
        void *addr = (void *)strtoul(addr_str, NULL, 16);
        size_t cont = 128;
        unsigned char byte = 'A';
        printf("Filling %ld bytes with byte %c(%X) from address %p\n", cont, byte, byte, addr);
        LlenarMemoria(addr, cont, byte);
    }
    if (com == 3){
        void *addr = (void *)strtoul(addr_str, NULL, 16);
        size_t cont = strtoul(cont_str, NULL, 10);
        unsigned char byte = 'A';
        printf("Filling %ld bytes with byte %c(%d) from address %p\n", cont, byte, byte, addr);
        LlenarMemoria(addr, cont, byte);
    }
    if (com >= 4){
        void *addr = (void *)strtoul(addr_str, NULL, 16);
        size_t cont = strtoul(cont_str, NULL, 10);
        unsigned char byte = *byte_str;
        printf("Filling %ld bytes with byte %c(%d) from address %p\n", cont, byte, byte, addr);
        LlenarMemoria(addr, cont, byte);
    }
}



void ToMem(char * command[], int com) {

    bool blocks = false;
    bool funcs = false;
    bool vars = false;
    bool pmap = false;

    for (int i = 1; i < com; i++) {
        if (!strcmp(command[i], "-blocks") && !blocks) {
            blocks = true;
        }
        if (!strcmp(command[i], "-funcs") && !funcs) {
            funcs = true;
        }
        if (!strcmp(command[i], "-vars") && !vars) {
            vars = true;
        }
        if (!strcmp(command[i], "-pmap") && !pmap) {
            pmap = true;
        }
        if (!strcmp(command[i], "-all")) {
            blocks = true;
            funcs = true;
            vars = true;
        }
    }
    if (blocks) {
        ImprimirListaMmap();
    }
    if (vars){
        int localVar1, localVar2, localVar3; // Variable local
        static int staticVar1, staticVar2, staticVar3; // Variable estática
        static int staticVar4 = 7, staticVar5 = 657, staticVar6 = -43; // Variable estáticainicializadas

        // Direcciones de variables
        printf("Local var\t\t\t%p,\t%p,\t%p\n", (void *)&localVar1, (void *)&localVar2, (void *)&localVar3);
        printf("Global var\t\t\t%p,\t%p,\t%p\n", (void *)&globalVar4, (void *)&globalVar5, (void *)&globalVar6);
        printf("Global (N.I.) var\t%p,\t%p,\t%p\n", (void *)&globalVar1, (void *)&globalVar2, (void *)&globalVar3);
        printf("Static var\t\t\t%p,\t%p,\t%p\n", (void *)&staticVar4, (void *)&staticVar5, (void *)&staticVar6);
        printf("Static (N.I.)var\t%p,\t%p,\t%p\n", (void *)&staticVar1, (void *)&staticVar2, (void *)&staticVar3);
    }
    if (funcs) {
        printf("Program functions\t%p,\t%p,\t%p\n", (void *) ToMem, (void *) ToWrite, (void *) ToRead);
        printf("Library functions\t%p,\t%p,\t%p\n", (void *) printf, (void *) scanf, (void *) malloc);
    }
    if (pmap){
        Do_MemPmap();
    }
}


void ToRecurse(char * command[], int com){

    if (com == 1)
        return;
    else if (com > 1){
        int n =abs( atoi(command[1]));
        if (n>=0)
            Recursiva(n);
        else
            Recursiva(0);
    }
}


