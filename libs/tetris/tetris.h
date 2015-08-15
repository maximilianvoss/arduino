#ifndef __TETRIS_TETRIS_H__
#define __TETRIS_TETRIS_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ledboard.h>

#define HEAD 4
#define TETRIS_BOARD_HEIGHT LED_BOARD_HEIGHT
#define TETRIS_BOARD_WIDTH LED_BOARD_WIDTH
#define TETRIS_BOARD_TOTAL_HEIGHT (TETRIS_BOARD_HEIGHT + HEAD + 1)

enum teterminoEnum { i, j, l, o, t, s, z };
enum posEnum { up, left, down, right };
enum moveDirectionEnum { moveDown, moveLeft, moveRight, rotateLeft, rotateRight, moveDrop };

typedef struct {
	uint8_t volatile centerPosX;
	uint8_t volatile centerPosY;
	enum ledboard_colorset_e color;
	enum teterminoEnum type;
	enum posEnum volatile pos;
	uint16_t data[TETRIS_BOARD_TOTAL_HEIGHT];
} tetermino_t;

#include "tetermino.h"
#include "collision.h"
#include "move.h"
#include "intelligence.h"

#ifdef __cplusplus
extern "C" {
#endif

void tetris_calculateDisplayBoard(ledboard_t *boardDisplay, ledboard_t *board, tetermino_t* tetermino);
uint8_t tetris_clearLines(ledboard_t *board);
void tetris_setColor(ledboard_t *board, tetermino_t *tetermino, uint8_t x, uint8_t y);

#ifdef __cplusplus
}
#endif

#endif
