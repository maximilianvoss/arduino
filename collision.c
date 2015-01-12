#include "collision.h"

char isRotateRightCollision(long *board, tetermino_t *tetermino) {
	char i;
	tetermino_t teterminoFuture;
	memcpy (&teterminoFuture, tetermino, sizeof(tetermino_t));

	rotateTeterminoRight(&teterminoFuture);

	if ( teterminoFuture.centerPosX == TETRIS_BOARD_WIDTH || teterminoFuture.centerPosX == 0) {
		return 1;
	}
	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {

		if ( teterminoFuture.data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

char isRotateLeftCollision(long *board, tetermino_t *tetermino) {
	char i;
	tetermino_t teterminoFuture;
	memcpy (&teterminoFuture, tetermino, sizeof(tetermino_t));

	rotateTeterminoLeft(&teterminoFuture);

	if ( teterminoFuture.centerPosX == TETRIS_BOARD_WIDTH || teterminoFuture.centerPosX == 0) {
		return 1;
	}

	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {

		if ( teterminoFuture.data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

char isMoveLeftCollision(long *board, tetermino_t *tetermino) {
	char i;
	tetermino_t teterminoFuture;
	memcpy (&teterminoFuture, tetermino, sizeof(tetermino_t));

	moveTeterminoLeft(&teterminoFuture);
	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( teterminoFuture.data[i] >= 1<<(TETRIS_BOARD_WIDTH ) ) {
			return 1;
		}
		if ( teterminoFuture.data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

char isMoveRightCollision(long *board, tetermino_t *tetermino) {
	char i;
	tetermino_t teterminoFuture;
	memcpy (&teterminoFuture, tetermino, sizeof(tetermino_t));

	moveTeterminoRight(&teterminoFuture);
	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( tetermino->data[i] & 1 != 0 ) {
			return 1;
		}
		if ( teterminoFuture.data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

char isCollision(long *board, tetermino_t *tetermino) {
	char i;
	tetermino_t teterminoFuture;
	memcpy (&teterminoFuture, tetermino, sizeof(tetermino_t));

	moveTetermino(&teterminoFuture);
	
	if ( tetermino->data[0] != 0 ) {
		return 1;
	}
	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( teterminoFuture.data[i] & board[i]) {
			return 1;
		}
	}
	return 0;
}

