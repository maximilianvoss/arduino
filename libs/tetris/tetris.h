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

#define COLOR_SETS { \
	{255, 128, 7}, \
	{255, 127, 6}, \
	{255, 126, 5}, \
	{255, 125, 4}, \
	{255, 124, 3}, \
	{255, 123, 2}, \
	{255, 122, 1} }

enum teterminoEnum { i, j, l, o, t, s, z };
enum posEnum { up, left, down, right };
enum moveDirectionEnum { moveDown, moveLeft, moveRight, rotateLeft, rotateRight, moveDrop };
enum colorEnum { cyan, blue, orange, yellow, lime, magenta, red };

typedef struct {
	uint8_t volatile centerPosX;
	uint8_t volatile centerPosY;
	enum colorEnum color;
	enum teterminoEnum type;
	enum posEnum volatile pos;
	uint16_t data[TETRIS_BOARD_TOTAL_HEIGHT];
} tetermino_t;

typedef struct {
	uint16_t volatile collision[TETRIS_BOARD_TOTAL_HEIGHT];
	uint8_t volatile red[TETRIS_BOARD_TOTAL_HEIGHT][TETRIS_BOARD_WIDTH];
	uint8_t volatile green[TETRIS_BOARD_TOTAL_HEIGHT][TETRIS_BOARD_WIDTH];
	uint8_t volatile blue[TETRIS_BOARD_TOTAL_HEIGHT][TETRIS_BOARD_WIDTH];
} board_t;

#include "tetermino.h"
#include "collision.h"
#include "move.h"

#ifdef __cplusplus
extern "C" {
#endif

void calculateDisplayBoard(board_t *boardDisplay, board_t *board, tetermino_t* tetermino);
void createBoard(board_t *board);
uint8_t clearLines(board_t *board);
void removeLine(board_t *board, uint8_t pos);
void setColor(board_t *board, tetermino_t *tetermino, uint8_t x, uint8_t y);

#ifdef __cplusplus
}
#endif

#endif
