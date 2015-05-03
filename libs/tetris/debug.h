#ifdef PC_DEBUG
#ifndef __DEBUG_H__
#define __DEBUG_H__

//#define SHOW_COLORS
//#define DISPLAY_HEIGHT TETRIS_BOARD_TOTAL_HEIGHT
#define DISPLAY_HEIGHT TETRIS_BOARD_HEIGHT

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void printBoard(board_t *board);

#ifdef __cplusplus
}
#endif

#endif
#endif
