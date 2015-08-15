#ifndef __TETRIS_TETERMINO_H__
#define __TETRIS_TETERMINO_H__

#include "tetris.h"

#define TETERMINO_CREATION_HISTORY 4
#define TETERMINO_CREATION_THERSHOLD 1

#ifdef __cplusplus
extern "C" {
#endif

void tetris_initTeterminoHistory();
void tetris_createTeterminoData(tetermino_t *tetermino);
uint8_t tetris_calculateRotations(tetermino_t *tetermino);
void tetris_calculateConstraints(tetermino_t *tetermino, uint8_t *start, uint8_t *stop);
uint8_t tetris_calculateNewTetermino();
uint8_t tetris_checkTeterminoHistory(uint8_t value);
void tetris_createTetermino(tetermino_t* tetermino);

#ifdef __cplusplus
}
#endif

#endif
