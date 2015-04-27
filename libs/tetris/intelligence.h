#ifndef __INTELLIGENCE_H__
#define __INTELLIGENCE_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void calculateStack(board_t *board, uint8_t *stack);

#ifdef __cplusplus
}
#endif

#endif