/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: none

// 
//
// Name: Krish Khasnobish
// login ID: kkhasnob
//////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include "connect.h"
#include "cs136-trace.h"

const char NONE = '_';
const char RED = 'R';
const char YELLOW = 'Y';

// The number of pieces that have to be in a straight line (horizontal of
//   vertical) in order to win the game.
 static const int WINLENGTH = 4;

// The width / number of columns of the Connect Four board.
static const int WIDTH = 7;

// The height / number of rows of the Connect Four board.
static const int HEIGHT = 6;

// find_index(c, r) returns the index of an array represented by column c
//   and row r.
// requires: c must be between 0 (inclusive) and WIDTH (exclusive)
//           r must be between 0 (inclusive) and HEIGHT (exclusive)
int find_index(int c, int r) {
    assert(c >= 0 && c < WIDTH);
    assert(r >= 0 && r < HEIGHT);
    return (c + (r * 7));
}

// player_swap(cf) changes the current active player
// effects: mutates *cf
void player_swap(struct connect *cf) {
    assert(cf);
    if (cf->current_player == RED) {
        cf->current_player = YELLOW;
    } else if (cf->current_player == YELLOW) {
        cf->current_player = RED;
    }
}

// get_char(board, c, r) returns the player who's piece is in column c and
//   row r.
// requires: c must be between 0 (inclusive) and WIDTH (exclusive)
//           r must be between 0 (inclusive) and HEIGHT (exclusive)
static char get_char(char *board, int c, int r) {
    assert(board);
    assert(c >= 0 && c < WIDTH);
    assert(r >= 0 && r < HEIGHT);
    return *(board + find_index(c, r));
}

// See connect.h for documentation.
struct connect connect_init() {
    struct connect my_game;
    
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        my_game.board[i] = NONE;
    }

    my_game.current_player = RED;
    return my_game;
}

// See connect.h for documentation.
bool connect_drop_piece(struct connect *cf, int col) {
    assert(cf);
    assert(col >= 0 && col < WIDTH);
    bool result = false;
    int i = find_index(col, 0);
    if (cf->board[i] != NONE) {
        result = false;
    } else {
        int row = 5;
        while (row >= 0) {
            i = find_index(col, row);
            if (cf->board[i] == NONE) {
                cf->board[i] = cf->current_player;
                player_swap(cf); 
                result = true;
                break;
            } else {
                row--;
            }
        }
    }
    return result;
}

// win_horizontal(cf, player) produces true if player has 4 
//   consecutive horizontal slots
// effects: none
bool win_horizontal(const struct connect *cf, char player) {
    assert(cf);
    bool result = false;
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < WINLENGTH; c++) {
            if ((cf->board[find_index(c, r)] == player) && 
                (cf->board[find_index(c+1, r)] == player) && 
                (cf->board[find_index(c+2, r)] == player) && 
                (cf->board[find_index(c+3, r)] == player)) {
                    result = true;
                    break;
                } 
        }
    }
    return result;
}

// win_vertical(cf, player) produces true if player has 4 
//   consecutive vertical slots
// effects: none
bool win_vertical(const struct connect *cf, char player) {
    assert(cf);
    bool result = false;
    for (int c = 0; c < 7; c++) {
        for (int r = 0; r < 3; r++) {
            if ((cf->board[find_index(c, r)] == player) && 
                (cf->board[find_index(c, r+1)] == player) && 
                (cf->board[find_index(c, r+2)] == player) && 
                (cf->board[find_index(c, r+3)] == player)) {
                    result = true;
                    break;
                } 
        }
    }
    return result;
}

// win_diagonal(cf, player) produces true if player has 4 
//   consecutive diagonal slots
// effects: none
bool win_diagonal(const struct connect *cf, char player) {
    assert(cf);
    bool result = false;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < WINLENGTH; c++) {
            if ((cf->board[find_index(c, r)] == player) && 
                (cf->board[find_index(c+1, r+1)] == player) && 
                (cf->board[find_index(c+2, r+2)] == player) && 
                (cf->board[find_index(c+3, r+3)] == player)) {
                    result = true;
                    break;
                }
            if ((cf->board[find_index(c, r+3)] == player) && 
                (cf->board[find_index(c+1, r+2)] == player) && 
                (cf->board[find_index(c+2, r+1)] == player) && 
                (cf->board[find_index(c+3, r)] == player)) {
                    result = true;
                    break;
                }  
        }
    }
    return result;
}

// See connect.h for documentation.
char connect_has_won(const struct connect *cf) {
    assert(cf);
    if (win_horizontal(cf, RED) || 
        win_vertical(cf, RED) || 
        win_diagonal(cf, RED)) {
        return RED;
    } else if (win_horizontal(cf, YELLOW) || 
            win_vertical(cf, YELLOW) || 
            win_diagonal(cf, YELLOW)) {
        return YELLOW;
    } else {
        return NONE;
    }
}

// See connect.h for documentation.
bool connect_has_finished(const struct connect *cf) {
    assert(cf);
    if (connect_has_won(cf) != NONE) {
        return true;
    } else {
        int count = 0;
        for (int i = 0; i < 42; i++) {
            if (cf->board[i] != NONE) {
                count++;
            }
        }
        if (count == 42) {
            return true;
        } else {
            return false;
        }
    }
}

// See connect.h for documentation.
void connect_print(struct connect *cf) {
    assert(cf);
    for (int r = 0; r < HEIGHT; ++r) {
        printf("|");
        for (int c = 0; c < WIDTH; ++c) {
            printf(" %c |", get_char(cf->board, c, r));
        }
        printf("\n");
    }
    printf("%c", cf->current_player);
    for (int w = 0; w < 4 * WIDTH - 1; ++w) {
        printf("-");
    }
    printf("%c\n\n", cf->current_player);
}