#include "move.h"

void moveTetermino(tetermino_t *tetermino) {
	char i;
	for ( i = 1; i < TETRIS_BOARD_HEIGHT; i++ ) {
		tetermino->data[i - 1] = tetermino->data[i];
	}
	tetermino->data[TETRIS_BOARD_HEIGHT - 1] = 0;
	tetermino->centerPosY--;
}

void moveTeterminoLeft(tetermino_t *tetermino) {
	char i;

	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		tetermino->data[i] <<= 1;
	}
	tetermino->centerPosX++;
}

void moveLeft(long *board, tetermino_t *tetermino) {
	if ( ! isMoveLeftCollision(board, tetermino) ) {
		moveTeterminoLeft(tetermino);
	}
}

void moveTeterminoRight(tetermino_t *tetermino ) {
	char i;

	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		tetermino->data[i] >>= 1;
	}
	tetermino->centerPosX--;
}

void moveRight(long *board, tetermino_t *tetermino) {
	if ( ! isMoveRightCollision(board, tetermino) ) {
		moveTeterminoRight(tetermino);
	}
}
