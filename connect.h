#include <stdbool.h>

#ifndef _CONNECT
#define _CONNECT
struct connect {
    char current_player; // the currently active player (either RED or YELLOW)
    char board[42];      // the board of size 6 x 7 (rows x columns, either RED, YELLOW, or NONE)
};
#endif // _CONNECT

// NONE represents none of the two players
extern const char NONE;

// RED represents the red player
extern const char RED;

// YELLOW represents the yellow player
extern const char YELLOW;

// connect_init() returns a new Connect Four game with an empty board and RED
//   as the currently active player.
struct connect connect_init();

// connect_drop_piece(cf, col) attempts to drop a piece in column col for the
//   currently active player. The function changes the active player and
//   returns true if the drop was successful; otherwise it does not change
//   the active player and returns false.
// effects: might mutate *cf
// requires: col must be a valid column
bool connect_drop_piece(struct connect *cf, int col);

// connect_has_finished(cf) returns true if the Connect Four game *cf has
//   finished, and false otherwise.
bool connect_has_finished(const struct connect *cf);

// connect_has_won(cf) returns which player has won the game. Possible values
//   are RED if the red player has won the game, YELLOW if the yellow player
//   has won the game, or NONE if neither of the players has won the game.
char connect_has_won(const struct connect *cf);

// connect_print(cf) prints the current board of the Connect Four game *cf.
// effects: write to output
void connect_print(struct connect *cf);