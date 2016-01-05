#include <stdio.h>
#include "Definitions.h"

void PrintBoard();

int KnightRules(int moveFrom, int moveTo);

int PawnRules(int moveTo, int moveFrom);

int RookRules(int moveTo, int moveFrom);

int BishopRules(int moveTo, int moveFrom);

void ReadInput();

void ValidMoveMade(int moveFrom, int moveTo);

void Move(char move[]);

int SquareOccupiedByOppositeColorPiece(int moveTo, int color);

int main() {
    PrintBoard();
    ReadInput();

    return 0;
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
    }
    else {
        printf("wrong.");
        //printf("move is not valid, moves should be on the form: 'e2e4'.\nInput was %c%c%c%c", move[0], move[1], move[2], move[3]);
        ReadInput();
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
                if (PawnRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case R:
                if (RookRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case N:
                if (KnightRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case B:
                /*if (BishopRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }*/
                printf("come on.\n");
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
    }

        // Black to move?
    else if (halfMoves % 2 == 1 && board[moveFrom] >= p && board[moveFrom] <= k &&
             (board[moveTo] == E || (board[moveTo] <= K && board[moveTo] >= P))) {
        switch (board[moveFrom]) {
            case p:
                if (PawnRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case r:
                if (RookRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case n:
                if (KnightRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case b:
                if (BishopRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
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
    }
    else {
        // The move from square is either empty or it's not your
        if (halfMoves % 2 == 0) {
            printf("It's whites turn to play and/or %c%c is empty.\n", move[0], move[1]);
        }
        else {
            printf("Invalid move\n");
        }
        ReadInput();
    }
}

int PawnRules(int moveTo, int moveFrom) {
    int validSquares[5] = {F, F, F, F, F};
    // White to move.. (WHITE is equal to 0, check enum in Definitions.h)
    if (halfMoves % 2 == WHITE) {
        // Checking if we can advance the pawn one step.
        if (board[moveFrom - 10] == E) {
            validSquares[0] = moveFrom - 10;
            // We know that we can move the pawn forward one step, let's check if, it's on it's beginning square and if it can move two steps forward.
            if (board[moveFrom - 20] == E && moveFrom / 7) {
                validSquares[1] = moveFrom - 20;
            }
        }
        if (board[moveFrom - 11] != F) {
            validSquares[2] = moveFrom - 11;
        }
        if (board[moveFrom - 9] != F) {
            validSquares[3] = moveFrom - 9;
        }

        //TODO(Implement En Passant)
        //TODO(Implement Promotion)
    }
        // Black to move.
    else {
        if (board[moveFrom + 10] == E) {
            validSquares[0] = moveFrom + 10;
            // We know that we can move the pawn forward one step, let's check if, it's on it's beginning square and if it can move two steps forward.
            if (board[moveFrom + 20] == E && moveFrom / 7) {
                validSquares[1] = moveFrom + 20;
            }
        }
        if (board[moveFrom + 11] != F) {
            validSquares[2] = moveFrom + 11;
        }
        if (board[moveFrom + 9] != F) {
            validSquares[3] = moveFrom + 9;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (moveTo == validSquares[i]) {
            return 1;
        }
    }
    return 0;
}

int KnightRules(int moveTo, int moveFrom) {
    // Since we already checked if the moveTo square is blocked by our own piece, we don't have to consider it here.
    int validSquares[8] = {F, F, F, F, F, F, F, F};
    if (board[moveFrom + 21] != F) {
        validSquares[0] = moveFrom + 21;
    }
    if (board[moveFrom - 21] != F) {
        validSquares[1] = moveFrom - 21;
    }
    if (board[moveFrom + 19] != F) {
        validSquares[2] = moveFrom + 19;
    }
    if (board[moveFrom - 19] != F) {
        validSquares[3] = moveFrom - 19;
    }
    if (board[moveFrom + 12] != F) {
        validSquares[4] = moveFrom + 12;
    }
    if (board[moveFrom - 12] != F) {
        validSquares[5] = moveFrom - 12;
    }
    if (board[moveFrom + 8] != F) {
        validSquares[6] = moveFrom + 8;
    }
    if (board[moveFrom - 8] != F) {
        validSquares[7] = moveFrom - 8;
    }

    for (int i = 0; i < 8; ++i) {
        if (moveTo == validSquares[i]) {
            return 1;
        }
    }
    return 0;
}

int RookRules(int moveTo, int moveFrom) {
    int validSquares[14] = {F, F, F, F, F, F, F, F, F, F, F, F, F, F};
    // Vertical moves negative direction. (fx. from the 1st rank to 8th rank).
    int k = 0;
    int i = 1;
    while (board[moveFrom - (i * 10)] != F) {
        if (board[moveFrom - (i * 10)] == E) {
            validSquares[k] = moveFrom - (i * 10);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - (i * 10), halfMoves % 2) == 1) {
            validSquares[k] = moveFrom - (i * 10);
            k++;
            break;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - (i * 10), halfMoves % 2) == 0) {
            break;
        }
        i++;
    }

    i = 1;
    while (board[moveFrom + (i * 10)] != F) {
        if (board[moveFrom + (i * 10)] == E) {
            validSquares[k] = moveFrom + (i * 10);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + (i * 10), halfMoves % 2) == 1) {
            validSquares[k] = moveFrom + (i * 10);
            k++;
            break;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + (i * 10), halfMoves % 2) == 0) {
            break;
        }
        i++;
    }

    // Horizontal direction positive.
    i = 1;
    while (board[moveFrom + i] != F) {
        if (board[moveFrom + i] == E) {
            validSquares[k] = moveFrom + i;
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + i, halfMoves % 2) == 1) {
            validSquares[k] = moveFrom + i;
            k++;
            break;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + i, halfMoves % 2) == 0) {
            break;
        }
        i++;
    }

    // Horizontal  direction negative
    i = 1;
    while (board[moveFrom - i] != F) {
        if (board[moveFrom - i] == E) {
            validSquares[k] = moveFrom - i;
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - i, halfMoves % 2) == 1) {
            validSquares[k] = moveFrom - i;
            k++;
            break;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - i, halfMoves % 2) == 0) {
            break;
        }
        i++;
    }

    for (int j = 0; j < 14; ++j) {
        if (validSquares[j] == moveTo) {
            return 1;
        }
    }
    return 0;
}

