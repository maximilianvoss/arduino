#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEAD 4
#define TETRIS_BOARD_HEIGHT 8
#define TETRIS_BOARD_WIDTH 8 
#define TETRIS_BOARD_TOTAL_HEIGHT (TETRIS_BOARD_HEIGHT + HEAD + 1)

enum teterminoEnum { i, j, l, o, t, s, z };
enum posEnum { up, left, down, right };
enum moveDirectionEnum { moveDown, moveLeft, moveRight, rotateLeft, rotateRight, moveDrop };

typedef struct {
	uint8_t volatile centerPosX;
	uint8_t volatile centerPosY;
	enum teterminoEnum type;
	enum posEnum volatile pos;
	uint16_t data[TETRIS_BOARD_TOTAL_HEIGHT];
} tetermino_t;

#include "tetermino.h"
#include "collision.h"
#include "move.h"

#ifdef __cplusplus
extern "C" {
#endif

void calculateDisplayBoard(uint16_t volatile *boardDisplay, uint16_t volatile *board, tetermino_t* tetermino);
void createBoard(uint16_t volatile *board);
uint8_t clearLines(uint16_t volatile *board);
void removeLine(uint16_t volatile *board, uint8_t pos);

#ifdef __cplusplus
}
#endif

#endif
