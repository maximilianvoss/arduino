#include "tetris.h"

int latchPinColumn = 8;
int clockPinColumn = 12;
int dataPinColumn = 11;
int latchPinRow = 3;
int clockPinRow = 7;
int dataPinRow = 6;
 
void setup()
{
  Serial.begin(9600);
  pinMode(latchPinColumn, OUTPUT);
  pinMode(clockPinColumn, OUTPUT);
  pinMode(dataPinColumn, OUTPUT);
  pinMode(latchPinRow, OUTPUT);
  pinMode(clockPinRow, OUTPUT);
  pinMode(dataPinRow, OUTPUT);
}

void printBoard(uint16_t *board) {
	uint8_t i;
	uint8_t j;
	uint16_t line;

	for ( i = 0; i < 25 - TETRIS_BOARD_HEIGHT + HEAD; i++ ) {
		Serial.print("\n");
	}

	for ( i = TETRIS_BOARD_HEIGHT - HEAD; i > 1 ; i-- ) {

		line = (board[1] & (1<<(TETRIS_BOARD_WIDTH + 1) - 1)) - 1;

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

		for ( j = TETRIS_BOARD_WIDTH + 1; j > 0 ; j-- ) {
			short level = ( board[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			Serial.print("%d ", level);
		}
		Serial.print("\n");

		delay(50);
	}
}

void loop() {
	uint16_t board[TETRIS_BOARD_HEIGHT];
	uint16_t boardDisplay[TETRIS_BOARD_HEIGHT];
	uint8_t i;
	uint8_t inputChar;
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


	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 0xFFFF;
		printBoard(board);
		delay(250);
	} 
}
