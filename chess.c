//
// Created by Jacob Lin on 11/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SIZE 8

static char *whitePieces[] = {"R", "N", "B", "Q", "K", "B", "N", "R"};
static char *blackPieces[] = {"r", "n", "b", "k", "q", "b", "n", "r"};
static char whitePawn = 'P', blackPawn = 'p', empty = 'x';

enum pieces {EMPTY, PAWN, KING, QUEEN, BISHOP, KNIGHT, ROOK};




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

            // empty piece
            if(current == 'x') {
                reset();
            }
            // white piece
            else if(current < 'a') {
                blue();
            }
            // black piece
            else {
                red();
            }

            if(current == EMPTY) {
                char piece = 'x';

                printf("%c ", piece);
            } else {
                char piece = 'p';

                printf("%c ", piece);
            }

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



int main(void) {
    uint32_t pieceOrder[] = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };
    uint32_t board[SIZE][SIZE] = { { EMPTY } };

    int i;
    for(i = 0; i < SIZE; i++) {
        board[0][i] += PAWN << 16;
    }

    printBoard(&board);

    while(1) {
        char move[10];

        printf("\n");
        printf("It's your move: ");
        scanf("%s", move);
        printf("\n");

        if(strcmp(move, "exit") == 0) {
            break;
        }

        printf("You entered: %s\n", move);
    }

    return 0;
}
