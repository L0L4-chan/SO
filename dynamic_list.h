#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H


#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>


typedef char tParticipantName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tEUParticipant;

typedef struct tItemL {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemL;

/*
#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>

typedef char tParticipantName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tEUParticipant;

typedef struct tItemL {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemL;

#endif //PRO2_2023_P1_TYPES_H
*/






/*
#include "types.h"
#include <stdbool.h>

#define LNULL NULL


typedef struct tNode* PosL;
struct tNode {
    tItemL itemL;
    tPosL posL;
};
typedef tPosL List;

void createEmptyList (tList*);
bool insertItem(tItemL, tPosL, tList*);
void updateItem(tItemL, tPosL, tList*);
void deleteAtPosition(tPosL, tList*);
tPosL findItem(tParticipantName , tList);
bool isEmptyList(tList);
tItemL getItem(tPosL, tList);
tPosL first(tList);
tPosL last(tList);
tPosL previous(tPosL, tList);
tPosL next(tPosL, tList);
#endif

*/

