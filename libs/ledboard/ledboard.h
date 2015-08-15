#ifndef __LEDBOARD_LEDBOARD_H__
#define __LEDBOARD_LEDBOARD_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "config.h"

typedef struct {
	uint16_t volatile collision[LED_BOARD_TOTAL_HEIGHT];
	uint8_t volatile red[LED_BOARD_TOTAL_HEIGHT][LED_BOARD_WIDTH];
	uint8_t volatile green[LED_BOARD_TOTAL_HEIGHT][LED_BOARD_WIDTH];
	uint8_t volatile blue[LED_BOARD_TOTAL_HEIGHT][LED_BOARD_WIDTH];
} ledboard_t;

#define LEDBOARD_COLOR_SETS { \
	{0xFF, 0xFF, 0xFF}, \
	{0xFF, 0xFF, 0xFF}, \
	{0xFF, 0xFF, 0xFF}, \
	{0xFF, 0xFF, 0x00}, \
	{0xFF, 0xFF, 0xFF}, \
	{0xFF, 0x00, 0xFF}, \
	{0xFF, 0x00, 0x00} }
enum ledboard_colorset_e { cyan, blue, orange, yellow, lime, magenta, red };

#include "display.h"

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