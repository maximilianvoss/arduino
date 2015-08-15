#ifndef __TETRIS_COLLISION_H__
#define __TETRIS_COLLISION_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t tetris_isCollision(tetrisboard_t *board, tetermino_t *tetermino);

#ifdef __cplusplus
}
#endif

#endif

