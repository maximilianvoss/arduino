#include "tetermino.h"

uint8_t static teterminoHistory[TETERMINO_CREATION_HISTORY];

void createTeterminoData(tetermino_t *tetermino) {
	uint16_t *data = tetermino->data;
	memset(data, 0, sizeof(uint16_t) * TETRIS_BOARD_TOTAL_HEIGHT);
	
	uint8_t posX = tetermino->centerPosX;
	uint8_t posY = tetermino->centerPosY;
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
		return;
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
		return;
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
		return;
	}
}

void initTeterminoHistory() {
	uint8_t i;
	for ( i = 0; i < TETERMINO_CREATION_HISTORY; i++ ) {
		teterminoHistory[i] = 255;
	}
}

uint8_t checkTeterminoHistory(uint8_t value) {
	uint8_t i;
	uint8_t count = 0;
	for ( i = 0; i < TETERMINO_CREATION_HISTORY; i++ ) {
		if ( teterminoHistory[i] == value ) {
			count++;
			if ( count > TETERMINO_CREATION_THERSHOLD ) {
				return 1;
			}
		}
	}
	return 0;
}

uint8_t calculateNewTetermino() {
	uint8_t i;
	uint8_t type;
	type = rand() % 7;
	while ( checkTeterminoHistory(type)) {
		type = rand() % 7;
	}

	for ( i = 1; i < TETERMINO_CREATION_HISTORY; i++ ) {
		teterminoHistory[i] = teterminoHistory[i - 1];
	}
	teterminoHistory[0] = type;
	return type;
}

void createTetermino(tetermino_t* tetermino) {
	uint8_t pos = TETRIS_BOARD_WIDTH / 2;
	uint16_t *data = tetermino->data;
	
	memset(data, 0, sizeof(uint16_t) * TETRIS_BOARD_TOTAL_HEIGHT);
	
	tetermino->pos = 0;	
	tetermino->type = calculateNewTetermino();
	tetermino->centerPosX=pos;

	if ( tetermino->type == i ) {
		tetermino->centerPosY=TETRIS_BOARD_TOTAL_HEIGHT-2;
		createTeterminoData(tetermino);
		return;
	}  else {
		tetermino->centerPosY=TETRIS_BOARD_TOTAL_HEIGHT-3;
		createTeterminoData(tetermino);
		return;
	} 
}
