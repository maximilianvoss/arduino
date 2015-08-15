#ifndef __LEDBOARD_BOARD_H__
#define __LEDBOARD_BOARD_H__

#include "ledboard.h"

#ifdef __cplusplus
extern "C" {
#endif

void ledboard_createBoard(ledboard_t *ledboard);
void ledboard_removeLine(ledboard_t *ledboard, uint8_t pos);
void ledboard_setColor(ledboard_t *ledboard, uint8_t x, uint8_t y, enum ledboard_colorset_e color);

#ifdef __cplusplus
}
#endif

#endif