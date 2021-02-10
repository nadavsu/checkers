#include "save_load.h"

//A function that saves the current state of the board in a binary file with name filename.
void storeBoard(Board board, char *file_name) {
    FILE *file;
    unsigned char buffer;
    int j, i;

    file = fopen(file_name, "wb");                      //Opening the file.
    checkFile(file);

    for (i = 0; i < BOARD_SIZE; i++) {                  //Going through the rows of the board.
        for (j = 0; j < BOARD_SIZE; j += 4) {           //Going through 4 columns of the board each time.
            buffer = encodeCells(board[i] + j);         //Creating a buffer from the 4 cells in the row starting from board[i] + j
            fwrite(&buffer, sizeof(char), 1, file);     //Writing the buffer to the file
        }
    }

    fclose(file);                                       //Closing the file.
}


//A function that takes 4 board cells as a parameter and encodes the 4 cells into a single byte.
unsigned char encodeCells(const unsigned char *cell_arr) {
    int i;
    unsigned char byte, buffer;
    buffer = 0;
    Player curr_player;

    for (i = 0; i < BOARD_SIZE / 2; i++) {              //Going through the four cells.
        curr_player = cell_arr[i];                      //Setting the current player to the current player in the board.
        if (curr_player == TOP_DOWN_PLAYER) {                       //Determining the code by using the current player in the 3 ifs ahead.
            byte = TOP_DOWN_PLAYER_CODE;
        } else if (curr_player == BOTTOM_UP_PLAYER) {
            byte = BOTTOM_UP_PLAYER_CODE;
        } else {                                        //If it's not T or not B then it must be an empty cell.
            byte = EMPTY_CELL_CODE;
        }
        buffer |= byte;                                 //Adding the byte to the buffer.
        if (i < 3) {                                    //Shifting the byte 2 to the left only 3 times to not lose the
            buffer <<= 2;                               //data at the fourth iteration of the loop.
        }
    }
    return buffer;
}

//A function that loads a board from a binary save file with name file_name
void loadBoard(Board board, char *file_name) {
    FILE *file;
    unsigned char curr_byte;
    int i, j;

    file = fopen(file_name, "rb");                      //Opening the file to read.
    checkFile(file);

    for (i = 0; i < BOARD_SIZE; i++) {                  //Going through the rows of the board
        for (j = 0; j < BOARD_SIZE; j += 4) {           //Going through 4 cells of the board at once, in total 16 iterations, just like the file length
            fread(&curr_byte, sizeof(char), 1, file);   //Reading 1 byte from the file, which we will decode.
            decodeCells(board[i] + j, curr_byte);       //Decoding the byte, and putting it in the board.
        }
    }
    fclose(file);
}

//A function that takes a byte, decodes it and writes it into the board.
void decodeCells(unsigned char *board, unsigned char byte) {
    int i;
    unsigned char mask, code;
    mask = TWO_LSB_MASK;                                //Setting the mask to TWO LSBs.
    Player player;

    for (i = (BOARD_SIZE / 2) - 1; i >= 0; i--) {       //Going through the cells from the right to left.
        code = mask & byte;                             //Saving the two LSBs of the current byte.
        if (code == TOP_DOWN_PLAYER_CODE) {                           //Checking if the code is T, B, or ' '.
            player = TOP_DOWN_PLAYER;                               //and saving player accordingly.
        } else if (code == BOTTOM_UP_PLAYER_CODE) {
            player = BOTTOM_UP_PLAYER;
        } else {
            player = EMPTY_CELL;
        }
        board[i] = player;                              //Writing the player to the board[i] cell.
        byte >>= 2;                                     //Shifting the given byte by two to the right so we can decode the next 2 bits.
    }
}

//A function used to check if a file opens.
void checkFile(FILE *file){
    if(!file){
        fprintf(stderr, "Error opening file!");
        exit(FILE_ERROR_CODE);
    }
}