#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t isCollision(ledboard_t *board, tetermino_t *tetermino);

#ifdef __cplusplus
}
#endif

#endif

