#include "intelligence.h"

void calculateStack(board_t *board) {
	uint8_t stack[TETRIS_BOARD_WIDTH];
	uint8_t i;
	uint8_t j;

	for ( i = 0; i < TETRIS_BOARD_WIDTH; i++ ) {
		stack[i] = 0;
	}

	i = 2;
//	for ( i = TETRIS_BOARD_HEIGHT - HEAD; i > 1 ; i-- ) {
		printf("%d\n", board->collision[i-1]);
		for ( j = TETRIS_BOARD_WIDTH + 1; j > 0 ; j-- ) {
			if ( stack[j] == 0 ) {
				stack[j] = (board->collision[i - 1] & 1<<(j-1)) != 0 ? i : 0;
			}
		}
//	}
	
	printf("\n");
	for ( j = TETRIS_BOARD_WIDTH; j > 0 ; j-- ) {
		printf("%d ", stack[j - 1]);
	}
	printf("\n");
}