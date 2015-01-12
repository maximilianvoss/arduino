#include "collision.h"

uint8_t isCollision(uint16_t *board, tetermino_t *teterminoFuture) {
	for ( uint8_t i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( teterminoFuture->data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

