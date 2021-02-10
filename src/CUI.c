//
// Created by Nadav Suliman on 4/4/20.
//

#include "CUI.h"

/*!
 * Prints the main menu of the game to the console.
 */
void printMainMenu() {
    printTitle("CHECKERS");
    printBody("1. New game (computer vs. computer)");
    printBody("2. Load board");
    printBody("3. Quit");
    printBody("Your option (1-3): ");
    printLine();
}

/*!
 * Prints a title to the console using the TITLE_STYLE defines in CUI.h
 * Params: the desired title to print
 */
void printTitle(const char *title) {
    int i;
    printf(TITLE_EDGE_STYLE);
    for (i = 0; i < PAGE_WIDTH - 2; ++i) {
        printf(TITLE_HLINE_STYLE);
    }
    printf(TITLE_EDGE_STYLE);
    printf("\n");
    printf(TITLE_VLINE_STYLE);
    for (i = 0; i < (PAGE_WIDTH - 2 - strlen(title)) / 2; ++i) {
        printf(TITLE_FILL_STYLE);
    }
    printf("%s", title);
    for (i = 0; i < (PAGE_WIDTH - 1 - strlen(title)) / 2; ++i) {
        printf(TITLE_FILL_STYLE);
    }
    printf(TITLE_VLINE_STYLE);
    printf("\n");
    printf(TITLE_EDGE_STYLE);
    for (i = 0; i < PAGE_WIDTH - 2; ++i) {
        printf(TITLE_HLINE_STYLE);
    }
    printf("+\n");
}

/*!
 * Prints a subtitle to the console using the SUBTITLE_STYLE defines in CUI.h
 * Params: a string of the subtitle.
 */
void printSubtitle(const char* subtitle) {
    int i;
    for (i = 0; i < (PAGE_WIDTH - strlen(subtitle)) / 2; ++i) {
        printf(SUBTITLE_LINE_STYLE);
    }
    printf("%s", subtitle);
    for (i = 0; i < (PAGE_WIDTH - strlen(subtitle)) / 2; ++i) {
        printf(SUBTITLE_LINE_STYLE);
    }
    printf("\n");
}

void printBody(const char *text) {
    int i = 0;
    printf(BODY_VLINE_STYLE);
    printf("%s", text);
    for (i = 0; i < PAGE_WIDTH - strlen(text) - 2; i++) {
        printf(BODY_FILL_STYLE);
    }
    printf(BODY_VLINE_STYLE);
    printf("\n");
}

/*!
 * Prints a line of width of PAGE_WIDTH using the TITLE_STYLEs (defined in CUI.h)
 */
void printLine() {
    printf(TITLE_EDGE_STYLE);
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        printf(BODY_HLINE_STYLE);
    }
    printf(TITLE_EDGE_STYLE);
    printf("\n");
}

/*!
 *  Prints the winning message of the current player.
 *  Params: the current Player.
 */
void printWinMessage(Player player) {
    if (player == TOP_DOWN_PLAYER) {
        printTitle("player TOP DOWN wins!");
    } else {
        printTitle("player BOTTOM UP wins!");
    }
    printf("\n\n");
}

/*!
 *  Prints the current state of the board.
 *  Params: the current board.
 */
void printBoard(Board board) {
    int i, j;
    printf("+---+---+---+---+---+---+---+---+---+\n");
    printf("|   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
    printf("+---+---+---+---+---+---+---+---+---+\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("| %c ", i + 'A');
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("| %c ", board[i][j]);

        }
        printf("|\n");
        printf("+---+---+---+---+---+---+---+---+---+\n");
    }
    printf("\n");
}
