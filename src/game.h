#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H

#include <time.h>
#include "multiple_source_moves_list.h"


void playGame(Board board, Player starting_player);
void turn(Board board, Player player);
Player swapPlayer(Player curr_player);
SingleSourceMovesList *chooseBestMove(MultipleSourceMovesList *all_possible_moves);
MultipleSourceMovesListCell **getBestMovesPtrArr(MultipleSourceMovesList *all_possible_moves, int *log_size);
short getMostCapturesInTurn(MultipleSourceMovesList *all_possible_moves);
int isEndGame(Board board, Player player);
int pawnsLeft(Board board, Player player);
void initBoard(Board board);

#endif