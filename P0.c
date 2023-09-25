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

#include "P0.h"

// a continuacion copio el codigo de ayuda

/*las funciones entre puntos hay que implementarlas */

/**
 * Print on a console ->> indicating to the user an entry is needed
 */
void PrintPromt(){
    // printf("->>"); //codigo c
    // revisar si debemos hacerlo con SystemCalls en ese caso
    //https://man7.org/linux/man-pages/man2/write.2.html
    ssize_t result;
    result =  write(1,buf_out,(sizeof(out)));//SYSTEM CALL REVISAR LOS PARAMETROS NECESARIOS  salida deseada ->
     if (result < 0) {perror("Something when wrong\n");}// manejo de errores ver the llamar write() en lugar de printf
    //an error has happened, and we should handle it

}
/**
 * Read the command or entry made for the user
 * print Something went wrong in case the is nos entry
 */
void ReadEntry(){
    // libreria c
    //char* result =  fgets(in,MAXSIZE,stdin); //https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
    //if (result == NULL) {printf("Something when wrong\n");} manejo de errores
    //  revisar si debemos hacerlo con SystemCalls en ese caso
    for(int i= 0;i < MAXSIZE; i++){
        in[i] = ' ';
    }
    ssize_t result;
    result = read(0, buf_in, sizeof (in));// SYSTEM CALL revisar parametros requeridos
    if (result < 0) {
        perror("Something went wrong.\n");
        ToClose();
    }// manejo de errores ver the llamar write() en lugar de printf
    //an error has happened, and we should handle it
   // else//for testing remove after
   // {
       // printf(buf_in);

    //}
}
 /**
  * Break down the entry
  * @param cadena  pointer to the text we need to break into tokens
  * @param trozos  pointer to the tokens
  * @return int number of pieces
  * print There is no entry, try again in case there no command or text.
  */
 int SliceEntry(char * chain,char * token[], char * delim){  // no esta funcionando
     int i=1;
     if((token[0]=strtok(chain,delim))==NULL){//https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
         printf("There is no entry, try again.\n");
         return 0;
     }
     while((token[i]=strtok(NULL, delim))!=NULL){
         i++;
     }
     return i;
 }
/**
 * Print name and mode from the open files' list
 * @tList list
 */
void ListOpenFiles(tItem list[]) {

       for(int i = 0 ; i<= counterFiles; i++){
           tItem  aux = list[i];
            printf("Descriptor %d: %s  %d", aux.index, aux.CommandName, fcntl(aux.index,F_GETFL));
        }
}
/**
 * Function that will be on charge to process the entry,
 * create a process
 * and log it
 */
void ProcessingEntry (char * chunks[]){
    int com ;
    com = SliceEntry(in,chunks, " \n\t");
    if(com == 0){
        printf("No entry, please try again.\n");
    }else {
        if (chunks == NULL) {//seems unnecessary due to the fact that  if chunks is null, com is 0 but for safekeeping we create this exception
            printf("No entry, please try again.\n");
            return;
        }else{
            if(counterProcesses < MAXENTRIES) {
                //1º we store the command on our historical
                tItem newProcess; //create a process
                newProcess.CommandName = (char *) chunks[0];
                newProcess.index = counterProcesses;
                // printf( " 155 \n"); for test
                //bool success; //for test

                logStorage[counterProcesses] = newProcess; // log the process
                //printf("%d\n", success);
                counterProcesses++; //increase process number

                int result = ActionList(chunks, com, logStorage);
            }else{
                printf("It has not been possible to log this action\n");
            }
        }
    }

}
/**
 * Analyzes the first command and redirect to the right process
 * @param command  tokens, commands
 * @param index number of tokens
 * @param process information for the process
 * @return
 */
