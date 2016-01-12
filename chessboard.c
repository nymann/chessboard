#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Definitions.h"

void PrintBoard();

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

int Check(int lastMoveTo);

void ValidMoveMade(int moveFrom, int moveTo);

void ToAlgebraicNotation(int lastMoveTo);

void Move(char move[]);

int SquareOccupiedByOppositeColorPiece(int moveTo, int color);

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

int main() {

    PrintBoard();
    ReadInput();
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

        printf("Invalid move.\n");
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
                if (BishopRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case Q:
                if (QueenRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case K:
                if (KingRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
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
                if (QueenRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
                break;
            case k:
                if (KingRules(moveTo, moveFrom) == 1) {
                    ValidMoveMade(moveTo, moveFrom);
                }
                else {
                    printf("Invalid move.\n");
                    ReadInput();
                }
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

        //TODO(Implement Promotion)
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

    for (int i = 0; i < 4; ++i) {
        if (moveTo == validSquares[i]) {
            // Promotion
            if (moveTo / 10 == 2 || moveTo / 10 == 9) {
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
    while (board[moveFrom - (i * 10)] != F ||
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
    while (board[moveFrom + (i * 10)] != F ||
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
    while (board[moveFrom + i] != F || SquareOccupiedByOppositeColorPiece(moveFrom + i, halfMoves % 2) != 0) {
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
    while (board[moveFrom - i] != F || SquareOccupiedByOppositeColorPiece(moveFrom - i, halfMoves % 2) != 0) {
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
    while (board[moveFrom - (i * 9)] != F ||
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
    while (board[moveFrom + (i * 11)] != F ||
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
    while (board[moveFrom + (i * 9)] != F ||
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
    while (board[moveFrom - (i * 11)] != F ||
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


    for (int i = 0; i < k; ++i) {
        if (validMoves[i] == moveTo) {
            kingSquares[halfMoves % 2] = moveTo;
            printf("king square. %d\n", kingSquares[halfMoves % 2]);
            return 1;
        }
    }

    //TODO(Implement castling).

    return 0;
}

int QueenRules(int moveTo, int moveFrom) {
    return RookRules(moveTo, moveFrom) || BishopRules(moveTo, moveFrom);
}

void ValidMoveMade(int moveTo, int moveFrom) {
    if (DoesKingExist(moveTo) == 1) {
        board[moveTo] = board[moveFrom];
        board[moveFrom] = E;
        Check(moveTo);
        halfMoves++;
        PrintBoard();
        ReadInput();
    }
    else {
        printf("Game is over!\n");
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

void Castle(int castle) {
    if (castle == WKC) {
        board[97] = K;
        board[95] = E;
        board[96] = R;
        board[98] = E;
        kingSquares[0] = 97;
    } else if (castle == WQC) {
        board[91] = E;
        board[94] = R;
        board[93] = K;
        board[95] = E;
        kingSquares[0] = 93;
    } else if (castle == BKC) {
        board[25] = E;
        board[28] = E;
        board[26] = r;
        board[27] = k;
        kingSquares[1] = 27;
    } else {
        board[21] = E;
        board[25] = E;
        board[24] = r;
        board[23] = k;
        kingSquares[1] = 23;
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

    halfMoves++;
    PrintBoard();
    ReadInput();
}

int DoesKingExist(int moveTo) {
    if (board[kingSquares[WHITE]] == K || board[kingSquares[BLACK]] == k || board[moveTo] == K || board[moveTo] == k) {
        return 1;
    }
    return 0;
}

int Check(int lastMoveTo) {
    switch (board[lastMoveTo]) {
        case P:
            if (PawnRules(kingSquares[BLACK], lastMoveTo) == 1) {
                printf("Check by the white pawn on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case R:
            if (RookRules(kingSquares[BLACK], lastMoveTo) == 1) {
                printf("Check by the white rook on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case N:
            if (KnightRules(kingSquares[BLACK], lastMoveTo) == 1) {
                printf("Check by the white knight on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case B:
            if (BishopRules(kingSquares[BLACK], lastMoveTo) == 1) {
                printf("Check by the white bishop on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case Q:
            if (QueenRules(kingSquares[BLACK], lastMoveTo) == 1) {
                printf("Check by the white queen on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;

        case p:
            if (PawnRules(kingSquares[WHITE], lastMoveTo) == 1) {
                printf("Check by the black pawn on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case r:
            if (RookRules(kingSquares[WHITE], lastMoveTo) == 1) {
                printf("Check by the black rook on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case n:
            if (KnightRules(kingSquares[WHITE], lastMoveTo) == 1) {
                printf("Check by the black knight on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case b:
            if (BishopRules(kingSquares[WHITE], lastMoveTo) == 1) {
                printf("Check by the black bishop on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;
        case q:
            if (QueenRules(kingSquares[WHITE], lastMoveTo) == 1) {
                printf("Check by the black queen on ");
                ToAlgebraicNotation(lastMoveTo);
                return 1;
            }
            break;

        default:
            break;
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