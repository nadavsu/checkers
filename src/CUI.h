//
// Created by Nadav Suliman on 4/4/20.
//

#ifndef CHECKERS_GIT_CUI_H
#define CHECKERS_GIT_CUI_H

#include <stdio.h>
#include <string.h>


#define PAGE_WIDTH      37

#define TITLE_HLINE_STYLE       "-"
#define TITLE_EDGE_STYLE        "+"
#define TITLE_VLINE_STYLE       "|"
#define TITLE_FILL_STYLE        " "

#define SUBTITLE_LINE_STYLE     "="

#define BODY_FILL_STYLE         " "
#define BODY_VLINE_STYLE        "|"
#define BODY_HLINE_STYLE        "-"

#define INVALID_INPUT_MESSAGE   "Invalid input!"

#define BOARD_SIZE              8
#define TOP_DOWN_PLAYER         'T'
#define BOTTOM_UP_PLAYER        'B'
#define EMPTY_CELL              ' '

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

void printMainMenu();
void printTitle(const char *title);
void printSubtitle(const char *subtitle);
void printBody(const char * text);
void printLine();
void printBoard(Board board);
void printWinMessage(Player player);

#endif //CHECKERS_GIT_CUI_H