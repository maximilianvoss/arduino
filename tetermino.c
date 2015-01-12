#include "tetermino.h"

void createTeterminoData(tetermino_t *tetermino) {
	long *data = tetermino->data;
	memset(data, 0, sizeof(long) * TETRIS_BOARD_HEIGHT);
	
	char posX = tetermino->centerPosX;
	char posY = tetermino->centerPosY;
	if ( tetermino->type == i ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			data[posY + 1] = 1<<posX;
			data[posY] = 1<<posX;
			data[posY - 1] = 1<<posX;
			data[posY - 2] = 1<<posX;
		} else {
			data[posY] = 1<<(posX+1) | 1<<posX |1<<(posX-1) | 1<<(posX-2);
		}
		return;
	}

	if ( tetermino->type == j ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			data[posY] = 1<<posX;
			if ( tetermino->pos == up ) {
				data[posY + 1] = 1<<posX;
				data[posY - 1] = 1<<posX | 1<<(posX+1);
			} else {
				data[posY - 1] = 1<<posX;
				data[posY + 1] = 1<<posX | 1<<(posX-1);
			}
		} else {
			data[posY] = 1<<posX | 1<<(posX-1) | 1<<(posX+1);
			if ( tetermino->pos == right ) {
				data[posY - 1] = 1<<(posX - 1);
			} else {
				data[posY + 1] = 1<<(posX + 1);
			}
		}
		return;
	}

	if ( tetermino->type == l ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			data[posY] = 1<<posX;
			if ( tetermino->pos == up ) {
				data[posY + 1] = 1<<posX;
				data[posY - 1] = 1<<posX | 1<<(posX-1);
			} else {
				data[posY - 1] = 1<<posX;
				data[posY + 1] = 1<<posX | 1<<(posX+1);
			}
		} else {
			data[posY] = 1<<posX | 1<<(posX-1) | 1<<(posX+1);
			if ( tetermino->pos == left ) {
				data[posY - 1] = 1<<(posX + 1);
			} else {
				data[posY + 1] = 1<<(posX - 1);
			}
		}
		return;
	}

	if ( tetermino->type == t ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			data[posY] = 1<<posX | 1<<(posX+1) | 1<<(posX-1);
			if ( tetermino->pos == down ) {
				data[posY - 1] = 1<<posX;
			} else {
				data[posY + 1] = 1<<posX;
			}
		} else  {
			data[posY - 1] = 1<<posX;
			data[posY + 1] = 1<<posX;
			if ( tetermino->pos == right ) {
				data[posY] = 1<<(posX+1) | 1<<posX;
			} else {
				data[posY] = 1<<(posX-1) | 1<<posX;
			}
		}
		return;
	}

	if ( tetermino->type == o ) {
		data[posY] = 1<<posX | 1<<(posX+1);
		data[posY + 1] = 1<<posX | 1<<(posX+1);
	}

	if ( tetermino->type == s ) {
		if ( tetermino->pos == up || tetermino->pos == down) {
			data[posY] = 1<<posX | 1<<(posX+1);
			data[posY + 1] = 1<<posX | 1<<(posX-1);
		} else {
			data[posY - 1] = 1<<(posX);
			data[posY] = 1<<posX | 1<<(posX+1);
			data[posY + 1] = 1<<(posX+1);
		}
	}

	if ( tetermino->type == z ) {
		if ( tetermino->pos == up || tetermino->pos == down) {
			data[posY] = 1<<posX | 1<<(posX-1);
			data[posY + 1] = 1<<posX | 1<<(posX+1);
		} else {
			data[posY - 1] = 1<<(posX);
			data[posY] = 1<<posX | 1<<(posX-1);
			data[posY + 1] = 1<<(posX-1);
		}
	}
}

void createTetermino(tetermino_t* tetermino, enum teterminoEnum type) {
	char pos = TETRIS_BOARD_WIDTH / 2;
	long *data = tetermino->data;
	
	memset(data, 0, sizeof(long) * TETRIS_BOARD_HEIGHT);
	
	tetermino->pos = 0;	
	tetermino->type = type;
	tetermino->centerPosX=pos;

	if ( type == i ) {
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-2;
		createTeterminoData(tetermino);
		return;
	}  else {
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		createTeterminoData(tetermino);
		return;
	} 
}
