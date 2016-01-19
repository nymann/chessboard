#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Definitions.h"

void PrintBoard();

void AI();

int RuleCaller(int moveTo, int moveFrom, int switchCase);

int KnightRules(int moveFrom, int moveTo);

int PawnRules(int moveTo, int moveFrom);

int RookRules(int moveTo, int moveFrom);

int BishopRules(int moveTo, int moveFrom);

int DoesKingExist(int moveTo);

int KingRules(int moveTo, int moveFrom);

int QueenRules(int moveTo, int moveFrom);

void Castle(int castle);

void EnPassant(int moveTo, int moveFrom, int color);

void Promotion(int moveTo, int moveFrom, int color);

void ReadInput();

int Check(int moveTo, int moveFrom);

void ValidMoveMade(int moveTo, int moveFrom);

void ToAlgebraicNotation(int moveTo);

void Move(char move[]);

int SquareOccupiedByOwnColorPiece(int moveTo, int color);

void DiscoverCheck(int number, int moveFrom);

int SquareOccupiedByOppositeColorPiece(int moveTo, int color);

void AvailableCommands();

int check = 0;
int playerVsComputer = 0;
int playerColor = 0;
int halfMoves = 0;
int whiteQueensideCastle = 1;
int whiteKingsideCastle = 1;
int blackKingsideCastle = 1;
int blackQueensideCastle = 1;
int enPassantSquare = 0;
int halfMovesSinceEnPassantSquare = 0;
int kingSquares[] = {95, 25};
int board[120] = {
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F,
        F, r, n, b, q, k, b, n, r, F,
        F, p, p, p, p, p, p, p, p, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, P, P, P, P, P, P, P, P, F,
        F, R, N, B, Q, K, B, N, R, F,
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F
};

/*int board[120] = {
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F,
        F, Q, E, E, N, k, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, N, E, E, E, F,
        F, b, E, E, E, Q, E, E, E, F,
        F, E, p, E, p, E, E, b, E, F,
        F, E, E, E, E, E, p, E, E, F,
        F, E, E, p, E, E, E, E, E, F,
        F, E, b, E, E, E, K, b, E, F,
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F
};*/

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    rand();
    if(argc > 1) {
        if(strcmp(argv[1], "1") == 0 && ((strcmp((argv[2]), "W") == 0) || (strcmp((argv[2]), "w") == 0))) {
            printf("1 player starting as white.\n");
            playerVsComputer = 1;
            playerColor = WHITE;
        }
        else if (strcmp(argv[1], "1") == 0 && ((strcmp((argv[2]), "B") == 0) || (strcmp((argv[2]), "b") == 0))) {
            printf("1 player starting as black.\n");
            playerVsComputer = 1;
            playerColor = BLACK;
        }
        else if(strcmp(argv[1], "2") == 0) {
            printf("2 players.\n");
            playerVsComputer = 0;
        }
    } else {
        playerVsComputer = 0;
        printf("No arguments registered.\nYou can start a new game by fx. typing 'chessboard 1 w',\n"
                       "which would start a new game against the computer where you are playing as white.\n"
                       "Since you didn't input any arguments, a multiplayer game has been selected.\n\n");
    }
    PrintBoard();

    if(halfMoves % 2 == playerColor && playerVsComputer == 1) {
        ReadInput();
    }
    else if(playerVsComputer == 1){
        AI();
    }
    else {
        ReadInput();
    }
    return 0;
}

