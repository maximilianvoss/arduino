#include <Arduino.h>
#include <PS3BT.h>
#include <usbhub.h>
#include <ledboard.h>
#include <tetris.h>
#include "config.h"

USB Usb;
BTD BluetoothDongle(&Usb);
PS3BT PS3(&BluetoothDongle, BLUETOOTH_MAC_ADDRESS);

ledboard_t board;
ledboard_t boardDisplay;
uint8_t volatile gameOver;
tetermino_t tetermino;

ISR(TIMER1_COMPA_vect) {
	if ( ! gameOver ) {
		if ( Tetris.move(&board, &tetermino, moveDown) ) {
			memcpy(&board, &boardDisplay, sizeof(ledboard_t));
			Tetris.createTetermino(&tetermino);
		}
		Tetris.clearLines(&board);
		if ( Tetris.isCollision(&board, &tetermino) ) {
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

	if (Usb.Init() == -1) {
		Serial.print(F("\r\nOSC did not start"));
    	while (1);
	}
	Serial.print(F("\r\nPS3 Bluetooth Library Started"));

	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 15624;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	sei();

	Tetris.initTeterminoHistory();
}

void keyAction() {
	Usb.Task();
	if ( PS3.getButtonClick(PS) ) {
		gameOver = 1;
		PS3.disconnect();
	}
	if ( PS3.getButtonClick(CIRCLE) ) {
		Tetris.move(&board, &tetermino, rotateLeft);
	}
	if ( PS3.getButtonClick(CROSS) ) {
		Tetris.move(&board, &tetermino, rotateRight);
	}
	if ( PS3.getButtonClick(UP) ) {
		Tetris.move(&board, &tetermino, moveDrop);
	}
	if ( PS3.getButtonClick(RIGHT) ) {
		Tetris.move(&board, &tetermino, moveRight);
	}
	if ( PS3.getButtonClick(DOWN) ) {
		Tetris.move(&board, &tetermino, moveDown);
	}
	if ( PS3.getButtonClick(LEFT) ) {
		Tetris.move(&board, &tetermino, moveLeft);
	}	
}

void loop() {
	Usb.Task();

	if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
		gameOver = 0;
		LEDBoard.createBoard(&board);
		Tetris.createTetermino(&tetermino);

		while(! gameOver) {
			keyAction();
			Tetris.calculateDisplayBoard(&boardDisplay, &board, &tetermino);
			LEDBoard.display(&boardDisplay);	
		} 

		while (gameOver) {
			LEDBoard.display(&board);
		}
	}
}

