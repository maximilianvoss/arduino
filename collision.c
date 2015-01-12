#include "collision.h"

char isCollision(long *board, tetermino_t *teterminoFuture) {
	char i;
	
	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( teterminoFuture->data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