int ActionList(char * command[], int index, tItem Log[]) {
    if (!strcmp(command[0], "authors")) {
        PrintAuthor(command,index);
        return 0;
    } else if (!strcmp(command[0], "pid")) {
        PrintPID(command,index);
        return 1;
    } else if (!strcmp(command[0], "chdir")){
        ChangeDir(command, index);
        return 2;
    }else if (!strcmp(command[0], "date")){
        PrintDate(command);
        return 3;
    }else if (!strcmp(command[0], "time")){
        PrintTime(command);
        return 4;
    }else if (!strcmp(command[0], "hist")){
        PrintLog(command,index,Log);
        return 5;
    }else if (!strcmp(command[0], "command")){
        ExecuteN(command, index, Log);
        return 6;
    }else if (!strcmp(command[0], "open")){
        Cmd_open(command);
        return 7;
    }else if (!strcmp(command[0], "close")){
        Cmd_close(command);
        return 8;
    }else if (!strcmp(command[0], "dup")){
        Cmd_dup(command);
        return 9;
    }else if (!strcmp(command[0], "listopen")){
        ListOpenFiles(archive);
        return 10;
    }else if (!strcmp(command[0], "infosys")){
        PrintInfoSystem(command,index);
        return 11;
    }else if (!strcmp(command[0], "help")){
PrintHelp(command,index);
        return 12;
    }else if(!strcmp(command[0],"quit")||!strcmp(command[0],"exit")||!strcmp(command[0],"bye")){
        ToClose();
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
        bool n = false;
        bool l = false;
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
                }
                if(n){
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
/**
 *  TO print commands and some information to help the user
 * @param command tokens for command information
 * @param com numbers of tokens
 *
 * print "Unrecognized command, please try again or write help for help. if the command ir incorrect
 */
void PrintHelp(char * command[], int com){
    if(com==1){
        printf("'help [cmd|-lt|-T topic]' ayuda sobre comandos\n"
           "\t\tComandos disponibles:\n"
           "authors\npid\nchdir\ndate\ntime\nhist\ncommand\nopen\nclose\n"
           "dup\nlistopen\ninfosys\nhelp\nquit\nexit\nbye\n");
    }else{
        printf("%s  %s", command[0], command[1]);
        if (!strcmp(command[1], "authors")&& (com ==2)) {
            printf("authors [-n|-l]	Shows the name and/or logins of the authors\n");
        } else if (!strcmp(command[1], "pid")&& (com ==2)) {
            printf("pid [-p]\tShows the pid from the shell or its parent\n");
        } else if (!strcmp(command[1], "chdir")&& (com ==2)){
            printf("chdir [dir]\tChange (or shows) the actual directory for the shell\n");
        }else if (!strcmp(command[1], "date")&& (com ==2)){
            printf("date  Shows the actual date\n");
        }else if (!strcmp(command[1], "time")&& (com ==2)){
            printf("time  Shows the actual time\n");
        }else if (!strcmp(command[1], "hist")&& (com ==2)){
            printf("hist [-c|-N]\tShows or erases the commands' log\n"
                   "\t-N: Shows the firsts N commands\n"
                   "\t-c: erases the full log \n");
        }else if (!strcmp(command[1], "command")&& (com ==2)){
            printf("command [-N]\tRepeats the N command from the log \n ");
        }else if (!strcmp(command[1], "open")&& (com ==2)){
            printf("open file m1 m2...\topens the file file and adds it to the opens files log\n"
                   "\t m1, m2  open modes\n"
                   "\tcr: O_CREAT\tap: O_APPEND\n"
                   "\tex: O_EXCL \tro: O_RDONLY\n"
                   "\trw: O_RDWR \two: O_WRONLY\n"
                   "\tcommand: O_TRUNC\n");
        }else if (!strcmp(command[1], "close")&& (com ==2)){
            printf("close df\tCloses df and erases the fole from the log\n");
        }else if (!strcmp(command[1], "dup")&& (com ==2)){
            printf("dup df\tDuplicates the file df and adds a new entry to the log\n");
        }else if (!strcmp(command[1], "listopen")&& (com ==2)){
            printf("listopen [n]\tLists the n open files on the shell\n");
        }else if (!strcmp(command[1], "infosys")&& (com ==2)){
            printf("infosys \tshows information about the machine where the shell is nested\n");
        }else if (!strcmp(command[1], "help")&& (com ==2)){
            printf("help [cmd]\tShows some help about the commands\n");
        }else if(!strcmp(command[1],"quit")||!strcmp(command[1],"exit")||!strcmp(command[1],"bye")&& (com ==2)){
            printf("%s  Closes the shell\n", command[1]);
        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }
    }
}
/**
 * change the actual directory or show on screen the directory the shell is in
 * @param command
 * @param com
 */
void ChangeDir(char * command[] , int com){
    if (com == 1){
        char location[256]; //to store the location
        getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
        printf("%s\n", location);
    }else {
        if(chdir(command[1])!=0){
            perror("Something went wrong");
            ToClose();
        }else{
            chdir(command[2]);
            printf("Change of directory suscesful");
        }
    }
}
/**
* TO print Pid or PPid of the shell
* @param command tokens for command information
* @param com numbers of tokens
* print "Unrecognized command, please try again or write help for help. if the command ir incorrect
*/
void PrintPID(char * command[], int com)// check if we should print header
{
    if(com==1){
        printf("Shell PID: %d\n", getpid());//https://man7.org/linux/man-pages/man2/getpid.2.html
    }else{

        if (!strcmp(command[1], "-p")&& (com ==2)) {
            printf("Shell's father PID %d\n", getppid());//https://www.geeksforgeeks.org/getppid-getpid-linux/
        } else {
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }
    }
}
/**
 * to print the actual date  day month year
 */
void PrintDate(char * command[]) {//https://barcelonageeks.com/funcion-time-en-c/
    //Variable que da el timepo actual como un objeto
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);//https://www.geeksforgeeks.org/time-h-localtime-function-in-c-with-examples/
    char date[20]; //Variable donde se almacena el valor de la fecha una vez formateado
    //Le damos formato a la fecha para poner año, mes y dia en pantalla
    char * formato = "%d-%m-%Y";// how the date will be show
    //Se formatea la fecha como un flujo de bytes en formato String. https://en.cppreference.com/w/c/chrono/strftime
    size_t datebytes =
            strftime(date, sizeof(date), formato, &tiempoLocal);//https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
    if (datebytes != 0) {//Si al dar formato a la fecha la cantidad de  bytes no es cero se muestra el resultado
        printf("%s\n", date);
    } else {
        printf("Output error\n");
    }
    return;
}
/**
 * to print the actual time  hour_minute_seconds
 */
//El funcionamiento de la función es igual al de la fecha pero al dar formato se cogen los valores de horas, minutos y segundos
void PrintTime(char * command[]) {
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char date[20];
    char *formato = "%H:%M:%S";
    int datebytes =
            strftime(date, sizeof date, formato, &tiempoLocal);
    if (datebytes != 0) {
        printf("%s\n", date);
    } else {
        printf("Output error\n");
    }
    return;
}
/**
 * Show information about the machine where the shell is been run
 * @param command
 * @param com
 */
void PrintInfoSystem(char * command[], int com){
    if(com==1){
        struct utsname name;
       //https://stackoverflow.com/questions/3596310/c-how-to-use-the-function-uname
        if (uname(&name) != 0){
            perror("uname");
            ToClose();
        }else{

            printf("node name   = %s\n", name.nodename);
            printf("system name = %s\n", name.sysname);
            printf("release     = %s\n", name.release);
            printf("version     = %s\n", name.version);
            printf("machine     = %s\n", name.machine);
            return;
        }
    }
}
/**
 * Print the lis of command at least the first N commands
 * @param command
 * @param com
 * @param Log
 */
void PrintLog(char * command[], int com, tItem Log[]) {
    if (com == 1){

        for(int i = 0 ; i<= counterFiles; i++){
            tItem  aux = Log[i];
            printf("Descriptor %d: %s  \n", aux.index, aux.CommandName);
        }
            return;
    }else{
        if (com == 2){
            if(!strcmp(command[1], "-c")){
                for(int i = 0 ; i<= counterFiles; i++){
                    Log[i].index=-1;
                    Log[i].CommandName = "";
                    Log[i].mode=-1;
                }
                counterProcesses = 0;
                return;
            }

            int auxt = abs( atoi(command[1]));

                tItem aux = Log[auxt];
                printf("Descriptor %d: %s  \n", aux.index, aux.CommandName);

            return;
        }
        printf("Unrecognized command, please try again or write \"help\" for help.\n");
    }
}
/**
 * Look up for the command N from the log and execute it again
 * @param command
 * @param com
 * @param Log
 */
void ExecuteN(char * command[], int com, tItem Log[]){
    if (com == 2){
        int auxt =abs( atoi(command[1]));
        for(int i = 0 ; i<auxt;i++){
            tItem aux = Log[i];
            if(aux.index == auxt-1){
            com = SliceEntry(aux.CommandName, command, "\n\t");
            ActionList(command, com, Log);
            return;
            }
        }
    }
    printf("Unrecognized command, please try again or write \"help\" for help.\n");
}
/**
 * Close the shell
 * check if is needed to freed any variable
 */
void ToClose() //review function todo header info and exception
{
    //eliminacion de recursos debera hacerse aqui

    exit(EXIT_SUCCESS); //https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm
}
/**
 * Open a file and storage it on Archive
 * @param command
 */
void Cmd_open (char * command[])//FUNCION DE APERTURA DE FICHEROS
{
    int i,df, mode=0;

    if (command[1] == NULL) /*no hay parametro*/
    {
        ListOpenFiles(archive);
        return;
    }
    for (i=1; command[i] != NULL; i++)
        //The strcmp() compares two strings character by character.
        // If the strings are equal, the function returns 0.
        if (!strcmp(command[i], "cr")) mode|=O_CREAT;
        else if (!strcmp(command[i], "ex")) mode|=O_EXCL;
        else if (!strcmp(command[i], "ro")) mode|=O_RDONLY;
        else if (!strcmp(command[i], "wo")) mode|=O_WRONLY;
        else if (!strcmp(command[i], "rw")) mode|=O_RDWR;
        else if (!strcmp(command[i], "ap")) mode|=O_APPEND;
        else if (!strcmp(command[i], "command")) mode|=O_TRUNC;
        else break;

    if ((df=open(command[1], mode, 0777)) == -1)
        perror ("Impossible to open file");//error out
    else{
        if(counterFiles < MAXENTRIES ){
        df = open(command[1], mode);
        tItem file;
        file.index=df;
        file.CommandName = command[1];
        file.mode = mode;
        archive[counterFiles] = file;
        counterFiles ++;
        printf ("Add entry number %d to the open file's table", df);// add all the info on the file
        }else{
            printf("There is no room for more files");
        }
    }
}
/**
 * To close a file an erase it from the open list
 * @param Command
 */
void Cmd_close (char *Command[])
{
    int df;

    if (Command[1]==NULL || (df=atoi(Command[1]))<0) { /*no hay parametro /o el descriptor es menor que 0*/
        ListOpenFiles(archive);
        return;
    }
    if (close(df)==-1) {
        perror("Impossible to close descriptor");
    }else{
        for (int i = df; i <=counterFiles; i++){
            archive[i] = archive[i+1];
        }
        counterFiles--;
        printf("file %s has been close", Command[1]);
    }
}
/**
 * Duplicate a file
 * @param command
 */
void Cmd_dup (char * command[])
{
    int df, duplicado;
    char aux[MAXSIZE],*p;

    if (command[1]==NULL || (df=atoi(command[1]))<0) { /*no hay parametro*/ //https://www.aprendeaprogramar.com/referencia/view.php?f=atoi&leng=C
        ListOpenFiles(archive);                 /*o el descriptor es menor que 0*/
        return;
    }
    tItem auxI;
    duplicado = counterFiles;
    auxI.index = duplicado;
    auxI.CommandName = archive[df].CommandName;
    auxI.mode = archive[df].mode;

    archive[counterFiles] = auxI;
    counterFiles++;
    printf ("Add entry number %d to the open file's table, duplicate of file",duplicado, df);
}


/**
 * GameLoop
 * @param argc
 * @param argv
 */
void main(int argc, char * argv[]){
    tItem aux1;
    aux1.index = 0;
    aux1.CommandName = "standard entry";
    aux1.mode = O_RDWR;
    archive[counterFiles] = aux1;
    counterFiles ++;
    tItem aux2;
    aux2.index = 1;
    aux2.CommandName = "standard output";
    aux2.mode = O_RDWR;
    archive[counterFiles] = aux2;
    counterFiles ++;
    tItem aux3;
    aux3.index = 2;
    aux3.CommandName = "standard error";
    aux3.mode = O_RDWR;
    archive[counterFiles] = aux3;
    counterFiles ++;

        bool ended = false;
        while (!ended)
        {
            char * chunks[5];
            PrintPromt();
            ReadEntry();
            ProcessingEntry(chunks);

        }
    }