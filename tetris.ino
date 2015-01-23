#include "tetris.h"

int latchPinColumn = 8;
int clockPinColumn = 12;
int dataPinColumn = 11;
int latchPinRow = 3;
int clockPinRow = 7;
int dataPinRow = 6;
 
void setup()
{
	Serial.begin(115200);
 	pinMode(latchPinColumn, OUTPUT);
	pinMode(clockPinColumn, OUTPUT);
	pinMode(dataPinColumn, OUTPUT);
	pinMode(latchPinRow, OUTPUT);
	pinMode(clockPinRow, OUTPUT);
	pinMode(dataPinRow, OUTPUT);
}

void printBoard(uint16_t *board) {

	for ( uint8_t i = 0; i < 25 - TETRIS_BOARD_HEIGHT + HEAD; i++ ) {
		Serial.print("\n");
	}

	for ( uint8_t i = TETRIS_BOARD_HEIGHT - HEAD; i > 1 ; i-- ) {

		uint16_t line = (board[i] & (1<<(TETRIS_BOARD_WIDTH)) - 2);
		line >>=1;

    	digitalWrite(latchPinRow, 0);
		//move 'em out
		shiftOut(dataPinRow, clockPinRow,MSBFIRST, line);
		//return the latch pin high to signal chip that it
		//no longer needs to listen for information
    	digitalWrite(latchPinRow, 1);

    	digitalWrite(latchPinColumn, 0);
		//move 'em out
		shiftOut(dataPinColumn, clockPinColumn, MSBFIRST, ~(1<<i));
		//return the latch pin high to signal chip that it
		//no longer needs to listen for information
    	digitalWrite(latchPinColumn, 1);

		for ( uint8_t j = TETRIS_BOARD_WIDTH + 1; j > 0 ; j-- ) {
			short level = ( board[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			Serial.print(level);
		}
		Serial.print("\n");

		delay(50);
	}
}

void loop() {
	uint16_t board[TETRIS_BOARD_HEIGHT];
	uint16_t boardDisplay[TETRIS_BOARD_HEIGHT];
	tetermino_t tetermino;

	createBoard(board);
	createTetermino(&tetermino, static_cast<teterminoEnum>(rand() % 7));

	while(1) {
		calculateDisplayBoard(boardDisplay, board, &tetermino);
		printBoard(boardDisplay);
		
		if ( move(board, &tetermino, moveDown) ) {
			memcpy ( board, boardDisplay, sizeof(short) * TETRIS_BOARD_HEIGHT);
			createTetermino(&tetermino, static_cast<teterminoEnum>(rand() % 7));
		}
		clearLines(board);
		if ( isCollision(board, &tetermino) ) {
			break;
		}
		delay(250);
	} 


	for ( uint8_t i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 0xFFFF;
		printBoard(board);
		delay(250);
	} 
}
