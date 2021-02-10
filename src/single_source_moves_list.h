#ifndef CHECKERS_SINGLE_SOURCE_MOVES_LIST_H
#define CHECKERS_SINGLE_SOURCE_MOVES_LIST_H

#include "single_source_moves_tree.h"
#include <string.h>

typedef struct _SingleSourceMovesListCell{
    checkersPos                         *position;
    unsigned short                      captures;
    struct _SingleSourceMovesListCell   *next;
} SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList{
    SingleSourceMovesListCell *head;
    SingleSourceMovesListCell *tail;
} SingleSourceMovesList;


unsigned short findMaxCaptures(SingleSourceMovesTreeNode *root);
int findMax(int a, int b);
SingleSourceMovesListCell* createNewSSMListNode(unsigned short captures, checkersPos *pos);
void addToEmptySSMList(SingleSourceMovesList *list, SingleSourceMovesListCell *new_cell);
void addToEndSSMList(SingleSourceMovesList *list, SingleSourceMovesListCell *new_cell);
void printMove(SingleSourceMovesList *move_list, Player player, Board board);
SingleSourceMovesList *allocateEmptySSMList();
void freeSSMList(SingleSourceMovesList *ssm_list);

#endif //CHECKERS_SINGLE_SOURCE_MOVES_LIST_H
