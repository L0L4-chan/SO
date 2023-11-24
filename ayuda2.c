//
// Created by lola on 30/10/23.
//* lo que esta en comentarios con 2 * /**
//depende de las funciones que se hayan hecho para la lista **/
//
//
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "p0.h"



#define TAMANO 2048


void ImprimirListaMmap(){

    printf("Blocks assigned to the process %d \n", getpid());

    if(!isEmptyList(memoryLog)){
        printf("ADDRESS\t\t\tSIZE\t\tTYPE\t     NAME\tPMRT\t  DATE\t\tKEY\tDESCRIPTOR\n");
        tPos pos = first(memoryLog);
        tMemList * aux = malloc(sizeof (tMemList));
        while(pos!=NULL){
            aux = (tMemList *)getItem(pos, memoryLog);
            printf("%p\t%15d\t%12s\t%10s\t%5s\t%s\t%5s\t%5d\n",aux->addr, aux->size, aux->type,aux->name ,aux->permit, aux->date, aux->key, aux->descriptors);
            pos = next(pos, memoryLog);
        }
        free(aux);
    }
}

void ImprimirListaMmapOnly(){

    printf("Blocks assigned to the process %d \n", getpid());

    if(!isEmptyList(memoryLog)){
        printf("ADDRESS\t\t\tSIZE\t\tTYPE\t     NAME\t PMRT\t  DATE\t  DESCRIPTOR\n");
        tPos pos = first(memoryLog);
        tMemList * aux = malloc(sizeof (tMemList));
        while(pos!=NULL){
            aux = (tMemList *)getItem(pos, memoryLog);
            if(!strcmp(aux->type,"mapped file")) {
                printf("%p\t%15d\t%12s\t%10s\t%5s\t%s\t%5d\n",aux->addr, aux->size, aux->type,aux->name ,aux->permit, aux->date, aux->descriptors);
            }
            pos = next(pos, memoryLog);
        }
        free(aux);
    }
}

void ImprimirShared(){
    printf("Shared blocks assigned to the process %d \n", getpid());

    if(!isEmptyList(memoryLog)){
        printf("ADR          SZ         DT        K \n");
        tPos pos = first(memoryLog);
        tMemList * aux = malloc(sizeof (tMemList));
        while(pos!=NULL){
            aux = (tMemList *)getItem(pos, memoryLog);
            if(!strcmp(aux->type,"shared")) {
                printf("%p    %d      %s        %s \n", aux->addr, aux->size, aux->date, aux->key);
            }
            pos = next(pos, memoryLog);
        }
        free(aux);
    }

}

void ImprimirListaMalloc(){

    printf("Blocks assigned to the process %d \n", getpid());

    if(!isEmptyList(memoryLog)){
        printf("ADR          SZ         DT   \n");
        tPos pos = first(memoryLog);
        tMemList * aux = malloc(sizeof (tMemList));
        while(pos!=NULL){
            aux = (tMemList *)getItem(pos, memoryLog);
            if(!strcmp(aux->type,"malloc")) {
                printf("%p    %d      %s \n", aux->addr, aux->size, aux->date);
            }
            pos = next(pos, memoryLog);
        }
        free(aux);
    }
}

void Recursiva (int n)
{
  char automatico[TAMANO];
  static char estatico[TAMANO];

  printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

  if (n>0)
    Recursiva(n-1);
}


