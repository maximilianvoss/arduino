#include "tetris.h"

void calculateDisplayBoard(long *boardDisplay, long *board, tetermino_t* tetermino) {
	char i;	
	memcpy(boardDisplay, board, sizeof(long) * TETRIS_BOARD_HEIGHT);
	for ( i = 0 ; i < TETRIS_BOARD_HEIGHT; i++ ) {
		boardDisplay[i] = board[i] | tetermino->data[i];	
	}
}

void createBoard(long *board) {
	int i;
	memset(board, 0, sizeof(long) * TETRIS_BOARD_HEIGHT);

	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 1 | 1<<TETRIS_BOARD_WIDTH + 1;
	}
	board[0] = 0xFFFFFFFF;
}
