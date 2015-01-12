#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

char isRotateRightCollision(long *board, tetermino_t *tetermino);
char isRotateLeftCollision(long *board, tetermino_t *tetermino);
char isMoveLeftCollision(long *board, tetermino_t *tetermino);
char isMoveRightCollision(long *board, tetermino_t *tetermino);
char isCollision(long *board, tetermino_t *tetermino);

#ifdef __cplusplus
}
#endif

#endif

