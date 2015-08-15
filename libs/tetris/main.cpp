#ifdef PC_DEBUG

#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include "tetris.h"

#define DISPLAY_COLLISIONS

uint8_t volatile isGameOver;
uint16_t volatile score;
tetrisboard_t currentBoard;
tetrisboard_t newBoard;
ledboard_t currentLedBoard;
ledboard_t newLedBoard;

tetermino_t tetermino;

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

void *threadMoveElements(void *ptr) {
	uint8_t hitGround;

	while ( ! isGameOver ) {
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
		usleep(250 * 1000);
	}
	return NULL;
}

void *threadGetKeys(void *ptr) {
	uint8_t inputChar;

	while ( !isGameOver) {
		inputChar = getch();
		if ( inputChar == 'a') {
			Tetris.move (&currentBoard, &tetermino, moveLeft);
		} else if ( inputChar == 's') {
			Tetris.move (&currentBoard, &tetermino, rotateLeft);
		} else if ( inputChar == 'd') {
			Tetris.move (&currentBoard, &tetermino, moveRight);
		} else if ( inputChar == 'w') {
			Tetris.move (&currentBoard, &tetermino, rotateRight);
		} else if ( inputChar == ' ') {
			Tetris.move (&currentBoard, &tetermino, moveDrop);
		}
	}
	return NULL;
}


void setup() {
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


void loop() {
	while(! isGameOver) {
		#ifdef DISPLAY_COLLISIONS
			Tetris.displayCollisions(&newBoard);
		#else
			LEDBoard.display(&newLedBoard);
		#endif
		usleep(250 * 1000);
	}

	for ( uint8_t i = 0; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
		for ( uint8_t j = 0; j < TETRIS_BOARD_WIDTH; j++ ) {
			currentLedBoard.red[i][j] = 1;
			currentLedBoard.blue[i][j] = 0;
			currentLedBoard.green[i][j] = 0;
		}
		#ifdef DISPLAY_COLLISIONS
			Tetris.displayCollisions(&newBoard);
		#else
			LEDBoard.display(&currentLedBoard);
		#endif
		usleep(500 * 1000);
	}
}

int main() {
	pthread_t thread1, thread2;

	setup();

	int16_t iret1 = pthread_create(&thread1, NULL, threadMoveElements, NULL);
	if(iret1) {
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}

	int16_t iret2 = pthread_create(&thread2, NULL, threadGetKeys, NULL);
	if(iret2) {
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}

	loop();

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	return 0;
}

#endif
