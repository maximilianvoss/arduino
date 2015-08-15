#include "collision.h"

uint8_t isCollision(ledboard_t *board, tetermino_t *teterminoFuture) {
	uint8_t i;
	for ( i = 0; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
		if ( teterminoFuture->data[i] & board->collision[i]) {
			return 1;
		}
	}
	return 0;
}

