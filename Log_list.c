//
// Created by lola on 17/09/2023.
//
#include "Log_list.h"
#include <string.h>


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

    if (node == LNULL)
        return false;
    else {
        node->item = i;
        node->next = LNULL;

        if (*L == LNULL)
            *L = node;
        else
            last(*L)->next = node;
    }
    return true;
}
