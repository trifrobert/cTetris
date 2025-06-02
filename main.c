#include <stdio.h>
#include <conio.h>   // Windows-only header
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

//------------------------CONTROLS-----------------------//
// UP Arrow - Rotate
// DOWN Arrow - Partially Drop the Item
// RIGHT Arrow - Move Right
// LEFT Arrow - Move Left
// SPACE - Drop Entirely
//------------------------------------------------------//

//------------------------TETRIMINO-----------------------//
//     1      110      111      10         11
// I - 1  Z - 011  T - 010  L - 11  cube - 11
//        
//     
//--------------------------------------------------------//

typedef struct{
    int rows;
    int columns;
    const int *data;
}Tetrimino;

#define ROWS 15
#define COLUMNS 15

#define RANDOM(min, max) ((rand() % ((max) - (min) + 1)) + (min))

const int I_SHAPE[] = {1, 1};
const int Z_SHAPE[] = {1, 1, 0, 0, 1, 1};
const int T_SHAPE[] = {1, 1, 1, 0, 1, 0};
const int L_SHAPE[] = {1, 0, 1, 1};
const int CUBE[] = {1, 1, 1, 1};

int environment[ROWS][COLUMNS];
unsigned char game_running_flag = 1;
unsigned char special_char_flag = 0;
unsigned char isTetriminoActive = 0;

int current_row;
int current_column;

Tetrimino tetrimino;
Tetrimino tetriminos[] = {
    {2, 1, I_SHAPE},
    {2, 3, Z_SHAPE},
    {2, 3, T_SHAPE},
    {2, 2, L_SHAPE},
    {2, 2, CUBE}
};

// Windows version of readInput
int readInput() {
    if (_kbhit()) {
        return _getch();  // No echo, no ENTER
    }
    return 0;
}

void printBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", environment[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Tetrimino createTetrimino(){
    return tetriminos[RANDOM(0,4)];
}

int canMove(Tetrimino tetrimino, int row, int column){

    if((tetrimino.rows + row) > ROWS || (tetrimino.columns + column) > COLUMNS
            || (row < 0) || (column < 0)){
        return 0;
    }
    
    for(int i=0; i< tetrimino.rows ; i++){
        for(int j=0 ; j<tetrimino.columns; j++){
            if((*(tetrimino.data + i * tetrimino.columns + j)) == 1){
                if(environment[row+i][column+j] == 1){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void insertTetrimino(Tetrimino tetrimino, int row, int column){

    for(int i = 0 ; i < tetrimino.rows ; i++){
        for(int j = 0 ; j < tetrimino.columns ; j++){
            int value = *(tetrimino.data + i * tetrimino.columns + j);
            environment[row+i][column+j] = value;
        }
    }
}

void handleInput(){
    int input = readInput();

    if(!isTetriminoActive){
        tetrimino = createTetrimino();
        current_row = 0;
        current_column = COLUMNS / 2 - tetrimino.columns / 2;
        isTetriminoActive = 1;
    }

    if (input == 'q') {
        //exit game
        game_running_flag = 0;
        return;
    }
    if(input == 32){
        //space key
    }

    if(input == 224){
        special_char_flag = 1;
        return;
    }
    if(special_char_flag){
        int new_row = current_row;
        int new_column = current_column;

        switch (input) {
            case 75: new_column--; break; // LEFT
            case 77: new_column++; break; // RIGHT
            case 80: new_row++; break;    // DOWN
            case 72: /* ROTATE */ break;
        }

        if (canMove(tetrimino, new_row, new_column)) {
            current_row = new_row;
            current_column = new_column;
        }

        special_char_flag = 0;
    }
    insertTetrimino(tetrimino, current_row, current_column);
}

int main() {
    srand(time(NULL));
    while (game_running_flag) {
        system("cls");
        handleInput();
        printBoard();
        memset(environment, 0, sizeof(environment));
        Sleep(300); // milliseconds
    }

    return 0;
}
