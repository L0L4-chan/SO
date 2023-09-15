#include <stdlib.h>
#include "dynamic_list.h"
#include "string.h"
/*
bool createNode(tPosL *p){
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}
void createEmptyList(tList *list) {
    *list = LNULL;
}
bool insertItem(tItemL item, tPosL pos, tList *list) {
    tPosL q, r;

    if (!createNode(&q))
        return false;
    else {
        q->itemL = item;
        q->posL = LNULL;
        if (*list == LNULL) //Lista vacÃ­a
            *list = q;
        else if (pos == LNULL) { //insertar al final de la lista vacÃ­a
            for (r = *list; r->posL != LNULL; r = r->posL);
            r->posL = q;
        }
        else if (pos == *list){ //insertar en posiciÃ³n primera
            q->posL = pos;
            *list = q;
        }
        else{ //insertar en posiciÃ³n intermedia
            q->itemL = pos->itemL; //mueve dato de p a q
            pos->itemL = item; //pone dato nuevo en p
            q->posL = pos->posL;
            pos->posL = q;
        }
        return true;
    }
}

void updateItem(tItemL item, tPosL pos, tList *list){
    pos->itemL = item;
}

void deleteAtPosition(tPosL pos, tList *list) {
    tPosL q;

    if (pos == *list)//borrar primer elemento
        *list = (*list)->posL;
    else if (pos->posL == LNULL) { //eliminar Ãºltima posiciÃ³n
        for(q = *list; q->posL != pos; q = q->posL); //bucar anterior de p
        q->posL = LNULL;
    }
    else{//eliminar posiciÃ³n intermendia
        q = pos->posL;
        pos->itemL = q->itemL;
        pos->posL = q->posL;
        pos = q; //se borra realmente el nodo siguiente a p

    }
}

tPosL findItem(tParticipantName participantName, tList list){
    tPosL p;

    for(p =  list; (p != LNULL) && strcmp(p->itemL.participantName, participantName); p = p->posL);
    return p;
}

bool isEmptyList(tList list){
    return list == LNULL;
}

tItemL getItem(tPosL pos, tList list){
    return pos->itemL;
}

tPosL first(tList list) {
    return list;
}

tPosL last(tList list) {
    tPosL pos;

    for(pos = list; pos->posL != LNULL; pos = pos->posL);
    return pos;
}

tPosL previous(tPosL pos, tList list) {
    tPosL q;

    if (pos == list)
        return LNULL;
    else {
        for (q = list; q->posL !=pos; q = q->posL);
        return q;
    }
}
tPosL next(tPosL pos, tList list){
    return pos->posL;
}
*/