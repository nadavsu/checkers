#ifndef CHECKERS_MULTIPLE_SOURCE_MOVES_LIST_H
#define CHECKERS_MULTIPLE_SOURCE_MOVES_LIST_H

#include "single_source_moves_list.h"

typedef struct MultipleSourceMovesListCell{
    SingleSourceMovesList               *single_source_moves_list;
    struct MultipleSourceMovesListCell *next;
} MultipleSourceMovesListCell;

typedef struct MultipleSourceMovesList{
    MultipleSourceMovesListCell *head;
    MultipleSourceMovesListCell *tail;
} MultipleSourceMovesList;

MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);
MultipleSourceMovesList *allocateMSMList();
MultipleSourceMovesListCell *createNewMSMListNode(SingleSourceMovesList *ssm_list);
void addToMSMList(MultipleSourceMovesList *list, MultipleSourceMovesListCell *cell);
void addToEmptyMSMList(MultipleSourceMovesList *list, MultipleSourceMovesListCell *cell);
void addToEndMSMList(MultipleSourceMovesList *list, MultipleSourceMovesListCell *cell);
void freeMSMList(MultipleSourceMovesList *msm_list);

#endif //CHECKERS_MULTIPLE_SOURCE_MOVES_LIST_H
