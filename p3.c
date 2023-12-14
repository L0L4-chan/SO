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

void SetFork(){
    pid_t pid;

    if ((pid=fork())==0){
        printf("New process execution %d\n", getpid());

        char *args[] = {"./p3", NULL}; // Nombre del programa compilado
        execvp(args[0], args);


        perror("exec\n");
        exit(EXIT_FAILURE);
    }
    else if (pid!=-1) {
        waitpid(pid, NULL, 0);
        return;

    }else {
        printf("Error creating child process.\n");
        return;
    }
}


void SetEXEC(char* command[], int com) {
    pid_t pid = fork(); // Creamos un nuevo proceso

    if (pid == 0) {
        // Este es el proceso hijo
        char *args[com]; // Array para almacenar el comando y sus argumentos
        int i;

        // Construye el array de argumentos para execvp
        for (i = 1; i < com; ++i) {
            args[i - 1] = command[i];
        }
        args[com - 1] = NULL; // Establece el último elemento del array como NULL, requerido por execvp

        // Ejecuta el comando proporcionado en el proceso hijo
        if (execvp(args[0], args) == -1) {
            perror("error executing exec function\n");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // Este es el proceso padre
        int status;
        waitpid(pid, &status, 0); // Espera a que el proceso hijo termine
        printf("\n");
    } else {
        // Error al crear el proceso hijo
        perror("\n");
        exit(EXIT_FAILURE);
    }
}



void ToJobS(char* command[], int index){ // mensaje de si la primera asignacion es null
    tBackgroundNode *current = backgroundProcesses;
    if (current == NULL){
        printf("There is no proccess running\n");
    }
    else{
        while (current != NULL) {
            printf("PID: %d | Date: %s | Status: %d | Priority: %d\n",
                   current->process.pid, current->process.date, current->process.status, current->process.priority);
            current = current->next;
        }
    }
}

void ToDelJobs(char* command[], int com){
    bool finished = false;
    bool signaled = false;

    for (int i = 1; i < com; i++) {
        if (!strcmp(command[i], "-terms") && !finished) {
            finished = true;
        }
        if (!strcmp(command[i], "-sig") && !signaled) {
            signaled = true;
        }
    }
    if(com ==1){
        deleteList(activeproc);
        createEmptyList(activeproc);
    }else {
        tBackgroundNode *current = backgroundProcesses;
        tBackgroundNode *prev = NULL;
        if (finished) {
            while (current != NULL) {
                if (current->process.status == FINISHED) {
                    if (prev == NULL) {
                        backgroundProcesses = current->next;
                        free(current);
                        current = backgroundProcesses;
                    } else {
                        prev->next = current->next;
                        free(current);
                        current = prev->next;
                    }
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        }
        if (signaled) {
            while (current != NULL) {
                if (current->process.status == SIGNALED) {
                    if (prev == NULL) {
                        backgroundProcesses = current->next;
                        free(current);
                        current = backgroundProcesses;
                    } else {
                        prev->next = current->next;
                        free(current);
                        current = prev->next;
                    }
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        }
    }
}

void ToJob(char* command[], int com){
    bool fg = false;

    for (int i = 1; i < com; i++) {
        if (!strcmp(command[i], "-fg") && !fg) {
            fg = true;
        }
    }
    if (com == 1){
        printf("Not enough parametres\n");
        return;
    }
    else {
        tBackgroundNode *current = backgroundProcesses;
        if (com == 2) {
            int pid = atoi(command[1]);
            while (current != NULL) {
                if (current->process.pid == pid) {
                    printf("Process Information:\n");
                    printf("PID: %d | Date: %s | Status: %d | Command: %s | Priority: %d\n",
                           current->process.pid, current->process.date, current->process.status,
                           current->process.commandLine, current->process.priority);
                }
            }
        }
        else if (com >= 3 && -fg == true) {
            int pid = atoi(command[2]);
            current->process.foreground = false;
            printf("Moving process to foreground...\n");
            while (current != NULL) {
                if (current->process.pid == pid) {
                    printf("Process Information:\n");
                    printf("PID: %d | Date: %s | Status: %d | Command: %s | Priority: %d\n",
                           current->process.pid, current->process.date, current->process.status,
                           current->process.commandLine, current->process.priority);
                    current->process.foreground = true;
                }
            }
        }
        else{
            printf("Arguments not valid\n");
        }
    }
}

void initializeBackgroundList() {
    backgroundProcesses = NULL;
}

void addToBackgroundList(BackgroundProcess process) {
    tBackgroundNode *newNode = malloc(sizeof(tBackgroundNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->process = process;
    newNode->next = NULL;

    if (backgroundProcesses == NULL) {
        backgroundProcesses = newNode;
    } else {
        tBackgroundNode *temp = backgroundProcesses;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void removeFromBackgroundList(int pid) {
    tBackgroundNode *current = backgroundProcesses;
    tBackgroundNode *prev = NULL;

    while (current != NULL) {
        if (current->process.pid == pid) {
            if (prev == NULL) {
                backgroundProcesses = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}


 void ToUnknow1(char* command[], int index) {
     pid_t pid;
     bool foreground = true;

     if (strcmp(command[index-1], "&") == 0) {
         foreground = false;
     }

     if ((pid = fork()) == 0) {
         char path[MAXSIZE] = "/usr/bin/";
         strcat(path, command[0]);

         if (execvp(command[0], command) == -1) {
             printf("Cannot execute command\n");
             exit(EXIT_FAILURE);
         }
     } else if (pid < 0) {
         printf("Fork error\n");
     } else {
         if (foreground) {
             int status;
             waitpid(pid, &status, 0);
         } else {
             printf("Process %d running in background\n", pid);
             // Crear una instancia de BackgroundProcess
             BackgroundProcess newProcess;
             newProcess.pid = pid;
             newProcess.commandLine = command[0];
             time_t t = time(NULL);
             struct tm tiempoLocal = *localtime(&t);
             char date[80];
             char *formato = "%H:%M:%S";
             int datebytes = (int)strftime(date, sizeof date, formato, &tiempoLocal);
             if (datebytes != 0)
                 strcpy(newProcess.date,date);
             newProcess.priority = false;

             for (int i = 1; i < index; i++) {
                 if (!strcmp(command[i], "finished"))
                     newProcess.status = 0;
                 else if (!strcmp(command[i], "signaled"))
                     newProcess.status = 2;
                 else if (!strcmp(command[i], "stopped"))
                     newProcess.status = 1;
                 else if (!strcmp(command[i], "active"))
                     newProcess.status = 3;
                 else
                     newProcess.status = 0;
             }

             addToBackgroundList(newProcess);
         }
     }
 }


