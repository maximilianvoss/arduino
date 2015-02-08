#include "tetris.h"

static uint8_t color[7][3] = COLOR_SETS;

void calculateDisplayBoard(board_t *boardDisplay, board_t *board, tetermino_t* tetermino) {
	uint8_t i;
	uint8_t j;

	memcpy(boardDisplay, board, sizeof(board_t));
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

void setColor(board_t *board, tetermino_t *tetermino, uint8_t x, uint8_t y) {
	board->red[y][x-1] = color[tetermino->color][0];
	board->green[y][x-1] = color[tetermino->color][1];
	board->blue[y][x-1] = color[tetermino->color][2];
}

void createBoard(board_t *board) {
	uint8_t i;
	memset( (void *) board->collision, 0, sizeof(uint16_t) * TETRIS_BOARD_TOTAL_HEIGHT);

	board->collision[0] = 0xFFFF;
	for ( i = 1; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
		board->collision[i] = 0xFFFF - ((1<<(TETRIS_BOARD_WIDTH + 1)) - 1) + 1;
	}
	memset((void *) board->red, 0, sizeof(uint8_t) * TETRIS_BOARD_TOTAL_HEIGHT * TETRIS_BOARD_WIDTH);
	memset((void *) board->green, 0, sizeof(uint8_t) * TETRIS_BOARD_TOTAL_HEIGHT * TETRIS_BOARD_WIDTH);
	memset((void *) board->blue, 0, sizeof(uint8_t) * TETRIS_BOARD_TOTAL_HEIGHT * TETRIS_BOARD_WIDTH);
}

uint8_t clearLines(board_t *board) {
	uint8_t count = 0;
	uint8_t i;

	for ( i = TETRIS_BOARD_HEIGHT; i > 0; i-- ) {
		if ( board->collision[i] == 0xFFFF ) {
			count++;
			removeLine(board, i);
		}
	} 
	return count;
}

void removeLine(board_t *board, uint8_t pos) {
	uint8_t i;
	for ( i = pos; i < TETRIS_BOARD_HEIGHT - 1; i++ ) {
		board->collision[i] = board->collision[i+1];
		memcpy((void *) board->red[i], (void *) board->red[i+1], sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
		memcpy((void *) board->green[i], (void *) board->green[i+1], sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
		memcpy((void *) board->blue[i], (void *) board->blue[i+1], sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
	}
	board->collision[TETRIS_BOARD_TOTAL_HEIGHT - 1] = 0xFFFF - ((1<<TETRIS_BOARD_WIDTH) - 1) + 1;
	memset((void *) board->red[TETRIS_BOARD_TOTAL_HEIGHT - 1], 0, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
	memset((void *) board->green[TETRIS_BOARD_TOTAL_HEIGHT - 1], 0, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
	memset((void *) board->blue[TETRIS_BOARD_TOTAL_HEIGHT - 1], 0, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
}
