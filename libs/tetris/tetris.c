#include "tetris.h"

void calculateDisplayBoard(ledboard_t *boardDisplay, ledboard_t *board, tetermino_t* tetermino) {
	uint8_t i;
	uint8_t j;

	memcpy(boardDisplay, board, sizeof(ledboard_t));
	for ( i = 0 ; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
		boardDisplay->collision[i] = board->collision[i] | tetermino->data[i];	
		if ( tetermino->data[i] ) {
			for ( j = 0; j < TETRIS_BOARD_WIDTH + 1; j++ ) {
				if ( tetermino->data[i] & (1<<j) ) {
					setColor(boardDisplay, tetermino, j, i);
				}
			}
		}
	}
}

void setColor(ledboard_t *board, tetermino_t *tetermino, uint8_t x, uint8_t y) {
	ledboard_setColor(board, x, y, tetermino->color);
}

uint8_t clearLines(ledboard_t *board) {
	uint8_t count = 0;
	uint8_t i;

	for ( i = TETRIS_BOARD_HEIGHT; i > 0; i-- ) {
		if ( board->collision[i] == 0xFFFF ) {
			count++;
			ledboard_removeLine(board, i);
		}
	} 
	return count;
}

