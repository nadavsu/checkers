#include "multiple_source_moves_list.h"

//A function used to get all the possible best player moves and put them in a list.
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player){
    int i, j;
    MultipleSourceMovesList *msm_list;
    SingleSourceMovesList *ssm_list;
    SingleSourceMovesTree *ssm_tree;
    MultipleSourceMovesListCell *new_msm_node;
    checkersPos *curr_pos;

    msm_list = allocateMSMList();               //Creating a new empty MSM List

    for(i = 0; i < BOARD_SIZE; i++){            //A loop that goes through the whole board, looking for the player sent as the parameter.
        for(j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] == player){                              //Checking if the current position on the board contains that player
                curr_pos = coordToPos(i, j);                        //Creating a new checkersPos using the current coordinates in the 2D array (board)
                ssm_tree = findSingleSourceMoves(board, curr_pos);  //Creating a new SSM Tree for the current player.
                ssm_list = findSingleSourceOptimalMove(ssm_tree);   //Finding the optimal move for the current player from the moves tree.
                new_msm_node = createNewMSMListNode(ssm_list);      //Creating a new MSMList cell from the SSMList created in the line above.
                addToMSMList(msm_list, new_msm_node);               //Adding that cell to the MSMList.

                freeSSMTree(ssm_tree);                              //Freeing the tree.
                }

            }
     }
    return msm_list;
}

//A function used to allocate a new MSM list.
MultipleSourceMovesList *allocateMSMList(){
    MultipleSourceMovesList *list;
    list = (MultipleSourceMovesList *) malloc(sizeof(MultipleSourceMovesList));     //Allocating a new MSMlist.
    checkMemAllocation(list);                                                       //Checking the memory allocation

    list->head = list->tail = NULL;                                                 //Setting the list head and tail to null

    return list;
}

//A function that creates a new MSMList from a given SSMList.
MultipleSourceMovesListCell *createNewMSMListNode(SingleSourceMovesList *ssm_list){
    MultipleSourceMovesListCell *new_cell;
    new_cell = (MultipleSourceMovesListCell *) malloc(sizeof(MultipleSourceMovesListCell)); //Allocating memory for a new node
    checkMemAllocation(new_cell);

    new_cell->next = NULL;
    new_cell->single_source_moves_list = ssm_list;                                          //Pointing to that SSMList.

    return new_cell;
}

//A function which adds a given MSMList cell to an MSM list.
void addToMSMList(MultipleSourceMovesList *list, MultipleSourceMovesListCell *cell){
    if(list->head == NULL){                 //Adding to empty
        addToEmptyMSMList(list, cell);
    } else{                                 //Adding to end.
        addToEndMSMList(list, cell);
    }
}

//A function which adds to an empty MSMList.
void addToEmptyMSMList(MultipleSourceMovesList *list, MultipleSourceMovesListCell *cell){
    list->head = list->tail = cell;
}


//A function which adds to the end of a MSMList.
void addToEndMSMList(MultipleSourceMovesList *list, MultipleSourceMovesListCell *cell){
    list->tail->next = cell;
    list->tail = cell;
}

//A function which frees a MSMList
void freeMSMList(MultipleSourceMovesList *msm_list){
    MultipleSourceMovesListCell *curr = msm_list->head; //Setting current and previous pointers to the cells of the list.
    MultipleSourceMovesListCell *prev = NULL;

    while(curr){            //Going through the list.
        prev = curr;
        curr = curr->next;
        freeSSMList(prev->single_source_moves_list);        //Freeing the list inside the current MSMList cell.
        free(prev);                                         //Freeing the MSMList itself.
    }
    free(msm_list);                                         //Freeing the list itself.
}