#include "display.h"

#ifndef PC_DEBUG

#include <Arduino.h> 

void ledboard_display(ledboard_t *ledboard) {	
	uint8_t red_line;
	uint8_t green_line;
	uint8_t blue_line;
	uint8_t i;
	uint8_t j;

	for ( i = 1; i < LED_BOARD_HEIGHT + 1; i++ ) {
		red_line = 0;
		green_line = 0;
		blue_line = 0;

		for ( j = 0; j < LED_BOARD_WIDTH; j++ ) {
			if ( ledboard->red[i][j] ) {
				red_line |= 1<<j;
			}
			if ( ledboard->green[i][j] ) {
				green_line |= 1<<j;
			}
			if ( ledboard->blue[i][j] ) {
				blue_line |= 1<<j;
			}
		}

		// temporary till all colors are set

		red_line |= green_line | blue_line;

		digitalWrite(LATCHPIN, 0);
		shiftOut(ROW_DATAPIN, ROW_CLOCKPIN, MSBFIRST, red_line);
		shiftOut(COLUMN_DATAPIN, COLUMN_CLOCKPIN, MSBFIRST, ~(1<<(i-1)));
		digitalWrite(LATCHPIN, 1);
	}
}

#else // for debugging on PC

void ledboard_display(ledboard_t *ledboard) {
	uint8_t i;
	uint8_t j;
	uint8_t level;
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	for ( i = 0; i < 25 - LED_BOARD_HEIGHT; i++ ) {
		printf("\n");
	}

	for ( i = LED_BOARD_HEIGHT; i > 0 ; i-- ) {
		for (  j = LED_BOARD_WIDTH; j > 0 ; j-- ) {

			red = ledboard->red[i-1][j-1];
			green = ledboard->green[i-1][j-1];
			blue = ledboard->blue[i-1][j-1];

			level = ( red | green | blue ) ? 1 : 0;
			if ( level ) {
				printf("1"); 
			} else {
				printf(" ");
			}
		}

		#ifdef SHOW_COLORS
			printf("\t");

			for ( j = LED_BOARD_WIDTH; j > 0 ; j-- ) {
				red = ledboard->red[i-1][j-1];
				if ( red ) {
					printf("1"); 
				} else {
					printf(" ");
				}
			}

			printf("\t");

			for ( j = LED_BOARD_WIDTH; j > 0 ; j-- ) {
				green = ledboard->green[i-1][j-1];
				if ( green ) {
					printf("1"); 
				} else {
					printf(" ");
				}
			}

			printf("\t");

			for ( j = LED_BOARD_WIDTH; j > 0 ; j-- ) {
				blue = ledboard->blue[i-1][j-1];
				if ( blue ) {
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