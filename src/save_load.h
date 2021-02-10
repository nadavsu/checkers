#ifndef CHECKERS_GIT_SAVE_LOAD_H
#define CHECKERS_GIT_SAVE_LOAD_H

#include "game.h"

#define EMPTY_CELL_CODE         0x00
#define TOP_DOWN_PLAYER_CODE    0X01
#define BOTTOM_UP_PLAYER_CODE   0x02

#define TWO_LSB_MASK            0x03

#define FILE_ERROR_CODE         11

unsigned char encodeCells(const unsigned char *cell_arr);
void storeBoard(Board board, char *file_name);
void loadBoard(Board board, char *file_name);
void decodeCells(unsigned char *board, unsigned char byte);
void checkFile(FILE *file);

#endif //CHECKERS_GIT_SAVE_LOAD_H