void PrintBoard() {
    printf("    a   b   c   d   e   f   g   h\n");
    for (int i = 2; i < 10; i++) {
        printf("  +---+---+---+---+---+---+---+---+\n");
        printf("%d |", 10 - i);
        for (int j = 0; j < 10; j++) {
            switch (board[(i) * 10 + j]) {
                case E:
                    printf("   |");
                    break;
                case P:
                    printf(" P |");
                    break;

                case R:
                    printf(" R |");
                    break;

                case N:
                    printf(" N |");
                    break;

                case B:
                    printf(" B |");
                    break;

                case Q:
                    printf(" Q |");
                    break;

                case K:
                    printf(" K |");
                    break;
                case p:
                    printf(" p |");
                    break;

                case r:
                    printf(" r |");
                    break;

                case n:
                    printf(" n |");
                    break;

                case b:
                    printf(" b |");
                    break;

                case q:
                    printf(" q |");
                    break;

                case k:
                    printf(" k |");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
    printf("  +---+---+---+---+---+---+---+---+\n\n");
}

void ReadInput() {
    if(halfMoves % 2 != playerColor && playerVsComputer == 1) {
        AI();
    }
    else {
        char move[4];
        scanf("%s", &move);

        // Checking if the input is within the restricted files (a-h) and ranks 1-8.
        if (((move[0] >= 'a' && move[0] <= 'h') && move[1] >= '1' && move[1] <= '8') &&
            ((move[2] >= 'a' && move[2] <= 'h') && move[3] >= '1' && move[3] <= '8')) {
            halfMovesSinceEnPassantSquare++;
            Move(move);
        }
        else {
            // print help (available commands).

            AvailableCommands();
            ReadInput();
        }
    }
}

void Move(char move[]) {
    int moveFrom = 100 - (move[1] - '0') * 10 + (move[0] - 96);
    int moveTo = 100 - (move[3] - '0') * 10 + (move[2] - 96);
    // White to move?
    if (halfMoves % 2 == WHITE && board[moveFrom] >= P && board[moveFrom] <= K &&
        (board[moveTo] == E || (board[moveTo] <= k && board[moveTo] >= p))) {
        if (RuleCaller(moveTo, moveFrom, moveFrom) == 1) {
            ValidMoveMade(moveTo, moveFrom);
        }
        else {
            printf("Invalid move.\n");
            ReadInput();
        }
    }
        // Black to move?
    else if (halfMoves % 2 == BLACK && board[moveFrom] >= p && board[moveFrom] <= k &&
             (board[moveTo] == E || (board[moveTo] <= K && board[moveTo] >= P))) {

        if (RuleCaller(moveTo, moveFrom, moveFrom) == 1) {
            ValidMoveMade(moveTo, moveFrom);
        }
        else {
            printf("Invalid move.\n");
            ReadInput();
        }
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
                if (moveTo == moveFrom - 20) {
                    enPassantSquare = moveFrom - 20 + 10;
                    halfMovesSinceEnPassantSquare = 0;
                }
            }
        }
        if (SquareOccupiedByOppositeColorPiece(moveFrom - 11, WHITE) == 1) {
            validSquares[2] = moveFrom - 11;
        }
        if (SquareOccupiedByOppositeColorPiece(moveFrom - 9, WHITE) == 1) {
            validSquares[3] = moveFrom - 9;
        }

        if ((moveFrom - 11 == enPassantSquare || moveFrom - 9 == enPassantSquare) &&
            halfMovesSinceEnPassantSquare <= 1) {
            EnPassant(moveTo, moveFrom, WHITE);
        }


    }
        // Black to move.
    else {
        if (board[moveFrom + 10] == E) {
            validSquares[0] = moveFrom + 10;
            // We know that we can move the pawn forward one step, let's check if, it's on it's beginning square and if it can move two steps forward.
            if (board[moveFrom + 20] == E && moveFrom / 7) {
                if (moveTo == moveFrom + 20) {
                    enPassantSquare = moveFrom + 20 - 10;
                    halfMovesSinceEnPassantSquare = 0;
                }
                validSquares[1] = moveFrom + 20;
                halfMovesSinceEnPassantSquare = 0;
            }
        }
        if (SquareOccupiedByOppositeColorPiece(moveFrom + 11, BLACK) == 1) {
            validSquares[2] = moveFrom + 11;
        }
        if (SquareOccupiedByOppositeColorPiece(moveFrom + 9, BLACK) == 1) {
            validSquares[3] = moveFrom + 9;
        }

        if ((moveFrom + 11 == enPassantSquare || moveFrom + 9 == enPassantSquare) &&
            halfMovesSinceEnPassantSquare <= 1) {
            EnPassant(moveTo, moveFrom, BLACK);
        }
    }

    if(moveTo == AI_MOVE) {
        int l = 0;
        if(validSquares[0] == F) {
            return NO_MOVES;
        }
        while(1) {
            if(validSquares[l] != F) {
                l++;
            }
            else {
                break;
            }
        }
        return validSquares[(rand() % l)];
    }

    for (int i = 0; i < 4; ++i) {
        if (moveTo == validSquares[i]) {
            // Promotion
            if ((moveTo / 10) == 2 || (moveTo / 10) == 9) {
                Promotion(moveTo, moveFrom, halfMoves % 2);
            }
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

    if(moveTo == AI_MOVE) {
        int l = 0;
        if(validSquares[0] == F) {
            return NO_MOVES;
        }
        while(1) {
            if(validSquares[l] != F) {
                l++;
            }
            else {
                break;
            }
        }
        return validSquares[(rand() % l)];
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
    while (board[moveFrom - (i * 10)] != F && SquareOccupiedByOwnColorPiece(moveFrom - (i * 10), halfMoves%2) == 0 ||
           SquareOccupiedByOppositeColorPiece(moveFrom - (i * 10), halfMoves % 2) != 0) {
        if (board[moveFrom - (i * 10)] == E) {
            validSquares[k] = moveFrom - (i * 10);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - (i * 10), halfMoves % 2) == 1) {
            validSquares[k] = moveFrom - (i * 10);
            k++;
            break;
        }
        i++;
    }

    i = 1;
    while (board[moveFrom + (i * 10)] != F &&  SquareOccupiedByOwnColorPiece(moveFrom + (i * 10), halfMoves%2) == 0||
           SquareOccupiedByOppositeColorPiece(moveFrom + (i * 10), halfMoves % 2) != 0) {
        if (board[moveFrom + (i * 10)] == E) {
            validSquares[k] = moveFrom + (i * 10);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + (i * 10), halfMoves % 2) == 1) {
            validSquares[k] = moveFrom + (i * 10);
            k++;
            break;
        }
        i++;
    }

    // Horizontal direction positive.
    i = 1;
    while (board[moveFrom + i] != F && SquareOccupiedByOwnColorPiece(moveFrom + i, halfMoves%2) == 0|| SquareOccupiedByOppositeColorPiece(moveFrom + i, halfMoves % 2) != 0) {
        if (board[moveFrom + i] == E) {
            validSquares[k] = moveFrom + i;
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + i, halfMoves % 2) == 1) {
            validSquares[k] = moveFrom + i;
            k++;
            break;
        }
        i++;
    }

    // Horizontal  direction negative
    i = 1;
    while (board[moveFrom - i] != F && SquareOccupiedByOwnColorPiece(moveFrom - i, halfMoves%2) == 0|| SquareOccupiedByOppositeColorPiece(moveFrom - i, halfMoves % 2) != 0) {
        if (board[moveFrom - i] == E) {
            validSquares[k] = moveFrom - i;
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - i, halfMoves % 2) == 1) {
            validSquares[k] = moveFrom - i;
            break;
        }
        i++;
    }

    // Check if we should disable a castling opportunity due to rock being moved from it's start squares.
    if (moveFrom == 98) {
        whiteKingsideCastle = 0;
    } else if (moveFrom == 91) {
        whiteQueensideCastle = 0;
    } else if (moveFrom == 28) {
        blackKingsideCastle = 0;
    } else if (moveFrom == 21) {
        blackQueensideCastle = 0;
    }

    if(moveTo == AI_MOVE) {
        int l = 0;
        if(validSquares[0] == F) {
            return NO_MOVES;
        }
        while(1) {

            if(validSquares[l] != F) {
                l++;
            }
            else {
                break;
            }
        }
        return validSquares[(rand() % l)];
    }

    for (int j = 0; j < 14; ++j) {
        if (validSquares[j] == moveTo) {
            return 1;
        }
    }
    return 0;
}

