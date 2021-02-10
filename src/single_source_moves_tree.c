#include "single_source_moves_tree.h"
#include "single_source_moves_list.h"

//A function used to create a moves tree for the player at the current position.
SingleSourceMovesTree *findSingleSourceMoves(Board board, checkersPos *src) {
    SingleSourceMovesTree *tree;
    Player player;
    int row, col;
    posToCoord(src, &row, &col);
    player = board[row][col];           //Setting the player to be the character at board[row][col]

    tree = (SingleSourceMovesTree *) malloc(sizeof(SingleSourceMovesTree));     //Allocating a new tree.
    checkMemAllocation(tree);                                                   //Checking allocation
    if(player == TOP_DOWN_PLAYER){
        tree->source = newSingleSourceMovesTreeNode(board, src, 0);             //Creating a root for the tree.
        createMovesTreeForT(tree->source, board, row, col, 0);                  //Calling the auxiliary function to create a moves tree for T current player.
        return tree;
    } else if(player == BOTTOM_UP_PLAYER) {
        tree->source = newSingleSourceMovesTreeNode(board, src, 0);              //Creating a root for the tree.
        createMovesTreeForB(tree->source, board, row, col, 0);                   //Calling the auxiliary function to create a moves tree for B current player.
        return tree;
    } else {
        fprintf(stderr, "The given player is not legal! Must be ");
        fprintf(stderr, "%c", BOTTOM_UP_PLAYER);
        fprintf(stderr, " or ");
        fprintf(stderr, "%c", TOP_DOWN_PLAYER);       //If the player is not valid
        return NULL;
    }
}

//An auxiliary function used to create the tree if it's T's turn.
//NOTE: the defines in this function (e.g. T_LEFT_MOVE(N)) indicates the N moves to the left/right of the player.
void createMovesTreeForT(SingleSourceMovesTreeNode *root, Board board, int row, int col, unsigned short captures) {
    if(!isValidMove(T_LEFT_MOVE(1)) && !isValidMove(T_RIGHT_MOVE(1))){                              //CASE 1: Both moves left and right are not valid.
        return;
    } else{                                                                                     //CASE 2:  Conditions for left moves.
        if(isValidMove(T_LEFT_MOVE(1)) && captures == 0 && board[row + 1][col - 1] == EMPTY_CELL){     //CASE 2A: The player hasn't captured yet and the next move left is empty.
            checkersPos *new_pos = coordToPos(row + 1, col - 1);                                    //Creating a new position with the position of 1 move to the left.
            root->next_move[LEFT] = newSingleSourceMovesTreeNode(board, new_pos, captures);         //Creating a new SSMTree node and adding it to the left of the current node.
            performMove(root->next_move[LEFT]->board, TOP_DOWN_PLAYER, root->pos, new_pos);                     //Update the board of the tree node with the new position
        } else if(isValidMove(T_LEFT_MOVE(1)) && board[row + 1][col - 1] == BOTTOM_UP_PLAYER){               //CASE 2B: The move to the left is valid and the next move to the left is BOTTOM_UP_PLAYER.
            if(isValidMove(T_LEFT_MOVE(2)) && board[row + 2][col - 2] != BOTTOM_UP_PLAYER){                      //CASE 2Ba: The function checks if the next 2 moves are valid, and are not a BOTTOM_UP_PLAYER, in order to capture.
                checkersPos *new_pos = coordToPos(row + 2, col - 2);                                //Creating a new checkersPos with the position after capturing left.
                root->next_move[LEFT] = newSingleSourceMovesTreeNode(board, new_pos, captures + 1); //Creating a new node for the tree and putting it in the left of current node
                performMove(root->next_move[LEFT]->board, TOP_DOWN_PLAYER, root->pos, new_pos);                 //Update the board of the tree node with the new position
                createMovesTreeForT(root->next_move[LEFT], board, row + 2, col - 2, captures + 1);  //Calling the function recursively with the new position after capturing.
            }
        }                                                                                       //CASE 3:  Conditions for the right moves.
        if(isValidMove(T_RIGHT_MOVE(1)) && captures == 0 && board[row + 1][col + 1] == EMPTY_CELL){    //CASE 3A: The player hasn't captured yet and the next move right is empty.
            checkersPos *new_pos = coordToPos(row + 1, col + 1);                                //Creating a new pos with the new move.
            root->next_move[RIGHT] = newSingleSourceMovesTreeNode(board, new_pos, captures);    //Creating a new node with the pos created and adding it to the right branch.
            performMove(root->next_move[RIGHT]->board, TOP_DOWN_PLAYER, root->pos, new_pos);                 //Update the board of the tree node with the new position
        } else if(isValidMove(T_RIGHT_MOVE(1)) && board[row + 1][col + 1] == BOTTOM_UP_PLAYER){              //CASE 3B: The next move right is valid and the next to right is BOTTOM_UP_PLAYER
            if(isValidMove(T_RIGHT_MOVE(2)) && board[row + 2][col + 2] != BOTTOM_UP_PLAYER){                 //The function checks if the next 2 moves are valid, and are not a BOTTOM_UP_PLAYER, in order to capture.
                checkersPos *new_pos = coordToPos(row + 2, col + 2);                            //Creating a new checkersPos with the position after capturing right.
                root->next_move[RIGHT] = newSingleSourceMovesTreeNode(board, new_pos, captures + 1);    //Creating a new node for the tree and putting it in the right of current node.
                performMove(root->next_move[RIGHT]->board, TOP_DOWN_PLAYER, root->pos, new_pos);                    //Update the board of the tree node with the new position
                createMovesTreeForT(root->next_move[RIGHT], board, row + 2, col + 2, captures + 1);     //Calling the function recursively with the new position after capturing.
            }
        }
        return;
    }
}

