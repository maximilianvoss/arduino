#ifndef __MOVE_H__
#define __MOVE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t move(ledboard_t *board, tetermino_t *tetermino, enum moveDirectionEnum direction);

#ifdef __cplusplus
}
#endif

#endif
