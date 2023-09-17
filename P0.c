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
//#include <syscall.h>deprecade??
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Log_list.h"
#include "P0.h"
// a continuacion copio el codigo de ayuda

/*las funciones entre puntos hay que implementarlas */


void imprimirPront(){
    // revisar que esta llamada esta bien, deberia imprimir por pantalla ->
    // printf("->"); //codigo c
    // revisar si debemos hacerlo con SystemCalls en ese caso
    //https://man7.org/linux/man-pages/man2/write.2.html
    ssize_t result;
    result =  write(1,buf_out,(sizeof(out)));//SYSTEM CALL REVISAR LOS PARAMETROS NECESARIOS  salida deseada ->
     if (result < 0) {printf("Something when wrong\n");}// manejo de errores ver the llamar write() en lugar de printf
    //an error has happened, and we should handle it

}

void leerEntrada(){
    // libreria c
    //char* result =  fgets(in,MAXSIZE,stdin); //https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
    //if (result == NULL) {printf("Something when wrong\n");} manejo de errores
    //  revisar si debemos hacerlo con SystemCalls en ese caso
    ssize_t result;
    result = read(0, buf_in, sizeof (in));// SYSTEM CALL revisar parametros requeridos
    if (result < 0) {printf("Something when wrong\n");}// manejo de errores ver the llamar write() en lugar de printf
    //an error has happened, and we should handle it
    else
    {
        printf(buf_in);

    }//for testing remove after
}
 //TODO CREAR UNA FUNCION QUE SE ENCARGUE DEL MANEJO DE ERRORES Y LA IMPRESION DE MENSAJE DE ERROR POR PANTALLA
 int TrocearCadena(char * cadena,char * trozos[]){
     int i=1;
     if((trozos[0]=strtok(cadena," \n\t"))==NULL)//https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
         return 0;

     while((trozos[i]=strtok(NULL," \n\t"))!=NULL){
         printf(trozos[i] ,"\n");
         i++;
     }
     return i;
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
        printf ("Anadida entrada a la tabla ficheros abiertos..................");// add all the info on the file
    }
}

    void Cmd_close (char *tr[])
    {
        int df;

        if (tr[0]==NULL || (df=atoi(tr[0]))<0) { /*no hay parametro /o el descriptor es menor que 0*/
            ListOpenFiles();
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

void ListOpenFiles() {

}

void procesarEntrada() {
    char * chunck[MAXSIZE];
    TrocearCadena(buf_in,chunck );//revisar parametros en todas las funciones
    if(&chuncks[0] == NULL){
        return;
    }
        //1º we store the comamand on our historical
        actives_process ++;
        tItem newProcess;
        newProcess.PID = actives_process;
        newProcess.CommandName;// revisar = &chuncks[0];
        bool success =  insertItem(newProcess,Historical_List);


}

void main(int argc, char * argv[]){
        bool ended = false;
        while (!ended)
        {
            imprimirPront(); //funciona
            leerEntrada();
            procesarEntrada();

        }
    }


