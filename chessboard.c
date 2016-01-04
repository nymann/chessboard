#include <stdio.h>
#include "Definitions.h"

void PrintBoard();

void ReadInput();

void Move(char move[]);

int main() {
    PrintBoard();
    while (1) {
        ReadInput();
    }

    //return 0; redundant when we have an endless while loop.
}

void PrintBoard() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            switch (board[i * 10 + j]) {
                case 0:
                    printf(". ");
                    break;
                case 1:
                    printf("P ");
                    break;

                case 2:
                    printf("R ");
                    break;

                case 3:
                    printf("N ");
                    break;

                case 4:
                    printf("B ");
                    break;

                case 5:
                    printf("Q ");
                    break;

                case 6:
                    printf("K ");
                    break;
                case 7:
                    printf("p ");
                    break;

                case 8:
                    printf("r ");
                    break;

                case 9:
                    printf("n ");
                    break;

                case 10:
                    printf("b ");
                    break;

                case 11:
                    printf("q ");
                    break;

                case 12:
                    printf("k ");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}

void ReadInput() {
    char move[4];
    scanf("%s", &move);

    // Checking if the input is within the restricted files (a-h) and ranks 1-8.
    if (((move[0] >= 'a' && move[0] <= 'h') && move[1] >= '1' && move[1] <= '8') &&
        ((move[2] >= 'a' && move[2] <= 'h') && move[3] >= '1' && move[3] <= '8')) {
        Move(move);
    } else {
        printf("move is not valid, moves should be on the form: 'e2e4'.\n");
    }
}

void Move(char move[]) {
    int moveFrom = 100 - (move[1] - '0') * 10 + (move[0] - 96);
    int moveTo = 100 - (move[3] - '0') * 10 + (move[2] - 96);

    // White to move?
    if (halfMoves % 2 == 0 && board[moveFrom] >= P && board[moveFrom] <= K &&
        (board[moveTo] == E || (board[moveTo] <= k && board[moveTo] >= p))) {
        switch (board[moveFrom]) {
            case P:
                printf("white pawn.\n");
                break;
            case R:
                printf("white rook.\n");
                break;
            case N:
                printf("white knight.\n");
                break;
            case B:
                printf("white bishop.\n");
                break;
            case Q:
                printf("white queen.\n");
                break;
            case K:
                printf("white king.\n");
                break;

            default:
                printf("try again.\n");
                ReadInput();
                break;
        }
        board[moveTo] = board[moveFrom];
        board[moveFrom] = E;
        halfMoves++;
        PrintBoard();
    }

        // Black to move?
    else if (halfMoves % 2 == 1 && board[moveFrom] >= p && board[moveFrom] <= k &&
             (board[moveTo] == E || (board[moveTo] <= K && board[moveTo] >= P))) {
        switch (board[moveFrom]) {
            case p:
                printf("black pawn.\n");
                break;
            case r:
                printf("black rook.\n");
                break;
            case n:
                printf("black knight.\n");
                break;
            case b:
                printf("black bishop.\n");
                break;
            case q:
                printf("black queen.\n");
                break;
            case k:
                printf("black king.\n");
                break;
            default:
                printf("try again.\n");
                ReadInput();
                break;
        }
        board[moveTo] = board[moveFrom];
        board[moveFrom] = E;
        halfMoves++;
        PrintBoard();
    }
    else {
        // The move from square is either empty or it's not your
        if (halfMoves % 2 == 0) {
            printf("It's whites turn to play and/or %c%c is empty.\n", move[0], move[1]);
        }
        else {
            printf("It's blacks turn to play and/or %c%c is empty.\n", move[0], move[1]);
        }
        ReadInput();
    }
}