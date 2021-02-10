#include "CUI.h"
#include "game.h"
#include "save_load.h"

int main(int argc, char *argv[]) {
    Board board;
    int player_input = 0;
    char path_of_game_to_load[4096];
    srand(time(NULL));


    while (player_input != 3) {
        printMainMenu();
        scanf("%d", &player_input);
        if(player_input == 1) {
            playGame(board, TOP_DOWN_PLAYER);
        } else if (player_input == 2) {
            printf("Enter path of the save file: ");
            scanf("%s", path_of_game_to_load);
            loadBoard(board, path_of_game_to_load);
            playGame(board, TOP_DOWN_PLAYER);
        } else if (player_input == 3) {
            return 0;
        } else {
                printf(INVALID_INPUT_MESSAGE);
                printf("\n");
        }
    }
}