//
// Created by lola on 13/09/23.
//
/**
 * AUTHOR
 * Ismael Miguez Valero
 * i.miguezv@udc.es
 *
 * Lola Suárez González
 * d.suarez2@udc.es
 *
 * */
#include <stdbool.h>
#include "stdio.h"
#include "P0.h"
#include "unistd.h"
//#include <syscall.h>deprecade??
#include <unistd.h>
#include <stdlib.h>
// a continuacion copio el codigo de ayuda

/*las funciones entre puntos hay que implementarlas */

# define MAXSIZE 540 //REVISAR VALORES
# define MAXNAME 540

 enum valid_commads{
        O_CREAT,O_EXCL,O_RDONLY, O_WRONLY,O_RDWR,O_APPEND, O_TRUNC
};

char out[2] = {'-','>'};
char in[MAXSIZE];
const void * bufi = &in;
const void * bufo = &out;

void ListOpenFiles(int i);

void procesarEntrada();

void imprimirPront(){

    // revisar que esta llamada esta bien, deberia imprimir por pantalla ->


   write(1,bufo,(sizeof(out)));//SYSTEM CALL REVISAR LOS PARAMETROS NECESARIOS  salida deseada ->
}

void leerEntrada(){

    read(0, bufi, sizeof (in));// SYSTEM CALL revisar parametros requeridos

}

int TrocearCadena(char * character, char * cadena[])
{
    int i = 1;
    //copiar del archivo de la practica
}

void Cmd_open (char * tr[])//FUNCION DE APERTURA DE FICHEROS
{
    int i,df, mode=0;

    if (tr[0]==NULL) /*no hay parametro*/
    {
        // todo ..............ListarFicherosAbiertos...............
        return;
    }
    for (i=1; tr[i]!=NULL; i++)
        //The strcmp() compares two strings character by character.
        // If the strings are equal, the function returns 0.
        if (!strcmp(tr[i],"cr")) mode|=O_CREAT;
        else if (!strcmp(tr[i],"ex")) mode|=O_EXCL;
        else if (!strcmp(tr[i],"ro")) mode|=O_RDONLY;
        else if (!strcmp(tr[i],"wo")) mode|=O_WRONLY;
        else if (!strcmp(tr[i],"rw")) mode|=O_RDWR;
        else if (!strcmp(tr[i],"ap")) mode|=O_APPEND;
        else if (!strcmp(tr[i],"tr")) mode|=O_TRUNC;
        else break;

    if ((df=open(tr[0],mode,0777))==-1)
        perror ("Imposible abrir fichero");//error out
    else{
        //todo..........AnadirAFicherosAbiertos (descriptor...modo...nombre....)....
        printf ("Anadida entrada a la tabla ficheros abiertos..................",......);
    }
}

    void Cmd_close (char *tr[])
    {
        int df;

        if (tr[0]==NULL || (df=atoi(tr[0]))<0) { /*no hay parametro /o el descriptor es menor que 0*/
           //todo ..............ListarFicherosAbiertos...............
            return;
        }


        if (close(df)==-1) {
            perror("Inposible cerrar descriptor");
        }else{
        //todo.......EliminarDeFicherosAbiertos......
        }
    }

    void Cmd_dup (char * tr[])
    {
        int df, duplicado;
        char aux[MAXNAME],*p;

        if (tr[0]==NULL || (df=atoi(tr[0]))<0) { /*no hay parametro*/
            ListOpenFiles(-1);                 /*o el descriptor es menor que 0*/
            return;
        }

        /*todo
        p=.....NombreFicheroDescriptor(df).......;
        sprintf (aux,"dup %d (%s)",df, p);
        .......AnadirAFicherosAbiertos......duplicado......aux.....fcntl(duplicado,F_GETFL).....;*/
    }

void ListOpenFiles(int i) {

}

void procesarEntrada() {
    TrocearCadena(&in, )

}

void main(int argc, char * argv[]){
        bool terminado = false;
        while (!terminado)
        {
            imprimirPront();
            leerEntrada();
            procesarEntrada();


        }
    }