int BishopRules(int moveTo, int moveFrom) {
    int validMoves[13] = {F, F, F, F, F, F, F, F, F, F, F, F, F,};
    int i = 1;
    int k = 0;

    // Diagonal up right.
    while (board[moveFrom - (i * 9)] != F && SquareOccupiedByOwnColorPiece(moveFrom - (i * 9), halfMoves % 2) == 0 ||
           SquareOccupiedByOppositeColorPiece(moveFrom - (i * 9), halfMoves % 2) != 0) {
        if (board[moveFrom - (i * 9)] == E) {
            validMoves[k] = moveFrom - (i * 9);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - (i * 9), halfMoves % 2)) {
            validMoves[k] = moveFrom - (i * 9);
            k++;
            break;
        }
        i++;
    }

    // Diagonal down right.
    i = 1;
    while (board[moveFrom + (i * 11)] != F && SquareOccupiedByOwnColorPiece(moveFrom + (i * 11), halfMoves % 2) == 0 ||
           SquareOccupiedByOppositeColorPiece(moveFrom + (i * 11), halfMoves % 2) != 0) {
        if (board[moveFrom + (i * 11)] == E) {
            validMoves[k] = moveFrom + (i * 11);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + (i * 11), halfMoves % 2)) {
            validMoves[k] = moveFrom + (i * 11);
            k++;
            break;
        }
        i++;
    }

    // Diagonal down left.
    i = 1;
    while (board[moveFrom + (i * 9)] != F && SquareOccupiedByOwnColorPiece(moveFrom + (i * 9), halfMoves % 2) == 0 ||
           SquareOccupiedByOppositeColorPiece(moveFrom + (i * 9), halfMoves % 2) != 0) {
        if (board[moveFrom + (i * 9)] == E) {
            validMoves[k] = moveFrom + (i * 9);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom + (i * 9), halfMoves % 2)) {
            validMoves[k] = moveFrom + (i * 9);
            k++;
            break;
        }
        i++;
    }

    // Diagonal up left.
    i = 1;
    while (board[moveFrom - (i * 11)] != F && SquareOccupiedByOwnColorPiece(moveFrom = (i * 11), halfMoves % 2) == 0 ||
           SquareOccupiedByOppositeColorPiece(moveFrom - (i * 11), halfMoves % 2) != 0) {
        if (board[moveFrom - (i * 11)] == E) {
            validMoves[k] = moveFrom - (i * 11);
            k++;
        }
        else if (SquareOccupiedByOppositeColorPiece(moveFrom - (i * 11), halfMoves % 2)) {
            validMoves[k] = moveFrom - (i * 11);
            break;
        }
        i++;
    }

    if(moveTo == AI_MOVE) {
        int l = 0;
        if(validMoves[0] == F) {
            return NO_MOVES;
        }
        while(1) {
            if(validMoves[l] != F) {
                l++;
            }
            else {
                break;
            }
        }
        return validMoves[(rand() % l)];
    }

    for (int j = 0; j < 13; ++j) {
        if (validMoves[j] == moveTo) {
            return 1;
        }
    }
    return 0;
}