//An auxiliary function used to create a tree if it's B's turn.
//The function works the same way as createMovesTreeForT, just with the left and right moves and players adjusted.
void createMovesTreeForB(SingleSourceMovesTreeNode *root, Board board, int row, int col, unsigned short captures){
    if(!isValidMove(B_LEFT_MOVE(1)) && !isValidMove(B_RIGHT_MOVE(1))){
        return;
    } else{
        if(isValidMove(B_LEFT_MOVE(1)) && captures == 0 && board[row - 1][col - 1] == EMPTY_CELL){
            checkersPos *new_pos = coordToPos(row - 1, col - 1);
            root->next_move[LEFT] = newSingleSourceMovesTreeNode(board, new_pos, captures);
            performMove(root->next_move[LEFT]->board, BOTTOM_UP_PLAYER, root->pos, new_pos);
        } else if(isValidMove(B_LEFT_MOVE(1)) && board[row - 1][col - 1] == TOP_DOWN_PLAYER){
            if(isValidMove(B_LEFT_MOVE(2)) && board[row - 2][col - 2] != TOP_DOWN_PLAYER){
                checkersPos *new_pos = coordToPos(row - 2, col - 2);
                root->next_move[LEFT] = newSingleSourceMovesTreeNode(board, new_pos, captures + 1);
                performMove(root->next_move[LEFT]->board, BOTTOM_UP_PLAYER, root->pos, new_pos);
                createMovesTreeForB(root->next_move[LEFT], board, row - 2, col - 2, captures + 1);
            }
        }
        if(isValidMove(B_RIGHT_MOVE(1)) && captures == 0 && board[row - 1][col + 1] == EMPTY_CELL){
            checkersPos *new_pos = coordToPos(row - 1, col + 1);
            root->next_move[RIGHT] = newSingleSourceMovesTreeNode(board, new_pos, captures);
            performMove(root->next_move[RIGHT]->board, BOTTOM_UP_PLAYER, root->pos, new_pos);
        } else if(isValidMove(B_RIGHT_MOVE(1)) && board[row - 1][col + 1] == TOP_DOWN_PLAYER){
            if(isValidMove(B_RIGHT_MOVE(2)) && board[row - 2][col + 2] != TOP_DOWN_PLAYER){
                checkersPos *new_pos = coordToPos(row - 2, col + 2);
                root->next_move[RIGHT] = newSingleSourceMovesTreeNode(board, new_pos, captures + 1);
                performMove(root->next_move[RIGHT]->board, BOTTOM_UP_PLAYER, root->pos, new_pos);
                createMovesTreeForB(root->next_move[RIGHT], board, row - 2, col + 2, captures + 1);
            }
        }
        return;
    }
}

/*! Chooses the best move from a given moves tree.
 * It chooses the path which gives the most captures, and creates a list out of it. */
SingleSourceMovesList *findSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree){
    short max_captures, left_captures, right_captures;
    unsigned int randomMove;
    SingleSourceMovesListCell *new_list_node;
    SingleSourceMovesTreeNode *curr_tree_node;
    SingleSourceMovesList *list = allocateEmptySSMList();               //Allocating a new empty SSMList.

    max_captures = findMaxCaptures(moves_tree->source);                 //Finding the maximum number of captures in the tree (read function description)
    curr_tree_node = moves_tree->source;                                //Pointing to the root of the tree
    new_list_node = createNewSSMListNode(curr_tree_node->total_captures_so_far, curr_tree_node->pos);   //Creating a new list node from the first position.
    addToEmptySSMList(list, new_list_node);                             //Adding that first node to an empty list of moves.

    updateLeftAndRightCaptures(curr_tree_node, &left_captures, &right_captures);    //Storing the captures in the left and right tree nodes from root.

    if(left_captures == right_captures && left_captures != -1){                     //Choosing a move randomly if there are two branches with the same captures.
        randomMove = (unsigned int)rand() % 2;
        curr_tree_node = curr_tree_node->next_move[randomMove];
    }
    else if (curr_tree_node->next_move[LEFT] && left_captures == max_captures){     //Traversing left if the max captures path is on the left.
        curr_tree_node = curr_tree_node->next_move[LEFT];
    }
    else if (curr_tree_node->next_move[RIGHT] && right_captures == max_captures){   //Traversing right if max captures path is on the right.
        curr_tree_node = curr_tree_node->next_move[RIGHT];
    }
    else{
        return list;
    }

    while (curr_tree_node && curr_tree_node->total_captures_so_far == max_captures) {   //Traversing the tree while we're not in a leaf.
        new_list_node = createNewSSMListNode(curr_tree_node->total_captures_so_far, curr_tree_node->pos);   //Creating a new SSMList node and adding the current tree root to it.
        addToEndSSMList(list, new_list_node);
        updateLeftAndRightCaptures(curr_tree_node, &left_captures, &right_captures);    //Storing the captures of the left and right nodes from the root.
        if(left_captures == right_captures && left_captures != -1){         //Choosing a random move if we've reached a state where to paths have the same captures.
            randomMove = (unsigned)rand() % 2;
            curr_tree_node = curr_tree_node->next_move[randomMove];
        }
        else if (curr_tree_node->next_move[LEFT] && left_captures == max_captures){     //If max captures path is on the left, we traverse left.
            curr_tree_node = curr_tree_node->next_move[LEFT];
        }
        else if(curr_tree_node->next_move[RIGHT]) {                                     //If max captures path continues right then we traverse right.
            curr_tree_node = curr_tree_node->next_move[RIGHT];
        } else{
            curr_tree_node = NULL;
        }
    }

    return list;

}

