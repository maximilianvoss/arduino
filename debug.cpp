#include "debug.h"

#ifdef PC_DEBUG

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

void printBoard(uint16_t *board) {
	uint8_t i;
	uint8_t j;

	for ( i = 0; i < 25 - TETRIS_BOARD_HEIGHT + HEAD; i++ ) {
		printf("\n");
	}

	for ( i = TETRIS_BOARD_HEIGHT - HEAD; i > 0 ; i-- ) {

		for ( j = TETRIS_BOARD_WIDTH + 1; j >0 ; j-- ) {
			short level = ( board[i - 1] & 1<<(j-1) ) != 0 ? 1 : 0;
			printf("%d ", level);
		}
		printf("\n");
	}
}

int main() {
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
		//usleep(250 * 1000);
	} 


	for ( i = 0; i < TETRIS_BOARD_HEIGHT; i++ ) {
		board[i] = 0xFFFF;
		printBoard(board);
		usleep(250 * 1000);
	}
	

	return 0;
}

#endif
