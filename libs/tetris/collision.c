#include "collision.h"

uint8_t isCollision(uint16_t volatile *board, tetermino_t *teterminoFuture) {
	uint8_t i;
	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( teterminoFuture->data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}
