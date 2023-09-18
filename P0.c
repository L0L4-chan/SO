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
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Log_list.h"
#include "P0.h"
#include "ToTest.c"
// a continuacion copio el codigo de ayuda

/*las funciones entre puntos hay que implementarlas */

/**
 * Print on a console ->> indicating to the user an entry is needed
 */
void imprimirPront(){
    // printf("->>"); //codigo c
    // revisar si debemos hacerlo con SystemCalls en ese caso
    //https://man7.org/linux/man-pages/man2/write.2.html
    ssize_t result;
    result =  write(1,buf_out,(sizeof(out)));//SYSTEM CALL REVISAR LOS PARAMETROS NECESARIOS  salida deseada ->
     if (result < 0) {printf("Something when wrong\n");}// manejo de errores ver the llamar write() en lugar de printf
    //an error has happened, and we should handle it

}

/**
 * Read the command or entry made for the user
 * print Something went wrong in case the is nos entry
 */
void leerEntrada(){
    // libreria c
    //char* result =  fgets(in,MAXSIZE,stdin); //https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
    //if (result == NULL) {printf("Something when wrong\n");} manejo de errores
    //  revisar si debemos hacerlo con SystemCalls en ese caso
    ssize_t result;
    result = read(0, buf_in, sizeof (in));// SYSTEM CALL revisar parametros requeridos
    if (result < 0) {
        printf("Something went wrong.\n");
    }// manejo de errores ver the llamar write() en lugar de printf
    //an error has happened, and we should handle it
   // else//for testing remove after
   // {
       // printf(buf_in);

    //}
}
 //TODO CREAR UNA FUNCION QUE SE ENCARGUE DEL MANEJO DE ERRORES Y LA IMPRESION DE MENSAJE DE ERROR POR PANTALLA

 /**
  * Break down the entry
  * @param cadena  pointer to the text we need to break into tokens
  * @param trozos  pointer to the tokens
  * @return int number of pieces
  * print There is no entry, try again in case there no command or text.
  */
 int TrocearCadena(char * cadena,char * trozos[]){  // no esta funcionando
     int i=1;
     if((trozos[0]=strtok(cadena," \n\t"))==NULL){//https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
         printf("There is no entry, try again.\n");
         return 0;
     }
     while((trozos[i]=strtok(NULL," \n\t"))!=NULL){
         i++;
     }
   /* for(int l=0; l<i; l++) {
        printf(trozos[l], "\n");
    }
*/
     return i;
 }

/**
 * TODO
 */
void ListOpenFiles() {
}

/**
 * Function that will be on charge to process the entry,
 * create a process
 * and log it
 */
void procesarEntrada() {
    int com ;
    com = TrocearCadena(in,chunks);
    if(com == 0){
        printf("No entry, please try again.\n");
    }else {

        if (chunks == NULL) {//seems unnecesary due to the fact that  if chunks is null, com is 0 but for safekeeping we create this exception
            printf("No entry, please try again.\n");
            return;
        }
        //1º we store the command on our historical
        tItem newProcess; //create a process
        newProcess.PID = actives_process; // give it a number
        newProcess.CommandName = (char *) chunks[0];
        //TODO store the PPID
       // printf( " 155 \n"); for test
        //bool success; //for test
        /*success = */insertItem(newProcess, Historical_List); // log the process
        //printf("%d\n", success);
        actives_process++; //increase process number
        //int operation; for test
         /*operation =*/ ActionList(chunks, com, Historical_List);
       // printf("%d\n",operation); for test
    }

}

/**
 * Analize the first command and redirect to the right process
 * @param command  tokens, commands
 * @param index number of tokens
 * @param process information for the process
 * @return
 */
int ActionList(char * command[], int index, tList * Log) {
    if (!strcmp(command[0], "authors")) {
        PrintAuthor(command,index);
        return 0;
    } else if (!strcmp(command[0], "pid")) {
        PrintPID(command,index,Log);
        return 1;
    } else if (!strcmp(command[0], "chdir")){
        return 2;
    }else if (!strcmp(command[0], "date")){
        return 3;
    }else if (!strcmp(command[0], "time")){
        return 4;
    }else if (!strcmp(command[0], "hist")){
        return 5;
    }else if (!strcmp(command[0], "command")){
        return 6;
    }else if (!strcmp(command[0], "open")){
        return 7;
    }else if (!strcmp(command[0], "close")){
        return 8;
    }else if (!strcmp(command[0], "dup")){
        return 9;
    }else if (!strcmp(command[0], "listopen")){
        return 10;
    }else if (!strcmp(command[0], "infosys")){
        return 11;
    }else if (!strcmp(command[0], "help")){
        return 12;
    }else if(!strcmp(command[0],"quit")||!strcmp(command[0],"exit")||!strcmp(command[0],"bye")){
        return 13;
    }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");
    return -1;
}

