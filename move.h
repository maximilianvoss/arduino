#ifndef __MOVE_H__
#define __MOVE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void moveTetermino(tetermino_t *tetermino);
void moveTeterminoLeft(tetermino_t *tetermino);
void moveLeft(long *board, tetermino_t *tetermino);
void moveTeterminoRight(tetermino_t *tetermino );
void moveRight(long *board, tetermino_t *tetermino);

#ifdef __cplusplus
}
#endif

#endif
