#include "rotate.h"

void rotateTeterminoRight(tetermino_t *tetermino) {
	tetermino->pos++;
	if ( tetermino->pos > 3 ) {
		tetermino->pos = 0;
	}
	createTeterminoData(tetermino);
}

void rotateRight(long *board, tetermino_t *tetermino) {
	if ( !isRotateRightCollision(board, tetermino) ) {
		rotateTeterminoRight(tetermino);
	}
}

void rotateTeterminoLeft(tetermino_t *tetermino) {
	if ( tetermino->pos == 0 ) {
		tetermino-> pos = 3; 
	} else {
		tetermino->pos--;
	}
	createTeterminoData(tetermino);
}

void rotateLeft(long *board, tetermino_t *tetermino) {
	if ( !isRotateLeftCollision(board, tetermino) ) {
		rotateTeterminoLeft(tetermino);
	}
}
