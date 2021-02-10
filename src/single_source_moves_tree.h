#ifndef CHECKERS_SINGLE_SOURCE_MOVES_TREE_H
#define CHECKERS_SINGLE_SOURCE_MOVES_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include "CUI.h"

#define MALLOC_ERROR_CODE_MESSAGE "Memory allocation error!"
#define MALLOC_ERROR_CODE   10

#define LEFT                0
#define RIGHT               1

#define T_LEFT_MOVE(NUM_OF_MOVES)       row + NUM_OF_MOVES, col - NUM_OF_MOVES, board, 'T'
#define T_RIGHT_MOVE(NUM_OF_MOVES)      row + NUM_OF_MOVES, col + NUM_OF_MOVES, board, 'T'
#define B_LEFT_MOVE(NUM_OF_MOVES)       row - NUM_OF_MOVES, col - NUM_OF_MOVES, board, 'B'
#define B_RIGHT_MOVE(NUM_OF_MOVES)      row - NUM_OF_MOVES, col + NUM_OF_MOVES, board, 'B'


typedef struct _checkersPos{
    char row, col;
} checkersPos;


typedef struct _SingleSourceMovesTreeNode{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far;
    struct _SingleSourceMovesTreeNode *next_move[2];
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMoves{
    SingleSourceMovesTreeNode *source;
} SingleSourceMovesTree;

struct _SingleSourceMovesList;

SingleSourceMovesTree *findSingleSourceMoves(Board board, checkersPos *src);
SingleSourceMovesTreeNode *newSingleSourceMovesTreeNode(Board board, checkersPos *pos, unsigned short captures);
void createMovesTreeForT(SingleSourceMovesTreeNode *root, Board board, int row, int col, unsigned short captures);
void createMovesTreeForB(SingleSourceMovesTreeNode *root, Board board, int row, int col, unsigned short captures);
int isValidMove(int row, int col, Board board, Player p);
void freeSingleSourceMovesTreeAUX(SingleSourceMovesTreeNode *root);
checkersPos *coordToPos(int row, int col);
void posToCoord(checkersPos *pos, int *row, int *col);
void updateLeftAndRightCaptures(SingleSourceMovesTreeNode *curr_tree_node, short *left_captures, short *right_captures);
void performMove(Board board, Player player, checkersPos *start_pos, checkersPos *end_pos);
struct _SingleSourceMovesList *findSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
void freeSSMTree(SingleSourceMovesTree *tree);
void checkMemAllocation(void *allocation);

#endif //CHECKERS_SINGLE_SOURCE_MOVES_TREE_H