int KingRules(int moveTo, int moveFrom) {
    int validMoves[11] = {F, F, F, F, F, F, F, F, F, F, F};
    int k = 0;
    if (board[moveFrom + 1] == E || SquareOccupiedByOppositeColorPiece(moveFrom + 1, halfMoves % 2)) {
        validMoves[k] = moveFrom + 1;
        k++;
    }
    if (board[moveFrom - 1] == E || SquareOccupiedByOppositeColorPiece(moveFrom - 1, halfMoves % 2)) {
        validMoves[k] = moveFrom - 1;
        k++;
    }
    if (board[moveFrom - 9] == E || SquareOccupiedByOppositeColorPiece(moveFrom - 9, halfMoves % 2)) {
        validMoves[k] = moveFrom - 9;
        k++;
    }
    if (board[moveFrom - 10] == E || SquareOccupiedByOppositeColorPiece(moveFrom - 10, halfMoves % 2)) {
        validMoves[k] = moveFrom - 10;
        k++;
    }
    if (board[moveFrom - 11] == E || SquareOccupiedByOppositeColorPiece(moveFrom - 11, halfMoves % 2)) {
        validMoves[k] = moveFrom - 11;
        k++;
    }
    if (board[moveFrom + 9] == E || SquareOccupiedByOppositeColorPiece(moveFrom + 9, halfMoves % 2)) {
        validMoves[k] = moveFrom + 9;
        k++;
    }
    if (board[moveFrom + 10] == E || SquareOccupiedByOppositeColorPiece(moveFrom + 10, halfMoves % 2)) {
        validMoves[k] = moveFrom + 10;
        k++;
    }
    if (board[moveFrom + 11] == E || SquareOccupiedByOppositeColorPiece(moveFrom + 11, halfMoves % 2)) {
        validMoves[k] = moveFrom + 11;
        k++;
    }
    // Is whites king on it's home scare and can he castle kingside or queenside?
    if (moveFrom == 95 && whiteKingsideCastle == 1 && board[96] == E && board[97] == E && moveTo == 97) {
        Castle(WKC);
    } else if (moveFrom == 25 && blackKingsideCastle == 1 && board[26] == E && board[27] == E && moveTo == 27) {
        Castle(BKC);
    }
    if (moveFrom == 95 && whiteQueensideCastle == 1 && board[94] == E && board[93] == E && board[92] == E &&
        moveTo == 93) {
        Castle(WQC);
    } else if (moveFrom == 25 && blackQueensideCastle == 1 && board[24] == E && board[23] == E && board[22] == E &&
               moveTo == 23) {
        Castle(BQC);
    }

    if(moveTo == AI_MOVE) {
        int l = 0;
        if(validMoves[0] == F) {
            return NO_MOVES;
        }
        while(1) {
            if(validMoves[l] != F) {
                l++;
            }
            else {
                break;
            }
        }
        return validMoves[(rand() % l)];
    }

    for (int i = 0; i < k; ++i) {
        if (validMoves[i] == moveTo) {
            kingSquares[halfMoves % 2] = moveTo;
            return 1;
        }
    }

    return 0;
}