/**
 * TO print authors of the code information
 * @param command tokens for command information
 * @param com numbers of tokens
 * print "Unrecognized command, please try again or write help for help. if the command ir incorrect
 */
void PrintAuthor(char * command[], int com){
    if (com == 1){
        printf("Ismael Miguez Valero\n"
                      "i.miguezv@udc.es\n");
        printf("Dolores Suarez Gonzalez\n"
                      "d.suarez2@udc.es\n");
        return;
    }else{
        bool n, l = false;
        for(int i = 1; i<com; i++){
            if(!strcmp(command[i], "-l")){
                l=true;
            }
            if( !strcmp(command[i], "-n")&& !n){
                n=true;
            }
        }
            if (com == 2 &&(l || n)){
                if (l){
                    printf("i.miguezv@udc.es\n");
                    printf("d.suarez2@udc.es\n");
                    return;
                }else{
                    printf("Ismael Miguez Valero\n");
                    printf("Dolores Suarez Gonzalez\n");
                    return;
                }
            }
            if(com == 3 && (l && n)){
                printf("Ismael Miguez Valero\n"
                       "i.miguezv@udc.es\n");
                printf("Dolores Suarez Gonzalez\n"
                       "d.suarez2@udc.es\n");
                return;
            }else {
                printf("Unrecognized command, please try again or write \"help\" for help.\n");
            }
    }
}

void PrintPID(char * command[], int com, tList * Log)// check if we should print header
{
    bool p = false;
    tItem process;
    int PID = (int) command[1];
    int index = 0;
    if(PID!= NULL){ //if we have a correct number
        while (hasNext(findItem(index,Log), Log)){
            if(findItem(index,Log)->item.PID==PID){
                process = findItem(index,Log)->item;
            }
            index ++;
        }

         }
        if (com == 2 ){

         printf("%d  %s  \n",process.PID, process.CommandName );
        return;
    }
    if (com == 3){
        if(!strcmp(command[1], "-p")){
           if(process.PPID==NULL){
               PrintPID(command,com-1,Log);
           }else{
            p=true;
           }
        }
    }
    if(p){
        printf("%d  %s %d  \n",process.PID, process.CommandName, process.PPID );
    }else{
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
    }
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
    char aux[MAXSIZE],*p;

    if (tr[0]==NULL || (df=atoi(tr[0]))<0) { /*no hay parametro*/
        ListOpenFiles(-1);                 /*o el descriptor es menor que 0*/
        return;
    }

    /*todo
    p=.....NombreFicheroDescriptor(df).......;
    sprintf (aux,"dup %d (%s)",df, p);
    .......AnadirAFicherosAbiertos......duplicado......aux.....fcntl(duplicado,F_GETFL).....;*/
}
//implementacion de listas realizada en otra asignatura, ver que funciones son necesarias y eliminar el resto.
void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tPos first(tList L) {
    return L;
}

tPos last(tList L) {
    tPos pos;

    if (isEmptyList(L))
        return LNULL;

    for (pos = L; pos->next != LNULL; pos = pos->next);
    return pos;
}

tPos previous(tPos p, tList L) {
    tPos pos;

    if (p == L)
        pos = LNULL;
    else
        for (pos = L; pos->next != p; pos = pos->next);
    return pos;
}

bool hasNext(tPos p, tList L) {
    return (p->next!=NULL);
}

tPos next(tPos p, tList L) {
    return p->next;
}

tItem getItem(tPos p, tList L) {
    return p->item;
}

tPos findItem(int n, tList L) {
    int cnt = 1;
    tPos pos;

    for (pos = L; (pos != LNULL); pos = pos->next) {
        if (cnt == n)
            return pos;
        else
            cnt++;
    }
    return pos;
}

void updateItem(tItem i, tPos p, tList *L) {
    p->item = i;
}

void deleteAtPosition(tPos p, tList *L) {
    if (p == *L) {
        *L = p->next;
    } else
        previous(p, *L)->next = p->next;
    free(p);
}

void deleteList(tList *L) {
    tPos lastpos, aux;

    if (isEmptyList(*L))
        free(*L);
    else {
        lastpos = last(*L);
        aux = previous(lastpos, *L);
        if (aux == LNULL) {
            free(lastpos);
            *L = LNULL;
            deleteList(L);
        } else {
            aux->next = LNULL;
            free(lastpos);
            deleteList(L);
        }
    }
}

tPos findPosition(tItem i, tList L) {
    tPos aux;

    aux = L;
    while ((aux->next != LNULL) && (strcmp(i.CommandName, aux->next->item.CommandName) > 0))
        aux = aux->next;
    return aux;
}

bool insertItem(tItem i, tList *L) {
    tPos node;

    node = malloc(sizeof(struct tNode));

    if (node == LNULL) {
      //  printf(" 301\n");
        return false;
    }else {
        //printf(" 304\n");
        node->item = i;
        node->next = LNULL;

        if (*L == LNULL)
            *L = node;
        else
            last(*L)->next = node;
    }
    return true;
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


