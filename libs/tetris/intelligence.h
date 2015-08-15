#ifndef __INTELLIGENCE_H__
#define __INTELLIGENCE_H__

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

void calculateStack(ledboard_t *board, uint8_t *stack);
uint8_t calculateRanking(uint8_t *stack);
uint8_t calculateHoles(ledboard_t *board);
void calculateMove(ledboard_t *board, tetermino_t *tetermino);
rating_t calculateRating(ledboard_t *board, tetermino_t *tetermino);
uint8_t isBetterRating(rating_t *bestRating, rating_t *currentRating);

#ifdef __cplusplus
}
#endif

#endif