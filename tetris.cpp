#include <Arduino.h>
#include <PS3BT.h>
#include <usbhub.h>
#include <ledboard.h>
#include <tetris.h>
#include "config.h"

USB Usb;
BTD BluetoothDongle(&Usb);
PS3BT PS3(&BluetoothDongle, BLUETOOTH_MAC_ADDRESS);

uint8_t volatile isGameOver;
uint8_t volatile isStarted;
uint16_t volatile score;
tetrisboard_t currentBoard;
tetrisboard_t newBoard;
ledboard_t currentLedBoard;
ledboard_t newLedBoard;

tetermino_t tetermino;

ISR(TIMER1_COMPA_vect) {
	uint8_t hitGround;

	if ( ! isStarted ) {
		return;
	}

	if ( ! isGameOver ) {
		hitGround = Tetris.move(&currentBoard, &tetermino, moveDown);
		Tetris.merge(&newBoard, &currentBoard, &tetermino);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);

		if ( hitGround ) {
			Tetris.merge(&currentBoard, NULL, &tetermino);
			memcpy(&currentLedBoard, &newLedBoard, sizeof(ledboard_t));
			Tetris.createTetermino(&tetermino);
		}

		score += Tetris.clearLines(&currentBoard, &currentLedBoard);
		if ( hitGround ) {
			Tetris.calculateMove(&currentBoard, &tetermino);
		}
		if ( Tetris.isCollision(&currentBoard, &tetermino) ) {
			isGameOver = 1;
		}
	} else {
		for ( uint8_t j = 0; j < TETRIS_BOARD_WIDTH; j++ ) {
			currentLedBoard.red[isGameOver][j] = 1;
			currentLedBoard.blue[isGameOver][j] = 0;
			currentLedBoard.green[isGameOver][j] = 0;
			isGameOver++;
		}
		if ( isGameOver > TETRIS_BOARD_HEIGHT ) {
			isGameOver = 0;
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

	isStarted = 0;

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

	LEDBoard.createBoard(&currentLedBoard);
	LEDBoard.createBoard(&newLedBoard);

	Tetris.createBoard(&currentBoard);
	Tetris.createBoard(&newBoard);

	Tetris.createTetermino(&tetermino);
	Tetris.calculateMove(&currentBoard, &tetermino);

	isGameOver = 0;
	score = 0;
}

void keyAction() {
	Usb.Task();
	if ( PS3.getButtonClick(PS) ) {
		isGameOver = 1;
		isStarted = 0;
		PS3.disconnect();
	}
	if ( PS3.getButtonClick(CIRCLE) ) {
		Tetris.move(&currentBoard, &tetermino, rotateLeft);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);
	}
	if ( PS3.getButtonClick(CROSS) ) {
		Tetris.move(&currentBoard, &tetermino, rotateRight);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);
	}
	if ( PS3.getButtonClick(UP) ) {
		Tetris.move(&currentBoard, &tetermino, moveDrop);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);
	}
	if ( PS3.getButtonClick(RIGHT) ) {
		Tetris.move(&currentBoard, &tetermino, moveRight);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);
	}
	if ( PS3.getButtonClick(DOWN) ) {
		Tetris.move(&currentBoard, &tetermino, moveDown);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);
	}
	if ( PS3.getButtonClick(LEFT) ) {
		Tetris.move(&currentBoard, &tetermino, moveLeft);
		Tetris.calculateDisplayBoard(&newLedBoard, &currentLedBoard, &tetermino);
	}	
}

void loop() {
	Usb.Task();

	isStarted = 0;
	if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
		isStarted = 1;
		while(! isGameOver) {
			keyAction();
			LEDBoard.display(&newLedBoard);	
		} 

		while (isGameOver) {
			LEDBoard.display(&currentLedBoard);
		}
	}
}

