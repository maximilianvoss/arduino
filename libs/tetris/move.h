#ifndef __TETRIS_MOVE_H__
#define __TETRIS_MOVE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t tetris_move(tetrisboard_t *board, tetermino_t *tetermino, enum moveDirectionEnum direction);

#ifdef __cplusplus
}
#endif

#endif
