#include "debug.h"

#ifdef PC_DEBUG

uint8_t volatile isGameOver;
uint16_t volatile board[TETRIS_BOARD_HEIGHT];
uint16_t volatile boardDisplay[TETRIS_BOARD_HEIGHT];

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

void printBoard(uint16_t volatile *board) {
	for ( uint8_t i = 0; i < 25 - TETRIS_BOARD_HEIGHT + HEAD; i++ ) {
		printf("\n");
	}

	for ( uint8_t i = TETRIS_BOARD_HEIGHT - HEAD; i > 0 ; i-- ) {
		for ( uint8_t j = TETRIS_BOARD_WIDTH + 2; j > 0 ; j-- ) {
			uint8_t level = ( board[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			if ( level ) {
				printf("1 "); 
			} else {
				printf("  ");
			}
		}
		printf("\n");
	}
}

void *threadMoveElements(void *ptr) {
	while ( ! isGameOver) {
		calculateDisplayBoard(boardDisplay, board, &tetermino);
		if ( move(board, &tetermino, moveDown) ) {
			memcpy ( (void *) board, (void *) boardDisplay, sizeof(short) * TETRIS_BOARD_HEIGHT);
			createTetermino(&tetermino, static_cast<teterminoEnum>(rand() % 7));
		}
		clearLines(board);
		if ( isCollision(board, &tetermino) ) {
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
			move (board, &tetermino, moveLeft);
		} else if ( inputChar == 's') {
			move (board, &tetermino, rotateLeft);
		} else if ( inputChar == 'd') {
			move (board, &tetermino, moveRight);
		} else if ( inputChar == 'w') {
			move (board, &tetermino, rotateRight);
		} else if ( inputChar == ' ') {
			move (board, &tetermino, moveDrop);
		}
	}
	return NULL;
}

int main() {
	pthread_t thread1, thread2;
	isGameOver = 0;

	//board = (uint16_t*) malloc(sizeof(uint16_t) * TETRIS_BOARD_HEIGHT);
	//boardDisplay = (uint16_t*) malloc(sizeof(uint16_t) * TETRIS_BOARD_HEIGHT);
//	uint16_t volatile board[TETRIS_BOARD_HEIGHT];
//uint16_t volatile boardDisplay[TETRIS_BOARD_HEIGHT];

	createBoard(board);
	createTetermino(&tetermino, static_cast<teterminoEnum>(rand() % 7));

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
		printBoard(boardDisplay);
		usleep(250 * 1000);
	}


	for ( uint8_t i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 0xFFFF;
		printBoard(board);
		usleep(500 * 1000);
	}
	
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	return 0;
}

#endif
