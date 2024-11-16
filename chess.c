//
// Created by Jacob Lin on 11/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SIZE 8
#define WHITE 0
#define BLACK 1

static char *whitePieces[] = {"x", "P", "K", "Q", "B", "N", "R"};
static char *blackPieces[] = {"x", "p", "k", "q", "b", "n", "r"};

enum Piece {EMPTY, PAWN, KING, QUEEN, BISHOP, KNIGHT, ROOK};

void red(void) {
    printf("\033[0;31m");
}

void blue(void) {
    printf("\033[0;34m");
}

void reset(void) {
    printf("\033[0m");
}

void printBoard(uint32_t (*board)[SIZE][SIZE]) {
    int i, j;
    char starter = 'a';

    // print header
    printf("  ");
    for(i = 0; i < SIZE; i++) {
        printf("%c ", starter + i);
    }
    printf(" \n");

    // print main board
    for(i = 0; i < SIZE; i++) {
        // left side numbers
        printf("%d ", SIZE - i);
        for(j = 0; j < SIZE; j++) {
            uint32_t current = (*board)[i][j];

            uint32_t color = (current & (1 << 3)) >> 3;
            uint32_t piece = current & (7);

            char boardPiece = 'x';

            // empty piece
            if(piece == EMPTY) {
                reset();
            }
            // white piece
            else if(color == WHITE) {
                blue();
                boardPiece = *(whitePieces[piece]);
            }
            // black piece
            else {
                red();
                boardPiece = *(blackPieces[piece]);
            }

            printf("%c ", boardPiece);

            // reset color
            reset();
        }

        // right side numbers
        printf("%d\n", SIZE - i);
    }

    // print footer
    printf("  ");
    for(i = 0; i < SIZE; i++) {
        printf("%c ", starter + i);
    }
    printf(" \n");

    reset();
}

uint32_t getPiece(uint32_t (*board)[SIZE][SIZE], int row, int col) {
    if(row < 0 || col < 0 || row >= SIZE || col >= SIZE) {
        return -1;
    }

    uint32_t selected = (*board)[row][col];

    return (selected & 7);

}

// -1 for empty. 0 is white and 1 is black (#define)
uint32_t getColor(uint32_t (*board)[SIZE][SIZE], int row, int col) {
    if(row < 0 || col < 0 || row >= SIZE || col >= SIZE) {
        return -1;
    }

    uint32_t selected = (*board)[row][col];

    if(getPiece(board, row, col) != EMPTY) {
        return (selected & (1 << 3)) >> 3;
    }

    return -1;
}

// return 0 for invalid move. 1 for valid move.
int makeMove(uint32_t (*board)[SIZE][SIZE], const char move[10]) {
    char pieceChar = move[0];
    enum Piece current;

    size_t len = strlen(move);

    // extract piece
    if(pieceChar >= 'a' && pieceChar <= 'h') {
        current = PAWN;
    } else if(pieceChar == 'K') {
        current = KING;
    } else if(pieceChar == 'Q') {
        current = QUEEN;
    } else if(pieceChar == 'B') {
        current = BISHOP;
    } else if(pieceChar == 'N') {
        current = KNIGHT;
    } else if(pieceChar == 'R') {
        current = ROOK;
    } else {
        current = EMPTY;
    }

    // extract row/col of extraction



    printf("You are trying to move a: %d\n", current);



    return 0;
}




int main(void) {
    uint32_t whitePieceOrder[] = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };
    uint32_t blackPieceOrder[] = { ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK };
    uint32_t board[SIZE][SIZE] = { { EMPTY } };

    int colorPos = 3;

    int i;
    for(i = 0; i < SIZE; i++) {
        board[0][i] = board[0][i] | (1 << colorPos) + blackPieceOrder[i];
        board[1][i] = board[1][i] | (1 << colorPos) + PAWN;
        board[2][i] += EMPTY;
        board[3][i] += EMPTY;
        board[4][i] += EMPTY;
        board[5][i] += EMPTY;
        board[6][i] = (board[6][i] & ~(1 << colorPos)) + PAWN;
        board[7][i] = (board[7][i] & ~(1 << colorPos)) + whitePieceOrder[i];
    }

    printBoard(&board);

    while(1) {
        char move[10];

        printf("\n");
        printf("It's your move: ");
        scanf("%s", move);
        printf("\n");

        makeMove(&board, move);

        if(strcmp(move, "exit") == 0) {
            break;
        }

        printf("You entered: %s\n", move);
    }

    return 0;
}
