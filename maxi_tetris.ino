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

void printBoard(long *board) {
	char i;
	char j;

	for ( i = 0; i < 25 - TETRIS_BOARD_HEIGHT + HEAD; i++ ) {
		Serial.print("\n");
	}

	for ( i = 0; i < TETRIS_BOARD_HEIGHT - HEAD; i++ ) {
    	digitalWrite(latchPinRow, 0);
		//move 'em out
		shiftOut(dataPinRow, clockPinRow,MSBFIRST, board[i]);
		//return the latch pin high to signal chip that it
		//no longer needs to listen for information
    	digitalWrite(latchPinRow, 1);

    	digitalWrite(latchPinColumn, 0);
		//move 'em out
		shiftOut(dataPinColumn, clockPinColumn, MSBFIRST, ~(1<<i));
		//return the latch pin high to signal chip that it
		//no longer needs to listen for information
    	digitalWrite(latchPinColumn, 1);

		for ( j = TETRIS_BOARD_WIDTH; j > 0 ; j-- ) {
			short level = ( board[i] & 1<<(j-1) ) != 0 ? 1 : 0;
			Serial.print(level);
		}
		Serial.print("\n");
delay(50);
	}
}

void loop() {
	long board[TETRIS_BOARD_HEIGHT];
	long boardDisplay[TETRIS_BOARD_HEIGHT];
	tetermino_t tetermino;

	memset(board, 0, sizeof(long) * TETRIS_BOARD_HEIGHT);

	createTetermino(&tetermino, l ); //rand() % 7);

	while(1) {
		calculateDisplayBoard(boardDisplay, board, &tetermino);
		printBoard(boardDisplay);
		
		
		if ( isCollision (board, &tetermino) ) {
			memcpy ( board, boardDisplay, sizeof(long) * TETRIS_BOARD_HEIGHT);
			createTetermino(&tetermino, l); // rand() % 7);
			if ( isCollision(board, &tetermino) ) {
				break;
			}
		} else {
			moveTetermino(&tetermino);
		}	
		delay(500);
	} 
}