//A function used to create a new SSM Tree node.
SingleSourceMovesTreeNode *newSingleSourceMovesTreeNode(Board board, checkersPos *pos, unsigned short captures){
    int i, j;
    SingleSourceMovesTreeNode *root;
    root = (SingleSourceMovesTreeNode *) malloc(sizeof(SingleSourceMovesTreeNode));     //Allocating memory for a new root.
    checkMemAllocation(root);

    root->next_move[LEFT] = NULL;               //Setting the values.
    root->next_move[RIGHT] = NULL;
    root->pos = pos;
    root->total_captures_so_far = captures;
    for(i = 0; i < BOARD_SIZE; i++){            //Copying the board to the tree node.
        for(j = 0; j < BOARD_SIZE; j++){
            root->board[i][j] = board[i][j];
        }
    }

    return root;
}

//A function that updates the board  with the new position
void performMove(Board board, Player player, checkersPos *start_pos, checkersPos *end_pos){
    int start_row, start_col, end_row, end_col;
    posToCoord(start_pos, &start_row, &start_col);
    posToCoord(end_pos, &end_row, &end_col);

    board[start_row][start_col] = EMPTY_CELL;
    board[end_row][end_col] = player;                        //Put the player in the new cell
    if(end_col - start_col == 2){                            // If there are captures
        if(player == TOP_DOWN_PLAYER) {
            board[start_row + 1][start_col + 1] = EMPTY_CELL;        //Put space instead of the pawn BOTTOM_UP_PLAYER
        }
        else{
            board[start_row - 1][start_col + 1] = EMPTY_CELL;        //Put space instead of the pawn TOP_DOWN_PLAYER
        }
    }
    if(end_col - start_col == -2){                             //Another case of a capture:
        if(player == TOP_DOWN_PLAYER){
            board[start_row + 1][start_col - 1] = EMPTY_CELL;         //Put space instead of the pawn BOTTOM_UP_PLAYER
        }
        else{
            board[start_row - 1][start_col - 1] = EMPTY_CELL;         //Put space instead of the pawn TOP_DOWN_PLAYER
        }
    }
}

//Converts pos to array row and col
void posToCoord(checkersPos *pos, int *row, int *col){
    *row = pos->row - 'A';
    *col = pos->col - '1';
}


//A function used to convert 2D array indexes into a variable of type checkersPos
checkersPos *coordToPos(int row, int col) {
    checkersPos *pos;
    pos = (checkersPos *) malloc(sizeof(checkersPos));  //Allocating new memory for the position.
    checkMemAllocation(pos);                            //Checking allocation.

    row = row + 'A';                                    //Converting row numbers to relevant chars.
    col = col + '1';
    pos->row = (char) row;
    pos->col = (char) col;

    return pos;
}

//Checks if the move for player p to row, col is valid.
int isValidMove(int row, int col, Board board, Player p){
    return (col >= 0 && col <= 7 && row <= 7 && row >= 0 && board[row][col] != p);
}


// A function that frees the tree
void freeSSMTree(SingleSourceMovesTree *tree){
    if(tree){                                               //Check if the tree is not NULL
        freeSingleSourceMovesTreeAUX(tree->source);
        free(tree);
    }
}

// the auxiliary function for the tree
void freeSingleSourceMovesTreeAUX(SingleSourceMovesTreeNode *root){
    if(!root->next_move[LEFT] && !root->next_move[RIGHT]){
        free(root->pos);
        free(root);
        return;
    } else{
        if(root->next_move[LEFT]) {
            freeSingleSourceMovesTreeAUX(root->next_move[LEFT]);           //Free left branch
        }
        if(root->next_move[RIGHT]) {
            freeSingleSourceMovesTreeAUX(root->next_move[RIGHT]);          //Free right branch
        }
        free(root->pos);                                                   //Free the position of the root
        free(root);                                                        //Free the root
        return;
    }
}