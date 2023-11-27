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
        //printf("%d\n", real);
       struct passwd real_p= * getpwuid(real);
       struct passwd effe_p= * getpwuid(effective);
       printf("Real user: %s \n",  real_p.pw_name);
       printf("Effective user: %s \n",  effe_p.pw_name );

    }else if(index ==2 ){// credencial real y efectiva del usuario  get
        if(!strcmp(command[1], "-get")) {
            SetUID(command, 1);
        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }
    }else if(index == 3){ // set id (numerico) y un numero cambia la credencial https://man7.org/linux/man-pages/man2/setuid.2.html
        if(!strcmp(command[1], "-set")) {
            uid_t id = (uid_t) atoi(command[2]);
            if(setuid(id)==0){
                printf("User %s has been set as effective user\n", command[2]);

            }else{
                perror("impossible to performance this action\n");
            }

        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }
    }else if(index == 4){ // set -l id (numerico)  establece la credencial a ligin id
        if(!strcmp(command[1], "-set") &&!strcmp(command[2], "-l") ) {
            struct passwd nw = *getpwnam(command[3]);
            if(setuid(nw.pw_uid)==0){
                printf("User %s has been set as effective user\n", command[3]);

            }else{
                perror("impossible to performance this action\n");
            }


        }else{
            printf("Unrecognized command, please try again or write \"help\" for help.\n");
        }
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