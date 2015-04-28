#include "intelligence.h"

void calculateStack(board_t *board, uint8_t *stack) {
	uint8_t i;
	uint8_t j;

	memset(stack, 0, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);

	for ( i = TETRIS_BOARD_HEIGHT + 1; i > 1; i-- ) {
		for ( j = 2; j < TETRIS_BOARD_WIDTH + 2; j++ ) {
			if ( stack[j - 2] == 0 ) {
				stack[j - 2] = (board->collision[i - 1] & 1<<(j-1)) != 0 ? (i - 1) : 0;
			}
		}
	}
}


uint8_t calculateRanking(uint8_t *stack) {
	uint8_t i;
	uint8_t result = 0;
	int8_t diff;

	for ( i = 0; i < TETRIS_BOARD_WIDTH - 2; i++ ) {

		diff = stack[i] - stack[i + 1];
		if ( diff < 0 ) {
			diff *= -1;
		}
		if ( diff > 4 ) {
			diff = 4;
		}

		result += diff;
	}
	return result;
}