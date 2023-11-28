//
// Created by lola on 25/11/23.
//

#include <pwd.h>
#include "p0.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "ayuda3.c"



void SetUID(char* command[], int index){
    if(index ==1){ // credencial real y efectiva del usuario https://man7.org/linux/man-pages/man2/getuid.2.html
       uid_t  real = getuid();
       uid_t effective = geteuid();
        //printf("%d\n", real);
       struct passwd real_p= * getpwuid(real);
       struct passwd effe_p= * getpwuid(effective);
       printf("Real user: %s \n",  real_p.pw_name);
       printf("Effective user: %s \n",  effe_p.pw_name );

    }else if(index ==2 ){// credencial real y efectiva del usuario  get
        if(!strcmp(command[1], "-get")) {
            SetUID(command, 1);
            return;
        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
            return;
        }
    }else if(index == 3){ // set id (numerico) y un numero cambia la credencial https://man7.org/linux/man-pages/man2/setuid.2.html
        if(!strcmp(command[1], "-set")) {
            uid_t id = (uid_t) atoi(command[2]);
            if(setuid(id)==0){
                printf("User %s has been set as effective user\n", command[2]);
                return;
            }else{
                perror("impossible to performance this action\n");
                return;
            }

        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
            return;
        }
    }else if(index == 4){ // set -l id (numerico)  establece la credencial a ligin id
        if(!strcmp(command[1], "-set") &&!strcmp(command[2], "-l") ) {
            struct passwd nw = *getpwnam(command[3]);
            if(setuid(nw.pw_uid)==0){
                printf("User %s has been set as effective user\n", command[3]);
                return;
            }else{
                perror("impossible to performance this action\n");
                return;
            }
        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
            return;
        }
    }else {
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
        return;
    }
}
void ToShowVar(char* command[], int index){
    int i= 0;
    if(index==1){
        while(envi[i]!=NULL){
            printf("main arg3[%d] = %s   %p\n", i, envi[i], &envi[i]);
            i++;
        }
        return;
    }else if(index==2){
        if ((i = BuscarVariable(command[1], envi))!= (-1)){
            printf("main arg3[%d] =  %s   %p\n", i, envi[i], &envi[i]);
            char * geten = getenv(command[1]);//https://man7.org/linux/man-pages/man3/getenv.3.html
            printf("getenv =  %s   %p\n", geten, &geten);
            extern char **environ; //preguntar por que es la misma que main arg
            i = BuscarVariable(command[1],environ );
            printf("main arg3[%d] =  %s   %p\n", i, environ[i], &environ[i]);
            return;
        }
        printf("Unrecognized environment variable\n");
        return;
    }else{
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
        return;
    }
}

void ToChangeVar(char* command[], int index){ //https://man7.org/linux/man-pages/man3/setenv.3.html
    if(index==4){
        if(!strcmp(command[1], "-a")){
            CambiarVariable(command[2],command[3], envi);
            printf("Variable %s change using main arg3", command[2]);
            return;
        }else if(!strcmp(command[1], "-p")) {
            char s[MAXSIZE];
            strcat(s,command[2]);
            strcat(s,"=");
            strcat(s,command[3]);
            putenv(s);
            printf("Variable %s change using putenv", command[2]);
            return;
        }else if(!strcmp(command[1], "-e")) {
            extern char **environ; //preguntar por que es la misma que main
            CambiarVariable(command[2],command[3], environ);
            printf("Variable %s change using environ", command[2]);
        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        return;
        }
    }else{
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
        return;
    }
}

void ToSubVar(char* command[], int index){
    if(index==4){
        int i = 0;
        char s[MAXSIZE];
        char * aux[MAXSIZE];
        if(!strcmp(command[1], "-a")){
           i =  BuscarVariable(command[2], envi);
            SliceEntry(envi[1],aux,"=");
            strcat(s,command[3]);
            strcat(s,"=");
            strcat(s,aux[1]);
            //el resto igual
            envi[i] = s;
            return;
        }else if(!strcmp(command[1], "-e")) {
            extern char **environ;
            i = BuscarVariable(command[2], environ);
            //pendiente dividir el string y volver a componerlo antes de almacenarlo
            SliceEntry(envi[1],aux,"=");
            strcat(s,command[3]);
            strcat(s,"=");
            strcat(s,aux[1]);
            //el resto igual
            environ[i] = s;
            return;
        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
            return;
        }
    }else{
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
        return;
    }
}
void ToShowEnv(char* command[], int index){
    int i= 0;
    if(index==1){
        while(envi[i]!=NULL){
            printf("main arg3[%d] = %s   %p\n", i, envi[i], &envi[i]);
            i++;
        }
        return;
    }else if(index==2){
        extern char **environ; //preguntar por que es la misma que main arg
        if(!strcmp(command[1], "-environ")){
            while(environ[i]!=NULL){
                printf("environ[%d] = %s   %p\n", i, environ[i], &environ[i]);
                i++;
            }
            return;
        }else if(!strcmp(command[1], "-addr")) { //preguntar por este comando
            printf("environ = %p, is storage at  %p\n",  environ, &environ);
            printf("main arg3 =  %p, is storage at %p\n", envi, &envi);
            return;
        }

        printf("Unrecognized environment variable\n");
        return;
    }else{
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
        return;
    }
}

void SetFork(char* command[], int index){}
void SetEXEC(char* command[], int index){}
void ToJobS(char* command[], int index){}
void ToDelJobs(char* command[], int index){}
void ToJob(char* command[], int index){}
 //codigo proporcionado en la web de la asignatura
void ToUnknow1(char* command[], int index){
    int pplano=0;
    pid_t pid;
    if (!strcmp(command[1],"&")) {
        pplano = 1;
        printf("exec %s on banckground\n", command[0]);
    }
    if ((pid=fork())==0) {
        char path[MAXSIZE] = "/usr/bin/";
        strcat(path,command[0]);

        if (execl(path, command[0], "-update", "1",NULL)==-1){
            perror ("Cannot be execute\n");
        }
        if (kill (getppid(),SIGTERM)==-1) {  /*terminamos el proceso padre*/
            perror("Error on kill\n");
        }
        exit(0);
    }
    if (pplano)
        waitpid(pid,NULL,0);
}
