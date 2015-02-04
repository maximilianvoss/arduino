#include "tetris.h"

void calculateDisplayBoard(uint16_t volatile *boardDisplay, uint16_t volatile *board, tetermino_t* tetermino) {
	uint8_t i;

	memcpy((void *) boardDisplay, (void *) board, sizeof(uint16_t) * TETRIS_BOARD_HEIGHT);
	for ( i = 0 ; i < TETRIS_BOARD_HEIGHT; i++ ) {
		boardDisplay[i] = board[i] | tetermino->data[i];	
	}
}

void createBoard(uint16_t volatile *board) {
	uint8_t i;
	memset( (void *) board, 0, sizeof(uint16_t) * TETRIS_BOARD_HEIGHT);

	board[0] = 0xFFFF;
	for ( i = 1; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 0xFFFF - ((1<<(TETRIS_BOARD_WIDTH + 1)) - 1) + 1;
	}
}

uint8_t clearLines(uint16_t volatile *board) {
	uint8_t count = 0;
	uint8_t i;

	for ( i = TETRIS_BOARD_HEIGHT - HEAD; i > 0; i-- ) {
		if ( board[i] == 0xFFFF ) {
			count++;
			removeLine(board, i);
		}
	} 
	return count;
}

void removeLine(uint16_t volatile *board, uint8_t pos) {
	uint8_t i;
	for ( i = pos; i < TETRIS_BOARD_HEIGHT - HEAD - 1; i++ ) {
		board[i] = board[i+1];
	}
	board[TETRIS_BOARD_HEIGHT - 1] = 0xFFFF - ((1<<TETRIS_BOARD_WIDTH) - 1) + 1;
}