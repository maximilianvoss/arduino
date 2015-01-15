#include "move.h"


char move(uint16_t volatile *board, tetermino_t *tetermino, enum moveDirectionEnum direction) {
	uint8_t i;
	tetermino_t teterminoFuture;
	memcpy(&teterminoFuture, tetermino, sizeof(tetermino_t));

	if ( direction == moveDown ) {
		for ( i = 1; i < TETRIS_BOARD_HEIGHT; i++ ) {
			teterminoFuture.data[i - 1] = teterminoFuture.data[i];
		}
		teterminoFuture.data[TETRIS_BOARD_HEIGHT - 1] = 0;
		teterminoFuture.centerPosY--;
	} else if ( direction == moveLeft ) {
		for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
			teterminoFuture.data[i] <<= 1;
		}
		teterminoFuture.centerPosX++;
	} else if ( direction == moveRight ) {
		for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
			teterminoFuture.data[i] >>= 1;
		}
		teterminoFuture.centerPosX--;
	} else if ( direction == rotateLeft ) {
		if ( teterminoFuture.pos == 0 ) {
			teterminoFuture.pos = 3; 
		} else {
			teterminoFuture.pos--;
		}
		createTeterminoData(&teterminoFuture);
	} else if ( direction == rotateRight ) {
		teterminoFuture.pos++;
		if ( teterminoFuture.pos > 3 ) {
			teterminoFuture.pos = 0;
		}
		createTeterminoData(&teterminoFuture);
	} else if ( direction == moveDrop ) {
		// TODO: implement the drop
	}

	if ( ! isCollision(board, &teterminoFuture) )	{
		memcpy (tetermino, &teterminoFuture, sizeof(tetermino_t));
	} else if ( direction == moveDown ) {
		return 1;
	}
	return 0;
}

