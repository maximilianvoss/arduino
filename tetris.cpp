#include <Arduino.h>
#include <tetris.h>
#include "config.h"

uint16_t volatile board[TETRIS_BOARD_HEIGHT];
uint16_t volatile boardDisplay[TETRIS_BOARD_HEIGHT];
uint8_t volatile gameOver;
tetermino_t tetermino;

ISR(TIMER1_COMPA_vect) {
	if ( ! gameOver ) {
		if ( move(board, &tetermino, moveDown) ) {
			memcpy ( (void *) &board, (void *) &boardDisplay, sizeof(short) * TETRIS_BOARD_HEIGHT);
			createTetermino(&tetermino);
		}
		clearLines(board);
		if ( isCollision(board, &tetermino) ) {
			gameOver = 1;
		} 
	} else {
		board[gameOver] = 0xFFFF;
		gameOver++;
		if ( gameOver > TETRIS_BOARD_HEIGHT - HEAD ) {
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

void printBoard(uint16_t volatile *board) {	
	for ( uint8_t i = 1; i < TETRIS_BOARD_HEIGHT - HEAD; i++ ) {
		uint16_t line = (board[i] & (1<<(TETRIS_BOARD_WIDTH + 1) ) - 1);
		line >>=1;

    	digitalWrite(LATCHPIN, 0);
		shiftOut(ROW_DATAPIN, ROW_CLOCKPIN, MSBFIRST, line);
		shiftOut(COLUMN_DATAPIN, COLUMN_CLOCKPIN, MSBFIRST, ~(1<<(i-1)));
    	digitalWrite(LATCHPIN, 1);
	}
}

void loop() {
	gameOver = 0;
	createBoard(board);
	createTetermino(&tetermino);

	while(! gameOver) {
		calculateDisplayBoard(boardDisplay, board, &tetermino);
		printBoard(boardDisplay);	
	} 

	while (gameOver) {
		printBoard(board);
	}
}