void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
  unsigned char *arr=(unsigned char *) p;
  size_t i;

  for (i=0; i<cont;i++)
		arr[i]=byte;
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam)
{
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;

    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
        {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
             shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
// InsertarNodoShared (&L, p, s.shm_segsz, clave); */
    return (p);
}
void SharedCreate (char *tr[]){
   key_t cl;
   size_t tam;
   void *p;


   cl=(key_t)  strtoul(tr[2],NULL,10);
   tam=(size_t) strtoul(tr[3],NULL,10);
    if (tam==0) {
        printf ("0 bytes is not a valid size\n");
        return ;
    }
    if ((p=ObtenerMemoriaShmget(cl,tam))!=NULL) {
        printf("Assign %lu bytes on %p\n", (unsigned long) tam, p);
        tMemList * block = malloc(sizeof( tMemList));
        block->addr = p;
        strcpy(block->type, "shared");
        block->size = (int)tam;
        strcpy(block->key, tr[2]);
        time_t t = time(NULL);
        struct tm tiempoLocal = *localtime(&t);
        char date[20];
        char *formato = "%H:%M:%S";
        int datebytes = (int)strftime(date, sizeof date, formato, &tiempoLocal);
        if (datebytes != 0) {
            strcpy(block->date,date);
        } else {
            perror("Output error\n");
        }
        insertItem(block, memLog);
        printf ("shared memory with key %s is part of the this process\n" , block->key);
        return;
    } else{
		printf ("Impossible to assign shared memory with key %lu:%s\n",(unsigned long) cl,strerror(errno));
        return ;
    }
}
//
//
void * MapearFichero (char * fichero, int protection, char *  perm)
{
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;

    if (protection&PROT_WRITE)
          modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
          return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)// falla aqui con los creados por nosotros
           return NULL;
    tMemList * block = malloc(sizeof( tMemList));
    block->addr = p;
    strcpy(block->type , "mapped");
    block->size =(int) s.st_size;
    strcpy(block->name, fichero);
    block->descriptors = df;
    strcpy(block->permit, perm);
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char date[20];
    char *formato = "%H:%M:%S";
    int datebytes = (int)strftime(date, sizeof date, formato, &tiempoLocal);
    if (datebytes != 0) {
        strcpy(block->date, date);
    } else {
        perror("Output error\n");
    }
    insertItem(block, memLog);

    return p;
}
//
void CmdMmap(char *arg[])
{
     char *perm;
     void *p;
     int protection=0;

     if (arg[1]==NULL)
            {
         ImprimirListaMmapOnly();
          return;}
     if (!strcmp(arg[1], "-free")){
         tPos pos = first(memoryLog);
         tMemList * aux = malloc(sizeof (tMemList));
         while (pos != NULL) {
             aux = (tMemList *) getItem(pos, memoryLog);
             if (!strcmp(arg[2], aux->name)) {
                 munmap(aux->addr,aux->size);
                 printf("file %s has been unmapped", aux->name);
                 deleteAtPosition(pos, memLog);
                 return;
             }
             pos = next(pos, memoryLog);
         }
         free(aux);
     }else{
         if ((perm=arg[2])!=NULL && strlen(perm)<4) {
                if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
                if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
                if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
         }
         if ((p=MapearFichero(arg[1],protection, arg[2]))==NULL)
                 perror ("Impossible to map file\n");
         else
                 printf ("file %s mapped at %p\n", arg[1], p);
    }
}

void SharedDelkey (char *args[])
{
   key_t clave;
   int id;
   char *key=args[2];

   if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
   }
   if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: impossible to obtain shared memory");
        return;
   }
   if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: impossible to remove the id of the shared memory\n");
}
//
//
ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite)
{
   ssize_t  n;
   int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY;

   if (overwrite)
	flags=O_CREAT | O_WRONLY | O_TRUNC;


  if ((df=open(f,flags,0777))==-1)
	return -1;

   if ((n=write(df,p,cont))==-1){
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

ssize_t LeerFichero (char *f, void *p, size_t cont)
{
   struct stat s;
   ssize_t  n;
   int df,aux;

   if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
	return -1;
   if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
	cont=s.st_size;
   if ((n=read(df,p,cont))==-1){
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
  return n;
}

//void CmdRead (char *ar[])
//{
//   void *p;
//   size_t cont=-1;  /* -1 indica leer todo el fichero*/
//   ssize_t n;
//   if (ar[0]==NULL || ar[1]==NULL){
//	printf ("faltan parametros\n");
//	return;
//   }
//   p = cadtop(ar[1]);  /*convertimos de cadena a puntero*/
//   if (ar[2]!=NULL)
//	cont=(size_t) atoll(ar[2]);

//   if ((n=LeerFichero(ar[0],p,cont))==-1)
//	perror ("Imposible leer fichero");
//   else
//	printf ("leidos %lld bytes de %s en %p\n",(long long) n,ar[0],p);
//}

void Do_MemPmap (void) /*sin argumentos*/
 { pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
   char elpid[32];
   char *argv[4]={"pmap",elpid,NULL};

   sprintf (elpid,"%d", (int) getpid());
   if ((pid=fork())==-1){
      perror ("Imposible crear proceso");
      return;
      }
   if (pid==0){ /*proceso hijo*/
      if (execvp(argv[0],argv)==-1)
         perror("cannot execute pmap (linux, solaris)");

      argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
      if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
         perror("cannot execute vmmap (Mac-OS)");

      argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;
      if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
         perror("cannot execute procstat (FreeBSD)");

      argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;
            if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
         perror("cannot execute procmap (OpenBSD)");

      exit(1);
  }
  waitpid (pid,NULL,0);
 }
void *cadtop(char *dir){
    void* aux=(void *)strtol(dir, NULL, 16);
    if(aux!=NULL) return aux;
    else return (void *)dir;
}