int QueenRules(int moveTo, int moveFrom) {
    return RookRules(moveTo, moveFrom) || BishopRules(moveTo, moveFrom);
}

void ValidMoveMade(int moveTo, int moveFrom) {
    if (DoesKingExist(moveTo) == 1 && moveTo != kingSquares[(halfMoves+1)%2] && kingSquares[(halfMoves+1)%2] != 0) {
        board[moveTo] = board[moveFrom];
        board[moveFrom] = E;
        Check(moveTo, moveFrom);
        halfMoves++;
        PrintBoard();
        ReadInput();
    }
    else {
        printf("Game is over!\n");
        exit(0);
    }
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

int SquareOccupiedByOwnColorPiece(int moveTo, int color) {
    if (color == BLACK && board[moveTo] <= k && board[moveTo] >= p) {
        return 1;
    }
    else if (color == WHITE && board[moveTo] <= K && board[moveTo] >= P) {
        return 1;
    }

    return 0;
}

void Castle(int castle) {
    if (castle == WKC) {
        board[97] = K;
        board[95] = E;
        board[96] = R;
        board[98] = E;
        kingSquares[WHITE] = 97;
    } else if (castle == WQC) {
        board[91] = E;
        board[94] = R;
        board[93] = K;
        board[95] = E;
        kingSquares[WHITE] = 93;
    } else if (castle == BKC) {
        board[25] = E;
        board[28] = E;
        board[26] = r;
        board[27] = k;
        kingSquares[BLACK] = 27;
    } else {
        board[21] = E;
        board[25] = E;
        board[24] = r;
        board[23] = k;
        kingSquares[BLACK] = 23;
    }

    // disable future castling availability
    if (halfMoves % 2 == 0) {
        whiteQueensideCastle = 0;
        whiteKingsideCastle = 0;
    }
    else {
        blackKingsideCastle = 0;
        blackQueensideCastle = 0;
    }

    halfMoves++;
    PrintBoard();
    ReadInput();
}

void EnPassant(int moveTo, int moveFrom, int color) {
    board[moveTo] = board[moveFrom];
    board[moveFrom] = E;
    if (color == WHITE) {
        board[moveTo + 10] = E;
    }
    else {
        board[moveTo - 10] = E;
    }

    halfMoves++;
    PrintBoard();
    ReadInput();
}

void Promotion(int moveTo, int moveFrom, int color) {
    printf("What piece do you want?\n");
    char wantedPiece[4];
    scanf(" %c",
          &wantedPiece); // note the space between " %c, it's vital.. since otherwise it won't wait for user input.
    board[moveFrom] = E;
    wantedPiece[0] = toupper(wantedPiece[0]);
    switch (wantedPiece[0]) {
        case 'Q':
            if (color == WHITE) {
                board[moveTo] = Q;
            } else {
                board[moveTo] = q;
            }
            break;
        case 'R':
            if (color == WHITE) {
                board[moveTo] = R;
            } else {
                board[moveTo] = r;
            }
            break;
        case 'B':
            if (color == WHITE) {
                board[moveTo] = B;
            } else {
                board[moveTo] = b;
            }
            break;
        case 'N':
            if (color == WHITE) {
                board[moveTo] = N;
            } else {
                board[moveTo] = n;
            }
            break;
        default:
            Promotion(moveTo, moveFrom, color);
            break;
    }
    Check(moveTo, moveFrom);
    halfMoves++;
    PrintBoard();
    ReadInput();
}

int DoesKingExist(int moveTo) {
    if (board[kingSquares[WHITE]] == K && board[kingSquares[BLACK]] == k || board[moveTo] == K && board[moveTo] == k) {
        return 1;
    }
    return 0;
}

int Check(int moveTo, int moveFrom) {
    if (RuleCaller(kingSquares[(halfMoves + 1) % 2], moveTo, moveTo) == 1) {
        check = 1;
        printf("Check from ");
        ToAlgebraicNotation(moveTo);
    }
    // Check for discover checks.
    int moveFromRow = moveFrom / 10;
    int kingSquareRow = kingSquares[(halfMoves + 1) % 2] / 10;

    // Vertical.
    if (moveFrom % 10 == kingSquares[(halfMoves + 1) % 2] % 10) {
        DiscoverCheck(10, moveFrom);
    }
        // Horizontal
    else if (moveFromRow == kingSquareRow) {
        DiscoverCheck(1, moveFrom);
    }

    // diagonal
    int diagonalMoveFromDown = moveFrom % 9;
    int diagonalKingSquareDown = (kingSquares[(halfMoves + 1) % 2]) % 9;
    int diagonalMoveFromUp = moveFrom % 11;
    int diagonalKingSquareUp = (kingSquares[(halfMoves + 1) % 2]) % 11;

    if (diagonalMoveFromUp == diagonalKingSquareUp) {
        DiscoverCheck(11, moveFrom);
    }
    else if (diagonalMoveFromDown == diagonalKingSquareDown) {
        DiscoverCheck(9, moveFrom);
    }

    return 0;
}

void ToAlgebraicNotation(int indexSquare) {
    char algebraic[2];
    int row = indexSquare / 10;
    algebraic[0] = (char) (indexSquare % 10 + 96);
    algebraic[1] = (char) (10 - row + 48);
    printf("%c%c.\n", algebraic[0], algebraic[1]);
}

int RuleCaller(int moveTo, int moveFrom, int switchCase) {
    if(moveTo < 21) {
        return NO_MOVES;
    }
    switch (board[switchCase]) {
        case P:
            return PawnRules(moveTo, moveFrom);
        case N:
            return KnightRules(moveTo, moveFrom);
        case R:
            return RookRules(moveTo, moveFrom);
        case B:
            return BishopRules(moveTo, moveFrom);
        case Q:
            return QueenRules(moveTo, moveFrom);
        case K:
            return KingRules(moveTo, moveFrom);
        case p:
            return PawnRules(moveTo, moveFrom);
        case n:
            return KnightRules(moveTo, moveFrom);
        case r:
            return RookRules(moveTo, moveFrom);
        case b:
            return BishopRules(moveTo, moveFrom);
        case q:
            return QueenRules(moveTo, moveFrom);
        case k:
            return KingRules(moveTo, moveFrom);
        default:
            return 0;
    }
}

void DiscoverCheck(int number, int moveFrom) {
    if (moveFrom > kingSquares[(halfMoves + 1) % 2]) {
        int i = number;
        while (board[moveFrom + i] == E) {
            i += number;
        }
        if ((RuleCaller(kingSquares[(halfMoves + 1) % 2], (moveFrom + i), (moveFrom + i)) == 1 &&
             SquareOccupiedByOppositeColorPiece(moveFrom + i, (halfMoves + 1) % 2) == 1)) {
            printf("Check from ");
            ToAlgebraicNotation(moveFrom + i);
        }
    }
    else {
        int j = number;
        while (board[moveFrom - j] == E) {
            j += number;
        }
        if ((RuleCaller(kingSquares[(halfMoves + 1) % 2], (moveFrom - j), (moveFrom - j)) == 1 &&
             SquareOccupiedByOppositeColorPiece(moveFrom - j, (halfMoves + 1) % 2) == 1)) {
            printf("Check from ");
            ToAlgebraicNotation(moveFrom - j);
        }
    }
}

void AvailableCommands() {
    printf("Moves should be entered by their algebraic 'coordinates', like this"
                   " g1f3.\n");
}

void AI() {
    if (check == 1) {
        printf("we are in check.\n");
    }
    else {

        int randomPiece;
        chooseNewPiece:
        randomPiece = (rand() % 6);
        if(playerColor == WHITE) {
            // random number between enum p and enum k. (7-12).
            randomPiece += 7;
            //printf("We want to move the black piece %d.\n", randomPiece);
        }
        else {
            randomPiece += 1;
            //printf("We want to move the white piece %d.\n", randomPiece);
        }

        // Find the number of pieces of the chosen random type on the board, and then select a random one of them.
        int randomPieceFoundOnSquare[] = {0, 0, 0, 0, 0, 0, 0, 0};
        int k = 0;
        for (int i = 21; i < 98; ++i) {
            if(board[i] == randomPiece) {
                //printf("random piece is found on square %d.\n", i);
                randomPieceFoundOnSquare[k] = i;
                k++;
            }
        }

        int moveFrom = randomPieceFoundOnSquare[rand() % k];
        int moveTo = RuleCaller(AI_MOVE, moveFrom, moveFrom);
        if(moveTo == NO_MOVES) {
            //printf("No moves is available for %d, choosing a new piece.\n", randomPiece);
            goto chooseNewPiece;
        }
        //printf("We can move from square %d to square %d.\n", moveFrom, moveTo);
        ValidMoveMade(moveTo, moveFrom);
    }
    halfMoves++;
    ReadInput();
}