int BishopRules(int moveTo, int moveFrom) {
    printf("1");
    int validMoves[13] = {F, F, F, F, F, F, F, F, F, F, F, F, F,};
    int i = 1;
    int k = 0;

    // Diagonal up right.
    while(board[moveFrom - (i*11)] != F || SquareOccupiedByOppositeColorPiece(moveFrom - (i*11), halfMoves%2) == 0) {
        printf("2");
        if(board[moveFrom - (i*11)] == E) {
            validMoves[k] = moveFrom - (i*11);
        }
        else if(SquareOccupiedByOppositeColorPiece(moveFrom - (i*11), halfMoves%2)){
            validMoves[k] = moveFrom - (i*11);
            break;
        }
        i++;
    }

    // Diagonal down right.
    i=1;
    printf("3");
    while(board[moveFrom + (i*11)] != F || SquareOccupiedByOppositeColorPiece(moveFrom + (i*11), halfMoves%2) == 0) {
        if(board[moveFrom + (i*11)] == E) {
            validMoves[k] = moveFrom + (i*11);
        }
        else if(SquareOccupiedByOppositeColorPiece(moveFrom + (i*11), halfMoves%2)){
            validMoves[k] = moveFrom + (i*11);
            break;
        }
        i++;
    }

    // Diagonal down left.
    i=1;
    while(board[moveFrom + (i*9)] != F || SquareOccupiedByOppositeColorPiece(moveFrom + (i*9), halfMoves%2) == 0) {
        if(board[moveFrom + (i*9)] == E) {
            validMoves[k] = moveFrom + (i*9);
        }
        else if(SquareOccupiedByOppositeColorPiece(moveFrom + (i*9), halfMoves%2)){
            validMoves[k] = moveFrom + (i*9);
            break;
        }
        i++;
    }

    // Diagonal up left.
    i=1;
    while(board[moveFrom - (i*9)] != F || SquareOccupiedByOppositeColorPiece(moveFrom - (i*9), halfMoves%2) == 0) {
        if(board[moveFrom - (i*9)] == E) {
            validMoves[k] = moveFrom - (i*9);
        }
        else if(SquareOccupiedByOppositeColorPiece(moveFrom - (i*9), halfMoves%2)){
            validMoves[k] = moveFrom - (i*9);
            break;
        }
        i++;
    }

    for (int j = 0; j < 13; ++j) {
        if(validMoves[j] == moveTo) {
            return 1;
        }
    }
    return 0;
}

void ValidMoveMade(int moveTo, int moveFrom) {
    board[moveTo] = board[moveFrom];
    board[moveFrom] = E;
    halfMoves++;
    PrintBoard();
    ReadInput();
}

int SquareOccupiedByOppositeColorPiece(int moveTo, int color) {
    if (color == BLACK && board[moveTo] <= K && board[moveTo] >= P) {
        return 1;
    }
    else if (color == WHITE && board[moveTo] <= k && board[moveTo] >= p) {
        return 1;
    }

    return 0;
}