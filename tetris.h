#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEAD 4
#define TETRIS_BOARD_HEIGHT 23
#define TETRIS_BOARD_WIDTH 10 

enum teterminoEnum { i, j, l, o, t, s, z };
enum posEnum { up, left, down, right };
enum moveDirectionEnum { moveDown, moveLeft, moveRight, rotateLeft, rotateRight };

typedef struct {
	char centerPosX;
	char centerPosY;
	enum teterminoEnum type;
	enum posEnum pos;
	long data[TETRIS_BOARD_HEIGHT];
} tetermino_t;

#include "tetermino.h"
#include "collision.h"
#include "move.h"

#ifdef __cplusplus
extern "C" {
#endif

void calculateDisplayBoard(long *boardDisplay, long *board, tetermino_t* tetermino);
void createBoard(long *board);

#ifdef __cplusplus
}
#endif

#endif
