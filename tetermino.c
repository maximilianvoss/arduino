#include "tetermino.h"

void createTeterminoData(tetermino_t *tetermino) {
	long *data = tetermino->data;
	memset(data, 0, sizeof(long) * TETRIS_BOARD_HEIGHT);
	
	char posX = tetermino->centerPosX;
	if ( tetermino->type == i ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			data[tetermino->centerPosY+1] = 1<<posX;
			data[tetermino->centerPosY] = 1<<posX;
			data[tetermino->centerPosY-1] = 1<<posX;
			data[tetermino->centerPosY-2] = 1<<posX;
			return;
		}
		if ( tetermino->pos == right || tetermino->pos == left ) {
			data[tetermino->centerPosY] = 1<<(posX+1) | 1<<posX |1<<(posX-1) | 1<<(posX-2);
			return;
		}
	}

	if ( tetermino->type == t ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			data[tetermino->centerPosY] = 1<<posX | 1<<(posX+1) | 1<<(posX-1);
			if ( tetermino->pos == up ) {
				data[tetermino->centerPosY - 1] = 1<<posX;
			} else {
				data[tetermino->centerPosY + 1] = 1<<posX;
			}
			return;
		}
		if ( tetermino->pos == right || tetermino->pos == left ) {
			data[tetermino->centerPosY - 1] = 1<<posX;
			data[tetermino->centerPosY] = 1<<posX;
			data[tetermino->centerPosY + 1] = 1<<posX;
			if ( tetermino->pos == right ) {
				data[tetermino->centerPosY] = 1<<(posX+1) | 1<<posX;
			} else {
				data[tetermino->centerPosY] = 1<<(posX-1) | 1<<posX;
			}
			return;
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
	} 
	if ( type == j ) {
		data[TETRIS_BOARD_HEIGHT-2] = 1<<pos;
		data[TETRIS_BOARD_HEIGHT-3] = 1<<pos;
		data[TETRIS_BOARD_HEIGHT-4] = 1<<pos | 1<<(pos+1);
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		return;
	} 
	if ( type == l ) {
		data[TETRIS_BOARD_HEIGHT-2] = 1<<pos;
		data[TETRIS_BOARD_HEIGHT-3] = 1<<pos;
		data[TETRIS_BOARD_HEIGHT-4] = 1<<pos | 1<<(pos-1);
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		return;
	} 
	if ( type == o ) {
		data[TETRIS_BOARD_HEIGHT-3] = 1<<pos | 1<<(pos+1);
		data[TETRIS_BOARD_HEIGHT-4] = 1<<pos | 1<<(pos+1);
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		return;
	} 
	if ( type == t ) {
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		createTeterminoData(tetermino);
		return;
	} 
	if ( type == s ) {
		data[TETRIS_BOARD_HEIGHT-3] = 1<<pos | 1<<(pos-1);
		data[TETRIS_BOARD_HEIGHT-4] = 1<<pos | 1<<(pos+1);
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		return;
	} 
	if ( type == z ) {
		data[TETRIS_BOARD_HEIGHT-3] = 1<<pos | 1<<(pos+1);
		data[TETRIS_BOARD_HEIGHT-4] = 1<<pos | 1<<(pos-1);
		tetermino->centerPosY=TETRIS_BOARD_HEIGHT-3;
		return;
	} 
}
