//
// Created by lola on 25/11/23.
//

#include <pwd.h>
#include "p0.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"


void SetUID(char* command[], int index){
    if(index ==1){ // credencial real y efectiva del usuario https://man7.org/linux/man-pages/man2/getuid.2.html
       uid_t  real = getuid();
       uid_t effective = geteuid();
       struct passwd real_p= * getpwuid(real);
       struct passwd effe_p= * getpwuid(effective);
       printf("real user: %s \n",  real_p.pw_name);
       printf("effective user: %s \n",  effe_p.pw_name );

    }else if(index ==2 ){// credencial real y efectiva del usuario  get
        if(!strcmp(command[1], "-get")) {
            SetUID(command, 1);
        }
    }else if(index == 3){ // set id (numerico) y un numero cambia la credencial https://man7.org/linux/man-pages/man2/setuid.2.html

    }else if(index == 4){ // set -l id (numerico)  establece la credencial a ligin id

    }else {

    }



}
void ToShowVar(char* command[], int index){}
void ToChangeVar(char* command[], int index){}
void ToSubVar(char* command[], int index){}
void ToShowEnv(char* command[], int index){}

void SetFork(char* command[], int index){}
void SetEXEC(char* command[], int index){}
void ToJobS(char* command[], int index){}
void ToDelJobs(char* command[], int index){}
void ToJob(char* command[], int index){}
void ToUnknow1(char* command[], int index){}
void ToUnknow2(char* command[], int index){}