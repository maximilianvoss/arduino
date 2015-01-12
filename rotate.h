#ifndef __ROTATE_H__
#define __ROTATE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void rotateTeterminoRight(tetermino_t *tetermino);
void rotateRight(long *board, tetermino_t *tetermino);
void rotateTeterminoLeft(tetermino_t *tetermino);
void rotateLeft(long *board, tetermino_t *tetermino);

#ifdef __cplusplus
}
#endif

#endif
