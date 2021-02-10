///Checkers - Made by Nadav Suliman


#include "game.h"

/*!
 * Starts a checkers game - computer vs computer. Doing turns while the game doesn't end.
 * @params: A starting board, and the starting player.
 */
void playGame(Board board, Player starting_player){
    Player other_player = swapPlayer(starting_player);
    Player curr_player = starting_player;

    initBoard(board);
    printTitle("New game: Computer vs. Computer");
    printBoard(board);
    if(starting_player == TOP_DOWN_PLAYER || starting_player == BOTTOM_UP_PLAYER) {
        if(isEndGame(board, other_player)){
            return;
        }
        while (!isEndGame(board, curr_player)) {
            turn(board, curr_player);
            curr_player = swapPlayer(curr_player);
        }
    } else{
        fprintf(stderr, INVALID_INPUT_MESSAGE);
    }
}

/*!
 * Plays the turn on the board by creating a MultipleSourceMovesList which contains all possible player moves. The
 * function finds the best move and stores it in a SingleSourceMovesList. The move is then performed.
 * @params: the current board, and the current player.
 */
void turn(Board board, Player player){
    MultipleSourceMovesList *msm_list;
    SingleSourceMovesList *best_move_list;
    SingleSourceMovesListCell *best_move_cell;

    msm_list = FindAllPossiblePlayerMoves(board, player);
    best_move_list = chooseBestMove(msm_list);
    if(!best_move_list){
        printMove(best_move_list, player, board);
        freeMSMList(msm_list);
        board[0][0] = 0;
        return;
    }

    best_move_cell = best_move_list->head;
    while(best_move_cell && best_move_cell->next){
        performMove(board, player, best_move_cell->position, best_move_cell->next->position);
        best_move_cell = best_move_cell->next;
    }
    printMove(best_move_list, player, board);
    freeMSMList(msm_list);
}

/*!
 * Checks for winning conditions in the board - checking for draw, checking for player reaching the other side and checking
 * for player with no pawns left.
 * @params: the current board, the current player.
 * @return: 1 if the game has ended, otherwise returns 0.
 */
int isEndGame(Board board, Player player){
    int i;
    Player other_player = swapPlayer(player);

    if(!pawnsLeft(board, player)){
        printWinMessage(other_player);
        return 1;
    }
    if(board[0][0] == 0){
        printf("No moves possible! The game has ended with a draw!");
        return 1;
    }
    else {
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[0][i] == BOTTOM_UP_PLAYER){
                printWinMessage(BOTTOM_UP_PLAYER);
                return 1;
            } else if(board[7][i] == TOP_DOWN_PLAYER){
                printWinMessage(TOP_DOWN_PLAYER);
                return 1;
            }
        }
        return 0;
    }
}

/*!
 * Checks if there are any pawns left in the game by going through the board and looking for a player.
 * @params: current board, current player.
 * @return: the number of pawns left for the current player.
 */
int pawnsLeft(Board board, Player player){
    int j, i;
    for(i = 0; i < BOARD_SIZE; i++){
        for(j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] == player){
                return 1;
            }
        }
    }
    return 0;
}


/*!
 * Swaps curr_player to the other player in the board.
 * @params: the current player
 * @returns: the other player.
 */
Player swapPlayer(Player curr_player){
    if(curr_player == TOP_DOWN_PLAYER){
        return BOTTOM_UP_PLAYER;
    }
    return TOP_DOWN_PLAYER;
}

/*!
 * Chooses the best move out of all the best moves for each pawn. The function creates an array of
 * pointers to MultipleSourceMovesListCell which contain the maximum number of moves out of the whole MSM list. Then,
 * the function chooses one of these randomly.
 * @params:  MultipleSourceMovesList all_possible_moves - the MSMList to choose the best move from
 * @returns: A SingleSourceMovesList containing the best move out of all_possible_moves.
 *          Returns NULL if there is nowhere to move.
 */
