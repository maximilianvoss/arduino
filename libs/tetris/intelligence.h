#ifndef __TETRIS_INTELLIGENCE_H__
#define __TETRIS_INTELLIGENCE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint8_t clearedLines;
	uint8_t holes;
	uint8_t ranking;
	uint8_t posX;
	enum posEnum pos;
} rating_t;

void tetris_calculateStack(ledboard_t *board, uint8_t *stack);
uint8_t tetris_calculateRanking(uint8_t *stack);
uint8_t tetris_calculateHoles(ledboard_t *board);
void tetris_calculateMove(ledboard_t *board, tetermino_t *tetermino);
rating_t tetris_calculateRating(ledboard_t *board, tetermino_t *tetermino);
uint8_t tetris_isBetterRating(rating_t *bestRating, rating_t *currentRating);

#ifdef __cplusplus
}
#endif

#endif