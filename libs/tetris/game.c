#include "game.h"


void tetris_createBoard(tetrisboard_t *board) {
	uint8_t i;

	// TODO: may be removed as resetted in loop below
	memset( (void *) board->collision, 0, sizeof(uint16_t) * TETRIS_BOARD_TOTAL_HEIGHT);

	board->collision[0] = 0xFFFF;
	for ( i = 1; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
		board->collision[i] = 0xFFFF - ((1<<(TETRIS_BOARD_WIDTH + 1)) - 1) + 1;
	}
}

void tetris_calculateDisplayBoard(ledboard_t *newBoard, ledboard_t *currentBoard, tetermino_t *tetermino) {
	uint8_t i;
	uint8_t j;

	memcpy(newBoard, currentBoard, sizeof(ledboard_t));

	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		if ( tetermino->data[i] != 0 ) {
			for ( j = 0; j < TETRIS_BOARD_WIDTH + 1; j++ ) {
				if ( tetermino->data[i] & (1<<j) ) {
					LEDBoard.setColor(newBoard, j, i, tetermino->color);
				}
			}
		}
	}
}

void tetris_merge(tetrisboard_t *newBoard, tetrisboard_t *currentBoard, tetermino_t *tetermino) {
	uint8_t i;

	if ( currentBoard != NULL ) {
		memcpy(newBoard, currentBoard, sizeof(tetrisboard_t));
		for ( i = 0 ; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
			newBoard->collision[i] = currentBoard->collision[i] | tetermino->data[i];
		}	
	} else {
		for ( i = 0 ; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
			newBoard->collision[i] = newBoard->collision[i] | tetermino->data[i];
		}	
	}
}

uint8_t tetris_clearLines(tetrisboard_t *board, ledboard_t *ledBoard) {
	uint8_t count = 0;
	uint8_t i;

	for ( i = TETRIS_BOARD_HEIGHT; i > 0; i-- ) {
		if ( board->collision[i] == 0xFFFF ) {
			count++;
			tetris_removeLine(board, i);
			if (ledBoard != NULL ) {
				LEDBoard.removeLine(ledBoard, i);
			}
		}
	} 
	return count;
}

void tetris_removeLine(tetrisboard_t *board, uint8_t pos) {
	uint8_t i;

	for ( i = pos; i < TETRIS_BOARD_HEIGHT - 1; i++ ) {
		board->collision[i] = board->collision[i+1];
	}
	board->collision[TETRIS_BOARD_HEIGHT - 1] = 0xFFFF - ((1<<(TETRIS_BOARD_WIDTH + 1)) - 1) + 1;
}


#ifdef PC_DEBUG
void tetris_displayCollisions(tetrisboard_t *board) {
	uint8_t i;
	uint8_t j;
	uint8_t level;
	
	for ( i = 0; i < 25 - TETRIS_BOARD_HEIGHT; i++ ) {
		printf("\n");
	}

	for ( i = TETRIS_BOARD_HEIGHT; i > 0 ; i-- ) {
		for (  j = TETRIS_BOARD_WIDTH + 2; j > 0 ; j-- ) {
			level = ( board->collision[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			if ( level ) {
				printf("1");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}		
}
#endif