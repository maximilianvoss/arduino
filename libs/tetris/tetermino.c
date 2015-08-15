#include "tetermino.h"

uint8_t static teterminoHistory[TETERMINO_CREATION_HISTORY];

void tetris_createTeterminoData(tetermino_t *tetermino) {
	uint16_t *data = tetermino->data;
	memset(data, 0, sizeof(uint16_t) * TETRIS_BOARD_TOTAL_HEIGHT);
	
	uint8_t posX = tetermino->centerPosX;
	uint8_t posY = tetermino->centerPosY;
	if ( tetermino->type == i ) {
		tetermino->color = cyan;

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
		tetermino->color = blue;

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
		tetermino->color = orange;

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
		tetermino->color = magenta;

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
		tetermino->color = yellow;

		data[posY] = 1<<posX | 1<<(posX+1);
		data[posY + 1] = 1<<posX | 1<<(posX+1);
		return;
	}

	if ( tetermino->type == s ) {
		tetermino->color = lime;

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
		tetermino->color = red;

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

uint8_t tetris_calculateRotations(tetermino_t *tetermino) {
	if ( tetermino->type == i ) { 
		return 2;
	}  
	if ( tetermino->type == j ) { 
		return 4;
	}  
	if ( tetermino->type == l ) {
		return 4;
	}  
	if ( tetermino->type == o ) { 
		return 1;
	}  
	if ( tetermino->type == t ) {
		return 4;
	}  
	if ( tetermino->type == s ) { 
		return 2;
	}  
	if ( tetermino->type == z ) { 
		return 2;
	}
	return 0;
}

void tetris_calculateConstraints(tetermino_t *tetermino, uint8_t *start, uint8_t *stop ) {
	if ( tetermino->type == i ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			*start = 1;
			*stop = TETRIS_BOARD_WIDTH;
		} else if ( tetermino->pos == left || tetermino->pos == right ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		}
	} else if ( tetermino->type == j ) {
		if ( tetermino->pos == up ) {
			*start = 1;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == left ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == down ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH;
		} else if ( tetermino->pos == right ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		}
	} else if ( tetermino->type == l ) {
		if ( tetermino->pos == up ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH;
		} else if ( tetermino->pos == left ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == down ) {
			*start = 1;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == right ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		}
	} else if ( tetermino->type == o ) {
		*start = 1;
		*stop = TETRIS_BOARD_WIDTH - 1;
	} else if ( tetermino->type == t ) {
		if ( tetermino->pos == up ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == left ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH;
		} else if ( tetermino->pos == down ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == right ) {
			*start = 1;
			*stop = TETRIS_BOARD_WIDTH - 1;
		}
	} else if ( tetermino->type == s ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == left || tetermino->pos == right ) {
			*start = 1;
			*stop = TETRIS_BOARD_WIDTH - 1;
		}
	} else if ( tetermino->type == z ) {
		if ( tetermino->pos == up || tetermino->pos == down ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH - 1;
		} else if ( tetermino->pos == left || tetermino->pos == right ) {
			*start = 2;
			*stop = TETRIS_BOARD_WIDTH;
		}
	}
}

void tetris_initTeterminoHistory() {
	uint8_t i;
	for ( i = 0; i < TETERMINO_CREATION_HISTORY; i++ ) {
		teterminoHistory[i] = 255;
	}
}

uint8_t tetris_checkTeterminoHistory(uint8_t value) {
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

uint8_t tetris_calculateNewTetermino() {
	uint8_t i;
	uint8_t type;

	type = rand() % 7;
	while ( tetris_checkTeterminoHistory(type)) {
		type = rand() % 7;
	}

	for ( i = 1; i < TETERMINO_CREATION_HISTORY; i++ ) {
		teterminoHistory[i] = teterminoHistory[i - 1];
	}
	teterminoHistory[0] = type;
	return type;
}

void tetris_createTetermino(tetermino_t* tetermino) {
	uint8_t pos = TETRIS_BOARD_WIDTH / 2;
	uint16_t *data = tetermino->data;
	
	memset(data, 0, sizeof(uint16_t) * TETRIS_BOARD_TOTAL_HEIGHT);
	
	tetermino->pos = 0;	
	tetermino->type = tetris_calculateNewTetermino();
	tetermino->centerPosX=pos;

	if ( tetermino->type == i ) {
		tetermino->centerPosY=TETRIS_BOARD_TOTAL_HEIGHT-2;
		tetris_createTeterminoData(tetermino);
		return;
	}  else {
		tetermino->centerPosY=TETRIS_BOARD_TOTAL_HEIGHT-3;
		tetris_createTeterminoData(tetermino);
		return;
	} 
}
