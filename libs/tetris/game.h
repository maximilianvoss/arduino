#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void tetris_calculateDisplayBoard(ledboard_t *boardDisplay, ledboard_t *board, tetermino_t* tetermino);
uint8_t tetris_clearLines(ledboard_t *board);
void tetris_setColor(ledboard_t *board, tetermino_t *tetermino, uint8_t x, uint8_t y);

#ifdef __cplusplus
}
#endif

#endif
