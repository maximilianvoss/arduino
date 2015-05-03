#include "debug.h"

#ifdef PC_DEBUG

void printBoard(board_t *board) {
	for ( uint8_t i = 0; i < 25 - DISPLAY_HEIGHT; i++ ) {
		printf("\n");
	}

	for ( uint8_t i = DISPLAY_HEIGHT; i > 0 ; i-- ) {
		for ( uint8_t j = TETRIS_BOARD_WIDTH + 2; j > 0 ; j-- ) {
			uint8_t level = ( board->collision[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			if ( level ) {
				printf("1"); 
			} else {
				printf(" ");
			}
		}

		#ifdef SHOW_COLORS
			printf("\t");

			for ( uint8_t j = TETRIS_BOARD_WIDTH; j > 0 ; j-- ) {
				uint8_t level = board->red[i-1][j-1];
				if ( level ) {
					printf("1"); 
				} else {
					printf(" ");
				}
			}

			printf("\t");

			for ( uint8_t j = TETRIS_BOARD_WIDTH; j > 0 ; j-- ) {
				uint8_t level = board->green[i-1][j-1];
				if ( level ) {
					printf("1"); 
				} else {
					printf(" ");
				}
			}

			printf("\t");

			for ( uint8_t j = TETRIS_BOARD_WIDTH; j > 0 ; j-- ) {
				uint8_t level = board->blue[i-1][j-1];
				if ( level ) {
					printf("1"); 
				} else {
					printf(" ");
				}
			}
		#endif

		printf("\n");
	}
}

#endif