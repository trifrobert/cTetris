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
// I - 1  Z - 011  T - 010  L - 10  cube - 11
//     1                        11         
//     1
//--------------------------------------------------------//


#define ROWS 15
#define COLUMNS 15

typedef struct{
    int rows;
    int columns;
    const int *data;
}Tetrimino;


const int I_SHAPE[] = {1, 1, 1, 1};
const int Z_SHAPE[] = {1, 1, 0, 0, 1, 1};
const int T_SHAPE[] = {1, 1, 1, 0, 1, 0};
const int L_SHAPE[] = {1, 0, 1, 0, 1, 1};
const int CUBE[] = {1, 1, 1, 1};

int environment[ROWS][COLUMNS];
unsigned char game_running_flag = 1;
unsigned char special_char_flag = 0;

Tetrimino tetriminos[] = {
    {4, 1, I_SHAPE},
    {2, 3, Z_SHAPE},
    {2, 3, T_SHAPE},
    {3, 2, L_SHAPE},
    {2, 2, CUBE}
};

int returnRandom(int min, int max){
    int rd_num = rand() % (max - min + 1) + min;
    return rd_num;
}

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
    return tetriminos[returnRandom(0,4)];
}

void insertTetrimino(Tetrimino tetrimino, int insertion_row, int insertion_column){

    for(int i = 0 ; i < tetrimino.rows ; i++){
        for(int j = 0 ; j < tetrimino.columns ; j++){
            int value = *(tetrimino.data + i * tetrimino.columns + j);
            environment[insertion_row+i][insertion_column+j] = value;
        }
    }
}

void handleInput(){
    int input = readInput();
    printf("Input: %d\n", input);

    if (input == 'q') {
        //exit game
        game_running_flag = 0;
    }
    else if(input == 32){
        //space key
    }

    if(input == 224){
        special_char_flag = 1;
    }
    else if(special_char_flag == 1){
        if(input == 77){
            //right key
        }
        else if(input == 75){
            //left key
        }
        else if(input ==  72){
            //up key
        }
        else if(input == 80){
            //down key
        }
        special_char_flag = 0;
    }
    Tetrimino new_tetrimino = createTetrimino();
    insertTetrimino(new_tetrimino, 0, 6);
}

int main() {
    srand(time(NULL));
    while (game_running_flag) {
        system("cls");
        handleInput();
        printBoard();
        memset(environment, 0, sizeof(environment));    //clean the environment
        Sleep(500); // milliseconds
    }

    return 0;
}
