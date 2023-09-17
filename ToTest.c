//
//  Created by lola on 17/09/2023.
//
// To test any piece of function that we do not understand how it works.
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


void TestMain(int argc, char * argv[])
{
char  hola [15] = {'h','o', 'l', 'a', ' ', 'm', 'u','n', 'd', 'o'} ;

char prueba[15];
for(int i = 0; i < 5; i++) {
    prueba[i] = *strtok(hola, "\n\t");
    printf(&prueba[i]);
}

}