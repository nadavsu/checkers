#include "single_source_moves_list.h"

/*!
 * A function used to find the maximum captures in a given tree.
 *  The function also updates the 'captures' in each node in the path from the root to the leaf with the max captures to
 *  the maximum number of captures in the tree, creating a 'path' of maximum captures
 *  This is done so findSingleSourceOptimalMove can find the path of the max captures
 */
unsigned short findMaxCaptures(SingleSourceMovesTreeNode *root){
    if (!root->next_move[LEFT] && !root->next_move[RIGHT])      //If at leaf, we just return the total captures so far.
        return root->total_captures_so_far;
    else {
        int captures_left, captures_right, max_captures;
        captures_left = captures_right = -1;

        if (root->next_move[LEFT]) {                            //Finding the maximum captures of the left subtree.
            captures_left = findMaxCaptures(root->next_move[LEFT]);
        }
        if (root->next_move[RIGHT]) {                           //Finding the maximum captures of the right subtree.
            captures_right = findMaxCaptures(root->next_move[RIGHT]);
        }
        max_captures = findMax(captures_left, captures_right);  //Finding the maximum captures between the two
        root->total_captures_so_far = (unsigned short)max_captures; //Updating the root's current captures to the most captures.
        return (unsigned short)max_captures;
    }
}

//A function that creates a new SSMList node
SingleSourceMovesListCell* createNewSSMListNode(unsigned short captures, checkersPos *pos) {
    SingleSourceMovesListCell* new_node;

    checkersPos *pos_cpy = (checkersPos *) malloc(sizeof(checkersPos)); //allocating memory for a copy of the current position
    checkMemAllocation(pos_cpy);

    new_node = (SingleSourceMovesListCell*) malloc(sizeof(SingleSourceMovesListCell));  //allocating memory for the cell.
    checkMemAllocation(new_node);

    memcpy(pos_cpy, pos, sizeof(checkersPos));      //Copying the position, the old one will be freed in the freeSSMTree function.
    new_node->position = pos_cpy;                   //Adding values to list cell.
    new_node->captures = captures;
    new_node->next = NULL;

    return new_node;
}

//A function that adds a node to a empty SSMList
void addToEmptySSMList(SingleSourceMovesList *list, SingleSourceMovesListCell *new_cell) {
    list->head = list->tail = new_cell;
}

//A function that adds a node to the end of the SSMList
void addToEndSSMList(SingleSourceMovesList *list, SingleSourceMovesListCell *new_cell) {
    list->tail->next = new_cell;
    list->tail = new_cell;
}

//A function that creates an empty SSMList
SingleSourceMovesList *allocateEmptySSMList() {
    SingleSourceMovesList *list;
    list = (SingleSourceMovesList *) malloc(sizeof(SingleSourceMovesList));
    checkMemAllocation(list);
    list->head = list->tail = NULL;

    return list;
}


//A function used to update the variables left_captures and right_captures from a given tree node.
void updateLeftAndRightCaptures(SingleSourceMovesTreeNode *curr_tree_node, short *left_captures, short *right_captures){
    if(curr_tree_node->next_move[LEFT]){    //If there is a left subtree, then update left_captures to the left subtree's captures.
        *left_captures = curr_tree_node->next_move[LEFT]->total_captures_so_far;
    }
    else{
        *left_captures = -1;                //Otherwise change it to -1.
    }
    if(curr_tree_node->next_move[RIGHT]){   //If there is a right subtree then update right_captures to the right subtree's captures.
        *right_captures = curr_tree_node->next_move[RIGHT]->total_captures_so_far;
    }
    else{                                   //Otherwise change it to -1.
        *right_captures = -1;
    }
}

/*!
 * Prints the move of a given SingleSourceMovesList.
 * Params: SingleSourceMovesList to print, the current Player, the current Board status.
 */
void printMove(SingleSourceMovesList *move_list, Player player, Board board) {
    if (player == 'T') {                          //Printing the player's name.
        printSubtitle("Player TOP DOWN's turn");
    } else {
        printSubtitle("Player BOTTOM UP's turn");
    }
    if (move_list) {                                             //If there is a move list (there's somewhere to move):
        SingleSourceMovesListCell *curr = move_list->head;

        while (curr->next) {                                    //Going through the move list
            printf("%c%c->", curr->position->row, curr->position->col); //printing the move
            curr = curr->next;
        }
        printf("%c%c\n", curr->position->row, curr->position->col);     //Printing the last move in the list.
    }
    printBoard(board);
}

//A function that frees the SSMList
void freeSSMList(SingleSourceMovesList *ssm_list){
    SingleSourceMovesListCell *curr = ssm_list->head;
    SingleSourceMovesListCell *prev = NULL;

    while(curr){
        prev = curr;
        curr = curr->next;
        free(prev->position);                   //Free the position of the node
        free(prev);                             //Free the previous node
    }
    free(ssm_list);                             //Free the list
}

//A function that returns the maximum between two numbers
int findMax(int a, int b){
    if(a > b)
        return a;
    return b;
}


//A function that checks the memory allocation
void checkMemAllocation(void *allocation){
    if(!allocation){
        fprintf(stderr, MALLOC_ERROR_CODE_MESSAGE);
        exit(MALLOC_ERROR_CODE);
    }
}
