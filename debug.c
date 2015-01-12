#include "debug.h"

void printBoard(long *board) {
	char i;
	char j;

	for ( i = 0; i < 25 - TETRIS_BOARD_HEIGHT + HEAD; i++ ) {
		printf("\n");
	}

	for ( i = TETRIS_BOARD_HEIGHT - HEAD; i > 0 ; i-- ) {

		for ( j = TETRIS_BOARD_WIDTH + 2; j > 0 ; j-- ) {
			short level = ( board[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			printf("%d ", level);
		}
		printf("\n");
	}
}

int main() {
	long board[TETRIS_BOARD_HEIGHT];
	long boardDisplay[TETRIS_BOARD_HEIGHT];
	char i;
	tetermino_t tetermino;

	createBoard(&board);

	createTetermino(&tetermino, rand() % 7);

	while(1) {
		calculateDisplayBoard(boardDisplay, board, &tetermino);
		printBoard(boardDisplay);
		
		if ( move(board, &tetermino, moveDown) ) {
			memcpy ( board, boardDisplay, sizeof(long) * TETRIS_BOARD_HEIGHT);
			createTetermino(&tetermino, rand() % 7);
		}
		if ( isCollision(board, &tetermino) ) {
			break;
		}


		usleep(250 * 1000);
	} 


	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 0xFFFFFFFF;
		printBoard(board);
		usleep(250 * 1000);
	}
	

	return 0;
}
