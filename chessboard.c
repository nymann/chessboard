#include <stdio.h>
#include "Definitions.h"

void PrintBoard();
void ReadInput();
void Move(char move[]);

int main()
{
    PrintBoard();
    while(1) {
        ReadInput();
    }

    return 0;
}

void PrintBoard()
{
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            switch (board[i * 10 + j]) {
                case 0:
                    printf(".");
                    break;
                case 1:
                    printf("P");
                    break;

                case 2:
                    printf("R");
                    break;

                case 3:
                    printf("N");
                    break;

                case 4:
                    printf("B");
                    break;

                case 5:
                    printf("Q");
                    break;

                case 6:
                    printf("K");
                    break;
                case 7:
                    printf("p");
                    break;

                case 8:
                    printf("r");
                    break;

                case 9:
                    printf("n");
                    break;

                case 10:
                    printf("b");
                    break;

                case 11:
                    printf("q");
                    break;

                case 12:
                    printf("k");
                    break;
                default:
                    break;
            }
            printf(" ");
        }
        printf("\n");
    }
}

void ReadInput() {
    char move[4];
    scanf("%s", &move);

    // Checking if the input is within the restricted files (a-h) and ranks 1-8.
    if(((move[0] >= 'a' && move[0] <= 'h') && move[1] >= '1' && move[1] <= '8') && ((move[2] >= 'a' && move[2] <= 'h') && move[3] >= '1' && move[3] <= '8')) {
        printf("move from and to should be okay.\n");
    }

    Move(move);
}

void Move(char move[])
{
    for (int i = 0; i < sizeof(move); i++) {
        printf("%c", move[i]);
    }
    printf("\n\n");
    int moveFrom = 100 - (move[1] - '0') * 10 + (move[0] - 96);
    int moveTo = 100 - (move[3] - '0') * 10 + (move[2] - 96);
    if((halfMoves % 2 == 0) && board[moveFrom] >= P && board[moveFrom] <= K && (board[moveTo] == E) || (board[moveTo] <= k && board[moveTo] >= p)){
        printf("White to move, the move from square contains a white piece, and the move to square is either empty or occupied by a black piece.");
    }
    else if((halfMoves % 2 == 1) && board[moveFrom] >= p && board[moveFrom] <= k && (board[moveTo] == E) || (board[moveTo] <= K && board[moveTo] >= P)) {
        printf("Black to move, the move from square contains a black piece, and the move to square is either empty or occupied by a white piece.");
    }

    board[moveTo] = board[moveFrom];
    board[moveFrom] = E;

    halfMoves++;
    PrintBoard();
}