#include "intelligence.h"

void tetris_calculateMove(tetrisboard_t *board, tetermino_t *tetermino) {
	tetrisboard_t boardCalculation;
	rating_t bestRating;
	rating_t currentRating;
	uint8_t start;
	uint8_t stop;
	uint8_t rotations;
	uint8_t i;
	uint8_t j;

	bestRating.clearedLines = 0;
	bestRating.holes = 0x7F;
	bestRating.ranking = 0x7F;

	rotations = tetris_calculateRotations(tetermino);
	for ( i = 0; i < rotations; i++ ) {
		tetermino->pos = i;
		tetris_calculateConstraints(tetermino, &start, &stop);

		for ( j = start; j <= stop; j++ ) {
			tetermino->centerPosY = TETRIS_BOARD_TOTAL_HEIGHT - 3;
			tetermino->centerPosX = j;

			tetris_createTeterminoData(tetermino);

			if ( ! tetris_isCollision(board, tetermino ) ) {
				tetris_move (board, tetermino, moveDrop);
				tetris_merge(&boardCalculation, board, tetermino);

				currentRating = tetris_calculateRating(&boardCalculation, tetermino);

				if ( tetris_isBetterRating(&bestRating, &currentRating ) ) {
					bestRating.clearedLines = currentRating.clearedLines;
					bestRating.holes = currentRating.holes;
					bestRating.ranking = currentRating.ranking;

					bestRating.posX = tetermino->centerPosX;
					bestRating.pos = tetermino->pos;
				}
			}
		}
	}

	tetermino->centerPosY = TETRIS_BOARD_TOTAL_HEIGHT - 3;
	tetermino->centerPosX = bestRating.posX;
	tetermino->pos = bestRating.pos;
	tetris_createTeterminoData(tetermino);
}


// TODO: Make it more readable
uint8_t tetris_isBetterRating(rating_t *bestRating, rating_t *currentRating) {

	int8_t diffClearedLines = bestRating->clearedLines - currentRating->clearedLines;
	int8_t diffHoles = bestRating->holes - currentRating->holes;
	int8_t diffRanking = bestRating->ranking - currentRating->ranking;

	if ( diffClearedLines < 0 ) {
		return 1;
	} else {
		if ( diffClearedLines == 0 ) {
			if ( diffHoles > 0 ) {
				return 1;
			} else {
				if ( diffHoles == 0 ) {
					if ( diffRanking > 0 ) {
						return 1;
					} else {
						return 0;
					}
				} else {
					return 0;
				}
			}
		} else {
			return 0;
		}
	}
}

rating_t tetris_calculateRating(tetrisboard_t *board, tetermino_t *tetermino) {
	rating_t rating;

	uint8_t stack[TETRIS_BOARD_WIDTH];
	tetris_calculateStack(board, stack);

	rating.clearedLines = tetris_clearLines(board, NULL);
	rating.holes = tetris_calculateHoles(board);
	rating.ranking = tetris_calculateRanking(stack);

	return rating;
}

// TODO: merge tetris_calculateStack and tetris_calculateRanking
void tetris_calculateStack(tetrisboard_t *board, uint8_t *stack) {
	uint8_t i;
	uint8_t j;

	memset(stack, 0, sizeof(uint8_t) * TETRIS_BOARD_WIDTH);

	for ( i = TETRIS_BOARD_HEIGHT + 1; i > 1; i-- ) {
		for ( j = 2; j < TETRIS_BOARD_WIDTH + 2; j++ ) {
			if ( stack[j - 2] == 0 ) {
				stack[j - 2] = (board->collision[i - 1] & 1<<(j-1)) != 0 ? (i - 1) : 0;
			}
		}
	}
}

uint8_t tetris_calculateRanking(uint8_t *stack) {
	uint8_t i;
	uint8_t result = 0;
	int8_t diff;

	for ( i = 0; i < TETRIS_BOARD_WIDTH - 1; i++ ) {
		diff = stack[i] - stack[i + 1];
		if ( diff < 0 ) {
			diff *= -1;
		}
		result += diff;
	}
	return result;
}

uint8_t tetris_calculateHoles(tetrisboard_t *board) {
	uint8_t i;
	uint8_t j;
	uint8_t holeCount = 0;
	uint8_t current;
	uint8_t last;
	uint8_t hit;

	for ( j = 2; j < TETRIS_BOARD_WIDTH + 2; j++ ) {
		last = 0;
		hit = 0;
		for ( i = TETRIS_BOARD_HEIGHT + 1; i > 1; i-- ) {
			current = (board->collision[i - 1] & 1<<(j-1)) != 0 ? (i - 1) : 0;
			if ( current == 0 && (last != 0 || hit )) {
				holeCount++;
				hit = 1;
			}
			last = current;
		}
	}

	return holeCount;
}
