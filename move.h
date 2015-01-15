#ifndef __MOVE_H__
#define __MOVE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

char move(uint16_t volatile *board, tetermino_t *tetermino, enum moveDirectionEnum direction);

#ifdef __cplusplus
}
#endif

#endif
