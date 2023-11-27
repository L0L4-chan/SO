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

#include "p0.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"

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
void ListOpenFiles(tList  * list) {
    if(isEmptyList(* list)){
        printf("there is not elements to show\n");
    }else{
        tPos pos = first(*list);
        while(pos!=NULL){
            tFile * elem = (tFile *)getItem(pos, *list);
            printf("Descriptor %d: %s %s \n",  elem->index, elem->CommandName, elem->permit);
            pos = next(pos,*list);
        }
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
            if(counterProcesses < MAXENTRIES ){
                //1º we store the command on our historical
                tItem * newProcess = malloc(sizeof (tItem)); //create a process
                strcpy(newProcess->CommandName, chunks[0]);
                for(int i = 1; i < com; i++) {
                    strcat(newProcess->CommandName, " ");
                    strcat(newProcess->CommandName, chunks[i]);
                }
                newProcess->index = counterProcesses;
                // printf( " 155 \n"); for test
                //bool success; //for test
                insertItem(newProcess, Historical_List); // log the process
                //printf("%d\n", success);
                counterProcesses++; //increase process number
            }else{
                printf("It has not been possible to log this action\n");
            }
            int result =  ActionList(chunks, com, Historical_List);

            if(result == -1){
                printf("Unrecognized command, please try again or write \"help\" for help.\n");
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
int ActionList(char * command[], int index, tList * Log) {
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
        PrintDate();
        return 3;
    }else if (!strcmp(command[0], "time")){
        PrintTime();
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
        Cmd_dup(command, Log);
        return 9;
    }else if (!strcmp(command[0], "listopen")){
        ListOpenFiles(Archive);
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
    }else if(!strcmp(command[0], "create")){
        ToCreate(command, index);
        return 14;
    }else if(!strcmp(command[0], "stat")){
        ShowStat(command, index);
        return 15;
    }else if(!strcmp(command[0], "list")){
        ToList(command, index);
        return 16;
    }else if(!strcmp(command[0], "delete")){
        ToDelete(command, index);
        return 17;
    }else if(!strcmp(command[0], "deltree")){
        ToDeleteTree(command,index);
        return 18;
    }else if(!strcmp(command[0], "malloc")){
        Make_Malloc(command,index);
        return 19;
    }else if(!strcmp(command[0], "shared")){
        Make_Shared(command,index);
        return 20;
    }else if(!strcmp(command[0], "mmap")){
        Make_Mmap(command, index);
        return 21;
    }else if(!strcmp(command[0], "read")){
        ToRead(command,index);
        return 22;
    }else if(!strcmp(command[0], "write")){
        ToWrite(command,index);
        return 23;
    }else if(!strcmp(command[0], "memdump")){
        Make_Memdump(command,index);
        return 24;
    }else if(!strcmp(command[0], "memfill")){
        Make_Memfill(command,index);
        return 25;
    }else if(!strcmp(command[0], "mem")){
        ToMem(command,index);
        return 26;
    }else if(!strcmp(command[0], "recurse")){
        ToRecurse(command,index);
        return 27;
    }else if(!strcmp(command[0], "uid")){
        SetUID(command,index);
        return 28;
    }else if(!strcmp(command[0], "showvar")){
        ToShowVar(command,index);
        return 29;
    }else if(!strcmp(command[0], "changevar")){
        ToChangeVar(command,index);
        return 30;
    }else if(!strcmp(command[0], "subsvar")){
        ToSubVar(command,index);
        return 31;
    }else if(!strcmp(command[0], "showenv")){
        ToShowEnv(command,index);
        return 32;
    }else if(!strcmp(command[0], "fork")){
        SetFork(command,index);
        return 33;
    }else if(!strcmp(command[0], "exec")){
        SetEXEC(command,index);
        return 34;
    }else if(!strcmp(command[0], "jobs")){
        ToJobS(command,index);
        return 35;
    }else if(!strcmp(command[0], "deljobs")){
        ToDelJobs(command,index);
        return 36;
    }else if(!strcmp(command[0], "job")){
        ToJob(command,index);
        return 37;
    }else if(!strcmp(command[0], "*****")){
        ToJobS(command,index);
        return 38;
    }else if(!strcmp(command[0], "*****&")) {
        ToJobS(command, index);
        return 39;
    }
    return -1;
}
/**
 * TO print authors of the code information
 * @param command tokens for command information
 * @param com numbers of tokens
 * print "Unrecognized command, please try again or write help for help. if the command ir incorrect
 */
void PrintAuthor(char * command[], int com){
    bool n = false;
    bool l = false;
    if (com == 1){
        printf("Ismael Miguez Valero\n"
               "i.miguezv@udc.es\n");
        printf("Dolores Suarez Gonzalez\n"
               "d.suarez2@udc.es\n");
        return;
    }else{

        for(int i = 1; i<com; i++){
            if(!strcmp(command[i], "-l")){
                l=true;
            }
            if( !strcmp(command[i], "-n")&& !n){
                n=true;
            }
        }
        if (com == 2 && (l || n)){
            if (l){
                printf("i.miguezv@udc.es\n");
                printf("d.suarez2@udc.es\n");
            }
            if (n){
                printf("Ismael Miguez Valero\n");
                printf("Dolores Suarez Gonzalez\n");
            }
        }else if (com == 3 && (l && n)){
            printf("Ismael Miguez Valero\n"
                   "i.miguezv@udc.es\n");
            printf("Dolores Suarez Gonzalez\n"
                   "d.suarez2@udc.es\n");
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
               "dup\nlistopen\ninfosys\nstat\ndeltree\nlist\ndelete\ncreate\n"
               "help\nquit\nexit\nbye\nmalloc\nmmap\nshared\nwrite\nread\n"
               "memdup\nmemfill\nmem\nrecurse\nuid\nshowvar\nchangevar\n"
               "subvar\nshowenv\nfork\nexec\njobs\ndeljobs\n"
               "job\n*****\n*****&\n");
    }else{
        printf("%s  %s\n", command[0], command[1]);
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
        }else if((!strcmp(command[1],"quit")||!strcmp(command[1],"exit")||!strcmp(command[1],"bye"))&& (com ==2)){
            printf("%s  Closes the shell\n", command[1]);
        }else if(!strcmp(command[1], "create")){
            printf("create [-f] [name]\tCreate a directory or a file\n");
        }else if(!strcmp(command[1], "stat")){
            printf("stat [-long][-link][-acc] name1 name2 ..\tlist files;\n"
                   "\t-long: long list\n"
                   "\t-acc: acesstime\n"
                   "\t-link: if is a symbolic link, it will show the path of the file\n");
        }else if(!strcmp(command[1], "list")){
            printf("list [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 ..\nlist the directorys and the files in them\n"
                   "\t-hid: include hidden files\n"
                   "\t-recb: recursive (before)\n"
                   "\t-reca: recursive (after)\n"
                   "\t-long: long list\n"
                   "\t-acc: acesstime\n"
                   "\t-link: if is a symbolic link, it will show the path of the file\n");
        }else if(!strcmp(command[1], "delete")){
            printf("delete [name1 name2 ..]\tDelete empty files or directories\n");
        }else if(!strcmp(command[1], "deltree")){
            printf("deltree [name1 name2 ..]\tRecursive delete of files or directories\n");
        }else if(!strcmp(command[1], "malloc")){
            printf("malloc [-free][tam]\tAllocation of a memory block with size tam with malloc\n"
                   "\t -free: Unassignation of memory block of size tam assigned with malloc\n");
        }else if(!strcmp(command[1], "shared")){
            printf("shared[-free][-create|-delkey]cl[tam]\tAllocation of shared memory with key cl and size tam\n"
                   "\t-create cl tam: Allocate (Creating) a shared memory block with key cl and size tam\n"
                   "\t-free cl: Unmap shared memory block with key cl\n"
                   "\t-delkey cl: delete of sistem (without unmapping) the memory key cl\n");
        }else if(!strcmp(command[1], "mmap")){
            printf("mmap [-free] fich prm\tMap file fich with permission prm\n"
                   "\t-free fich: Unmap file fich\n");
        }else if(!strcmp(command[1], "write")){
            printf("write [-o] fich addr cont\tWrite cont bytes from path addr to fich\n"
                   "\t-o: overwrite\n");
        }else if(!strcmp(command[1], "read")){
            printf("read fich addr cont\tRead cont bytes from fich to addr path\n");
        }else if(!strcmp(command[1], "memdump")){
            printf("memdump addr cont\tDump on screen contents (cont bytes) of memory position addr\n");
        }else if(!strcmp(command[1], "memfill")){
            printf("memfill addr cont byte\tFill memory from addr with byte\n");
        }else if(!strcmp(command[1], "mem")){
            printf("mem [-blocks|-funcs|-vars|all|-pmap]...\tShows processs memory detalils\n"
                   "\t-blocks: memory blocks allocated\n"
                   "\t-funcs: function adresses\n"
                   "\t-vars: variable addresses\n"
                   "\t-all: all information available\n"
                   "\t-pmap: shows the pmap command output (or similar)\n");
        }else if(!strcmp(command[1], "recurse")){
            printf("recurse [n]\tCalls recursive function n times\n");
        }else if(!strcmp(command[1], "uid")){
            printf("uid [-get|-set] [-l] [id] \t Accede a las credenciales del proceso que ejecuta el shell\n"
                   "\t-get: muestra las credenciales\n"
                   "\t-set id: establece la credencial al valor numerico id\n"
                   "\t-set -l id: establece la credencial a login id\n");
        }else if(!strcmp(command[1], "showvar")) {
            printf("showvar var	Muestra el valor y las direcciones de la variable de entorno var\n");
        }else if(!strcmp(command[1], "changevar")) {
            printf("changevar [-a|-e|-p] var valor\tCambia el valor de una variable de entorno\n"
                   "\t-a: accede por el tercer arg de main\n"
                   "\t-e: accede mediante environ\n"
                   "\t-p: accede mediante putenv\n");
        }else if(!strcmp(command[1], "subsvar")) {
            printf("subsvar [-a|-e] var1 var2 valor\tSustituye la variable de entorno var1\n"
                   "\tcon var2=valor\n"
                   "\t-a: accede por el tercer arg de main\n"
                   "\t-e: accede mediante environ\n");
        }else if(!strcmp(command[1], "showenv")) {
            printf("showenv [-environ|-addr] \t Muestra el entorno del proceso\n"
                   "\t-environ: accede usando environ (en lugar del tercer arg de main)\n"
                   "\t-addr: muestra el valor y donde se almacenan environ y el 3er arg main \n");
        }else if(!strcmp(command[1], "fork")) {
            printf("fork \tEl shell hace fork y queda en espera a que su hijo termine\n");
        }else if(!strcmp(command[1], "exec")) {
        printf("exec VAR1 VAR2 ..prog args....[@pri]\tEjecuta, sin crear proceso,prog con argumentos"
               "en un entorno que contiene solo las variables VAR1, VAR2...\n");
        }else if(!strcmp(command[1], "jobs")) {
            printf("jobs \tLista los procesos en segundo plano\n");
        }else if(!strcmp(command[1], "deljobs")) {
            printf("deljobs [-term][-sig]\tElimina los procesos de la lista procesos en sp\n"
                   "\t-term: los terminados\n"
                   "\t-sig: los terminados por senal\n");
        }else if(!strcmp(command[1], "job")) {
            printf("job [-fg] pid\tMuestra informacion del proceso pid.\n"
                   "\t\t-fg: lo pasa a primer plano\n");
        }printf("Unrecognized command, please try again or write \"help\" for help.\n");
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
        if(chdir(command[1])!=0){//https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
            perror("Something went wrong\n");
        }else{
            chdir(command[1]);
            printf("Change of directory successful\n");
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
        perror("Output error\n");
    }
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
        perror("Output error\n");
    }
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
            perror("System info could not be found.\n");
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
void PrintLog(char * command[], int com, tList * Log) {
    if (com == 1){
        tPos pos = first(*Log);
        while(pos!=NULL){
            tItem * aux = (tItem *)getItem(pos, *Log);
            printf("%d  %s \n", aux->index, aux->CommandName);
            pos = next(pos, *Log);
        }
        return;
    }else{
        if (com == 2){
            if(!strcmp(command[1], "-c")){
                deleteList(Log);
                counterProcesses = 1;
                return;
            }
            if(!strcmp(command[1], "-N")){
                tPos pos = first(*Log);
                tItem * aux = (tItem *)getItem(pos, *Log);
                printf("%d  %s \n", aux->index, aux->CommandName);
                return;
            }
            int auxt =abs( atoi(command[1]));
            tPos pos = first(*Log);
            for(int i = 1 ; i<=auxt;i++){
                tItem * aux = (tItem *)getItem(pos, *Log);
                printf("%d  %s\n", i, aux->CommandName);
                pos = next(pos, *Log);
            }
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
void ExecuteN(char * command[], int com, tList * Log){
    if (com == 2){
        int auxt =abs( atoi(command[1]));
        tPos pos = first(*Log);
        while(pos!=NULL){
            tItem * aux = (tItem *)getItem(pos, *Log);
            if(aux->index == auxt){
                com = SliceEntry(aux->CommandName, command, " \n\t");
                if(!strcmp(command[0], "command")){
                    printf("This command cannot be repeat, recursive call chain\n ");
                    return;
                }
                ActionList(command, com, Log);
                return;
            }
            pos = next(pos, * Log);
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
    deleteList(Historical_List);
    deleteList(Archive);
    tPos pos = first(memoryLog);
    while(pos!=NULL) {
        tMemList *aux = (tMemList *) getItem(pos, memoryLog);
        if(!strcmp(aux->type,"malloc")){
            free(aux->addr);
        }
        pos = next(pos, memoryLog);
    }
    deleteList(memLog);
    exit(EXIT_SUCCESS); //https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm
}
/**
 * Open a file and storage it on Archive
 * @param command
 */
void Cmd_open (char * command[])//FUNCION DE APERTURA DE FICHEROS
{
    int i, df, mode = 0;
    char mode_char[10] = "";
    if (command[1] == NULL) /*no hay parametro*/
    {
        ListOpenFiles(Archive);
        return;
    }
    for (i = 2; command[i] != NULL; i++) {
        //The strcmp() compares two strings character by character.
        // If the strings are equal, the function returns 0.
        if (!strcmp(command[i], "cr")) {
            mode |= O_CREAT;
            stpcpy(mode_char, "O_CREAT");
        } else if (!strcmp(command[i], "ex")) {
            mode |= O_EXCL;
            stpcpy(mode_char, "O_EXCL");
        }else if (!strcmp(command[i], "ro")){
            mode |= O_RDONLY;
            stpcpy(mode_char, "O_RDONLY");
        }else if (!strcmp(command[i], "wo")) {
            mode |= O_WRONLY;
            stpcpy(mode_char, "O_WRONLY");
        }else if (!strcmp(command[i], "rw")) {
            mode |= O_RDWR;
            stpcpy(mode_char, "O_RDWR");
        }else if (!strcmp(command[i], "ap")) {
            mode |= O_APPEND;
            stpcpy(mode_char, "O_APPEND");
        }else if (!strcmp(command[i], "command")) {
            mode |= O_TRUNC;
            stpcpy(mode_char, "O_TRUNC");
        }
    }
    if ((df = open(command[1], mode)) == -1){
        perror("Impossible to open file\n");//error out
    }else{
        if(counterFiles < MAXENTRIES ){
            tFile * file= malloc(sizeof (tFile));
            file->index = df;
            stpcpy(file->CommandName ,command[1]);
            stpcpy(file->permit,mode_char);
            insertItem(file,Archive);
            counterFiles ++;
            printf ("Add entry number %d to the open file's table\n", df);// add all the info on the file
        }else{
            printf("There is no room for more files\n");
        }
    }
}
/**
 * To close a file an erase it from the open list
 * @param Command
 */
void Cmd_close (char *Command[]){
    int df;
    if (Command[1]==NULL || (df=atoi(Command[1]))<0) {/*no hay parametro*/
        printf("This file is non available\n");
        ListOpenFiles(Archive);
        /*
        //System Call read dir para recorrer los archivos del directorio
        DIR *dir; //https://man7.org/linux/man-pages/man3/readdir.3.html
        struct dirent *direntp;

        char location[256]; //to store the location
        getcwd(location, sizeof(location));//https://man7.org/linux/man-pages/man3/getcwd.3.html
        dir = opendir(location);
        if(dir==NULL) {
            printf("This directory can't be open");
        }
        while ((direntp = readdir(dir)) != NULL) {
            printf("%s\n", direntp->d_name);
        }*/
        return;
    }
    if (close(df)==-1)
        perror("Descriptor can't be closed\n");
    else {
        df = atoi(Command[1]);
        close(df);
        deleteAtPosition(findItem(df, * Archive),Archive);
        printf("File %s has been close\n", Command[1]);
    }
}



/**
 * Duplicate a file
 * @param command
 */
void Cmd_dup (char * command[], tList *Log)
{
    int df, duplicate;

    if (command[1]==NULL || (df=atoi(command[1]))<0) { /*no hay parametro*/ //https://www.aprendeaprogramar.com/referencia/view.php?f=atoi&leng=C
        ListOpenFiles(Archive);                 /*o el descriptor es menor que 0*/
        return;
    }
    else {
        if(counterFiles < MAXENTRIES ) {

//            df = open(command[1], O_CREAT|O_EXCL|O_RDONLY|O_WRONLY|O_RDWR| O_APPEND|O_TRUNC);
            df = atoi(command[1]);
            duplicate = dup(df);  //https://man7.org/linux/man-pages/man2/dup.2.html
            tFile * fileaux = malloc(sizeof (tFile));
            fileaux->index = duplicate;
            tFile * file = (tFile *)findItem(df, * Archive)->item;
            stpcpy(fileaux->CommandName, file->CommandName);
            stpcpy(fileaux->permit, file->permit);
            insertItem(fileaux, Archive);
            counterFiles++;
            printf( "dup %d (%s)\n", df, fileaux->CommandName);

        }
        else
            perror("There is no room for more files\n");
    }

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
tPos next(tPos p, tList L) {
    return p->next;
}
void * getItem(tPos p, tList L) {
    return p->item;
}
tPos findItem(int n, tList L) {
    int cnt = 0;
    tPos pos;

    for (pos = L; (pos != LNULL); pos = pos->next) {
        if (cnt == n)
            return pos;
        else
            cnt++;
    }
    return pos;
}
void updateItem(void * i, tPos p, tList *L) {
    p->item = i;
}
void deleteAtPosition(tPos p, tList *L) {
    if (p == *L) {
        *L = p->next;
    } else
        previous(p, *L)->next = p->next;
    free(p->item);
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
            if(lastpos->item != NULL){
            free(lastpos->item);
            }
            free(lastpos);
            *L = LNULL;
            deleteList(L);
        } else {
            aux->next = LNULL;
            if(lastpos->item != NULL){
                free(lastpos->item);}
            free(lastpos);
            deleteList(L);
        }
    }
}
tPos findPosition(void * i, tList L) {
    tPos aux;

    aux = L;
    while ((aux->next != LNULL) && i!= 0) {
        aux = aux->next;
        i--;
    }
    return aux;
}
bool insertItem(void * i, tList *L) {
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

/**
 * Initialize the archive log
 * @param archive
 */
void Initialize(tNode * arc[]){
    tFile * aux1 = malloc(sizeof (tFile));
    aux1->index = counterFiles;
    strcpy(aux1->CommandName,"standard entry ");
    strcpy(aux1->permit,"O_RDWR");
    insertItem(aux1,arc);
    counterFiles ++;
    tFile * aux2= malloc(sizeof (tFile));
    aux2->index = counterFiles;
    strcpy(aux2->CommandName,"standard output ");
    strcpy(aux2->permit,"O_RDWR");
    insertItem(aux2,arc);
    counterFiles ++;
    tFile * aux3= malloc(sizeof (tFile));
    aux3->index = counterFiles;
    strcpy(aux3->CommandName,"standard error ");
    strcpy(aux3->permit,"O_RDWR");
    insertItem(aux3,arc);
    counterFiles ++;

}

/**
 * GameLoop
 * @param argc
 * @param argv
 */
int main(int argc, char * argv[], char * enviroment[]){

    createEmptyList(Historical_List);
    createEmptyList(Archive);
    createEmptyList(memLog);
    envi  = enviroment;

    Initialize(Archive);

    bool ended = false;
    while (!ended)
    {
        char * chunks[10];
        PrintPromt();
        ReadEntry();
        ProcessingEntry(chunks);

    }

    return 0;
}
