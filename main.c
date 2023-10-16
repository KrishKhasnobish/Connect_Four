#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "connect.h"
#include "cs136-trace.h"

// === THERE IS NO NEED TO MODIFY THE MAIN FUNCTION ===========================

// The program accepts the following commands:
// * INIT
//   Initializes a new game of Connect Four
// * DROP <col:int>
//   Attempts to drop a piece into column <col> for the currently active player

int main(void) {

    const int CMD_INIT = lookup_symbol("INIT");
    const int CMD_DROP = lookup_symbol("DROP");

    struct connect my_game = connect_init();

    int cmd = INVALID_SYMBOL;
    while ((cmd = read_symbol()) != INVALID_SYMBOL) {
        if (cmd == CMD_INIT) {
            my_game = connect_init();
            connect_print(&my_game);
        } else if (cmd == CMD_DROP) {
            int col = INT_MIN;
            assert(scanf("%d", &col) == 1);
            bool piece_placed = connect_drop_piece(&my_game, col);
            if (piece_placed) {
                connect_print(&my_game);
            } else {
                printf("STATUS: Cannot drop piece in column %d.\n", col);
            }
            if (connect_has_finished(&my_game)) {
                char winner = connect_has_won(&my_game);
                if (winner == RED) {
                    printf("STATUS: Congratulations, player RED, for winning the game!\n");
                } else if (winner == YELLOW) {
                    printf("STATUS: Congratulations, player YELLOW, for winning the game!\n");
                } else if (winner == NONE) {
                    printf("STATUS: The game ended with a draw.\n");
                } else {
                    printf("ERROR: Invalid winner.\n");
                }
                exit(0);
            }
        } else {
            printf("ERROR: Unknown command.\n");
            exit(0);
        }
    }
}