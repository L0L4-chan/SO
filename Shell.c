//
// Created by lola on 13/09/23.
//
#include "stdio.h"
#include "Shell.h"
#include "unistd.h"

// a continuacion copio el codigo de ayuda

/*las funciones entre puntos hay que implementarlas */

enum valid_commads{
        HIST,
        DATE,
        OPEN,
        CLOSE,
        LISTOPEN,
        HELP,
        DUP,
        COMMAND,
        QUIT,
        BYE,
        INFOSYS,
        MAN,
        //TODO INCLUIR LOS QUE FALTAN Y ORDENAR ALFABETICAMENTE.
};
void Cmd_open (char * tr[])
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
        .//todo..........AnadirAFicherosAbiertos (descriptor...modo...nombre....)....
        printf ("Anadida entrada a la tabla ficheros abiertos..................",......);
    }

    void Cmd_close (char *tr[])
    {
        int df;

        if (tr[0]==NULL || (df=atoi(tr[0]))<0) { /*no hay parametro /o el descriptor es menor que 0*/
           //todo ..............ListarFicherosAbiertos...............
            return;
        }


        if (close(df)==-1)
            perror("Inposible cerrar descriptor");
        else
        .//todo.......EliminarDeFicherosAbiertos......
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