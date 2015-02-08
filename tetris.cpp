#include <Arduino.h>
#include <tetris.h>
#include "config.h"

board_t board;
board_t boardDisplay;
uint8_t volatile gameOver;
tetermino_t tetermino;

ISR(TIMER1_COMPA_vect) {
	if ( ! gameOver ) {
		if ( move(&board, &tetermino, moveDown) ) {
			memcpy(&board, &boardDisplay, sizeof(board_t));
			createTetermino(&tetermino);
		}
		clearLines(&board);
		if ( isCollision(&board, &tetermino) ) {
			gameOver = 1;
		} 
	} else {
		memset((void *) board.red[gameOver], 0xFF, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
		memset((void *) board.green[gameOver], 0xFF, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);
		memset((void *) board.blue[gameOver], 0xFF, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);

		gameOver++;
		if ( gameOver > TETRIS_BOARD_HEIGHT + 1 ) {
			gameOver = 0;
		}
	}
}

void setup() {
	Serial.begin(SERIAL_BAUDRATE);
 	pinMode(LATCHPIN, OUTPUT);
	pinMode(COLUMN_CLOCKPIN, OUTPUT);
	pinMode(COLUMN_DATAPIN, OUTPUT);
	pinMode(ROW_CLOCKPIN, OUTPUT);
	pinMode(ROW_DATAPIN, OUTPUT);

	randomSeed(analogRead(0));

	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 15624;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	sei();

	initTeterminoHistory();
}

void printBoard(board_t *board) {	
	uint8_t red_line;
	uint8_t green_line;
	uint8_t blue_line;

	for ( uint8_t i = 1; i < TETRIS_BOARD_HEIGHT + 1; i++ ) {
		red_line = 0;
		green_line = 0;
		blue_line = 0;

		for ( uint8_t j = 0; j < TETRIS_BOARD_WIDTH; j++ ) {
			if ( board->red[i][j] ) {
				red_line |= 1<<j;
			}
			if ( board->green[i][j] ) {
				green_line |= 1<<j;
			}
			if ( board->blue[i][j] ) {
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

void loop() {
	gameOver = 0;
	createBoard(&board);
	createTetermino(&tetermino);

	while(! gameOver) {
		calculateDisplayBoard(&boardDisplay, &board, &tetermino);
		printBoard(&boardDisplay);	
	} 

	while (gameOver) {
		printBoard(&board);
	}
}

