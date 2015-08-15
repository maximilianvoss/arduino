#ifdef PC_DEBUG

#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include "tetris.h"

uint8_t volatile isGameOver;
uint16_t volatile score;
ledboard_t board;
ledboard_t boardDisplay;

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
		tetris_calculateDisplayBoard(&boardDisplay, &board, &tetermino);

		hitGround = tetris_move(&board, &tetermino, moveDown);
		if ( hitGround ) {
			memcpy ( &board, &boardDisplay, sizeof(ledboard_t));
			tetris_createTetermino(&tetermino);
		}
		score += tetris_clearLines(&board);
		if ( hitGround ) {
			tetris_calculateMove(&board, &tetermino);
		}
		if ( tetris_isCollision(&board, &tetermino) ) {
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
			tetris_move (&board, &tetermino, moveLeft);
		} else if ( inputChar == 's') {
			tetris_move (&board, &tetermino, rotateLeft);
		} else if ( inputChar == 'd') {
			tetris_move (&board, &tetermino, moveRight);
		} else if ( inputChar == 'w') {
			tetris_move (&board, &tetermino, rotateRight);
		} else if ( inputChar == ' ') {
			tetris_move (&board, &tetermino, moveDrop);
		}
	}
	return NULL;
}

int main() {
	pthread_t thread1, thread2;
	isGameOver = 0;
	score = 0;

	ledboard_createBoard(&board);
	tetris_createTetermino(&tetermino);
	tetris_calculateMove(&board, &tetermino);

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

	while(! isGameOver) {
		ledboard_display(&boardDisplay);
		usleep(250 * 1000);
	}

	for ( uint8_t i = 0; i < TETRIS_BOARD_TOTAL_HEIGHT; i++ ) {
		board.collision[i] = 0xFFFF;
		ledboard_display(&board);
		usleep(500 * 1000);
	}
	
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	return 0;
}

#endif