SingleSourceMovesList *chooseBestMove(MultipleSourceMovesList *all_possible_moves){
    MultipleSourceMovesListCell **best_moves_arr;
    SingleSourceMovesList *best_move;
    int arr_size, randomMove;
    arr_size = 0;

    best_moves_arr = getBestMovesPtrArr(all_possible_moves, &arr_size);

    if(best_moves_arr) {
        best_moves_arr = (MultipleSourceMovesListCell **) realloc(best_moves_arr, sizeof(MultipleSourceMovesListCell *) * arr_size);
        randomMove = rand() % arr_size;
        best_move = best_moves_arr[randomMove]->single_source_moves_list;
        free(best_moves_arr);
        return best_move;
    }
    else{
        return NULL;
    }

}

/*!
 * Creates and returns a new array of pointers to MultipleSourceMovesListCell. Each pointer points to the best move
 * out of the all_possible_moves list (there may be many best moves). A best move is defined to be a move with the most captures.
 * @params: MultipleSourceMovesList all_possible_moves - containing all possible moves in current turn
 *         int *log_size - the logical size of the array. Can be sent with 1.
 * @return: an array of pointers to MultipleSourceMovesListCell. Each pointer points to a SinglesSourceMovesList
 *          containing the best move.
 */
MultipleSourceMovesListCell **getBestMovesPtrArr(MultipleSourceMovesList *all_possible_moves, int *log_size) {
    MultipleSourceMovesListCell *curr_all_possible_moves_cell = all_possible_moves->head;
    SingleSourceMovesListCell *curr_ssm_cell;
    MultipleSourceMovesListCell **best_moves_arr = NULL;

    int most_captures = getMostCapturesInTurn(all_possible_moves);
    int phy_size = 0;

    while (curr_all_possible_moves_cell) {
        curr_ssm_cell = curr_all_possible_moves_cell->single_source_moves_list->head;
        if (curr_ssm_cell->captures == most_captures && curr_ssm_cell->next) {  //If there's somewhere to move and the current SSM Cell is a move with maximum captures:
            if (phy_size == *log_size) {                            //Checking if the array is full
                phy_size = phy_size * 2 + 1;                        //Doubling array size.
                best_moves_arr = (MultipleSourceMovesListCell **) realloc(best_moves_arr,sizeof(MultipleSourceMovesListCell *) *phy_size);
                checkMemAllocation(best_moves_arr);
            }
            best_moves_arr[*log_size] = curr_all_possible_moves_cell;                   //Adding the pointer to current curr_all_possible_moves_cell to the array.
            (*log_size)++;
        }
        curr_all_possible_moves_cell = curr_all_possible_moves_cell->next;
    }
    return best_moves_arr;
}

/*!
 *  Gets the most captures in a given turn. Each cell in all_possible_moves points to a SingleSourceMovesList which
 *  contains the number of captures inside each cell. The function goes through every head of the SingleSourceMovesList
 *  inside all_possible_moves and finds the maximum number of captures in all_possible_moves.
 *  @params: MultipleSourceMovesList all_possible_moves - all possible moves in the current turn.
 *  @return: The most captures found in all_possible_moves list.
 */
short getMostCapturesInTurn(MultipleSourceMovesList *all_possible_moves){
    short most_captures, curr_captures;
    MultipleSourceMovesListCell *curr_msm_cell;
    SingleSourceMovesListCell *curr_ssm_cell;

    most_captures = 0;
    curr_msm_cell = all_possible_moves->head;

    while(curr_msm_cell){
        curr_ssm_cell = curr_msm_cell->single_source_moves_list->head;
        curr_captures = curr_ssm_cell->captures;
        if(curr_captures > most_captures) {
            most_captures = curr_captures;
        }
        curr_msm_cell = curr_msm_cell->next;
    }

    return most_captures;
}

/*!
 * Initiates a new checkers board in the starting position of a checkers board.
 * @params: a board to be initialized.
 */
void initBoard(Board board) {
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++){
        for(j = 0; j < BOARD_SIZE; j++){
            board[i][j] = EMPTY_CELL;
        }
    }
    for(i = 0; i < 3; i++){
        for(j = i % 2; j < BOARD_SIZE; j += 2){
            board[i][j] = TOP_DOWN_PLAYER;
        }
    }

    for(i = BOARD_SIZE - 1; i > 4; i--){
        for(j = i % 2; j < BOARD_SIZE; j += 2){
            board[i][j] = BOTTOM_UP_PLAYER;
        }
    }
}
