//
// Created by lola on 24/11/23.
//
/*el siguiente codigo se da como ayuda por si se quiere utilizar*/
/*NO ES OBLIGATORIO USARLO*/
/*y pueden usarse funciones enteras o parte de funciones */

/*Este fichero, ayudaP3.c no estÃ¡ pensado para ser compilado separadamente */
/*, entre otras cosas, no contiene los includes necesarios*/
/*y las constantes utilizadas, no estÃ¡n definidas en Ã©l*/
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include "p0.h"


void initializeBackgroundList() {
    backgroundProcesses = NULL;
}

void addToBackgroundList(BackgroundProcess process) {
    tBackgroundNode *newNode = malloc(sizeof(tBackgroundNode));
    newNode->process = process;
    newNode->next = backgroundProcesses;
    backgroundProcesses = newNode;
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


void Cmd_fork(char *commandLine) {
    pid_t pid;
    time_t currentTime;
    time(&currentTime);
    char *date = ctime(&currentTime); // Obtener la fecha y hora actual

    // Eliminar el salto de línea al final de la fecha
    date[strlen(date) - 1] = '\0';

    if ((pid = fork()) == 0) {
        // Código del proceso hijo
        // Ejecutar el comando en el proceso hijo
        // Supongamos que el comando se pasa como argumento a esta función

        // Ejecutar el comando
        // Por ejemplo:
        // execlp("/bin/ls", "ls", "-l", NULL);
    } else if (pid > 0) {
        // Código del proceso padre
        BackgroundProcess newProcess;
        newProcess.pid = pid;
        strcpy(newProcess.date, date);
        newProcess.status = ACTIVE;
        newProcess.returnValue = 0; // O algún valor por defecto
        newProcess.commandLine = strdup(commandLine); // Duplicar el comando para almacenarlo
        newProcess.priority = false; // Establecer la prioridad según sea necesario

        addToBackgroundList(newProcess);

        waitpid(pid, NULL, 0); // Esperar a que el proceso hijo termine

        // Actualizar el estado del proceso en la lista
        // Aquí puedes usar información como el estado de salida del proceso hijo
        // Si tienes la información del estado de salida o la señal, puedes actualizarla aquí
        // Por ejemplo:
        // newProcess.status = FINISHED;
        // newProcess.returnValue = 0; // O el valor de salida del proceso hijo

        removeFromBackgroundList(pid); // Eliminar el proceso de la lista
    } else {
        // Error al crear el proceso hijo
        printf("Error creating child process.\n");
    }
}

int BuscarVariable (char * var, char *e[])  /*busca una variable en el entorno que se le pasa como parÃ¡metro*/
{
    int pos=0;
    char aux[MAXSIZE];

    strcpy (aux,var);
    strcat (aux,"=");

    while (e[pos]!=NULL)
        if (!strncmp(e[pos],aux,strlen(aux)))
            return (pos);
        else
            pos++;
    errno=ENOENT;   /*no hay tal variable*/
    return(-1);
}


int CambiarVariable(char * var, char * valor, char *e[]) /*cambia una variable en el entorno que se le pasa como parÃ¡metro*/
{                                                        /*lo hace directamente, no usa putenv*/
    int pos;
    char *aux;

    if ((pos=BuscarVariable(var,e))==-1)
        return(-1);

    if ((aux=(char *)malloc(strlen(var)+strlen(valor)+2))==NULL)
        return -1;
    strcpy(aux,var);
    strcat(aux,"=");
    strcat(aux,valor);
    e[pos]=aux;
    return (pos);
}


/*las siguientes funciones nos permiten obtener el nombre de una senal a partir
del nÃºmero y viceversa */
/*static struct SEN sigstrnum[]={
        {"HUP", SIGHUP},
        {"INT", SIGINT},
        {"QUIT", SIGQUIT},
        {"ILL", SIGILL},
        {"TRAP", SIGTRAP},
        {"ABRT", SIGABRT},
        {"IOT", SIGIOT},
        {"BUS", SIGBUS},
        {"FPE", SIGFPE},
        {"KILL", SIGKILL},
        {"USR1", SIGUSR1},
        {"SEGV", SIGSEGV},
        {"USR2", SIGUSR2},
        {"PIPE", SIGPIPE},
        {"ALRM", SIGALRM},
        {"TERM", SIGTERM},
        {"CHLD", SIGCHLD},
        {"CONT", SIGCONT},
        {"STOP", SIGSTOP},
        {"TSTP", SIGTSTP},
        {"TTIN", SIGTTIN},
        {"TTOU", SIGTTOU},
        {"URG", SIGURG},
        {"XCPU", SIGXCPU},
        {"XFSZ", SIGXFSZ},
        {"VTALRM", SIGVTALRM},
        {"PROF", SIGPROF},
        {"WINCH", SIGWINCH},
        {"IO", SIGIO},
        {"SYS", SIGSYS},
senales que no hay en todas partes
#ifdef SIGPOLL
        {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
        {"PWR", SIGPWR},
#endif
#ifdef SIGEMT
        {"EMT", SIGEMT},
#endif
#ifdef SIGINFO
        {"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
        {"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
        {"CLD", SIGCLD},
#endif
#ifdef SIGLOST
        {"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
        {"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
        {"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
        {"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
        {"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
        {"WAITING", SIGWAITING},
#endif
        {NULL,-1},
};    fin array sigstrnum */


//int ValorSenal(char * sen)  /*devuelve el numero de senial a partir del nombre*/
//{
//    int i;
//    for (i=0; sigstrnum[i].nombre!=NULL; i++)
//        if (!strcmp(sen, sigstrnum[i].nombre))
//            return sigstrnum[i].senal;
//    return -1;
//}


//char *NombreSenal(int sen)  /*devuelve el nombre senal a partir de la senal*/
//{			/* para sitios donde no hay sig2str*/
//    int i;
 //   for (i=0; sigstrnum[i].nombre!=NULL; i++)
//        if (sen==sigstrnum[i].senal)
//            return sigstrnum[i].nombre;
 //   return ("SIGUNKNOWN");
//}
