#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEAD 4
#define TETRIS_BOARD_HEIGHT 23
#define TETRIS_BOARD_WIDTH 10 

enum teterminoEnum { i, j, l, o, t, s, z };
enum posEnum { up, left, down, right };
enum moveDirectionEnum { moveDown, moveLeft, moveRight, rotateLeft, rotateRight, moveDrop };

typedef struct {
	uint8_t centerPosX;
	uint8_t centerPosY;
	enum teterminoEnum type;
	enum posEnum pos;
	uint16_t data[TETRIS_BOARD_HEIGHT];
} tetermino_t;

#include "tetermino.h"
#include "collision.h"
#include "move.h"

#ifdef __cplusplus
extern "C" {
#endif

void calculateDisplayBoard(uint16_t *boardDisplay, uint16_t *board, tetermino_t* tetermino);
void createBoard(uint16_t *board);
uint8_t clearLines(uint16_t *board);
void removeLine(uint16_t *board, uint8_t pos);

#ifdef __cplusplus
}
#endif

#endif
