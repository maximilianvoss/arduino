#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void tetris_createBoard(tetrisboard_t *board);
void tetris_calculateDisplayBoard(ledboard_t *newBoard, ledboard_t *currentBoard, tetermino_t *tetermino);
void tetris_merge(tetrisboard_t *newBoard, tetrisboard_t *currentBoard, tetermino_t *tetermino);
uint8_t tetris_clearLines(tetrisboard_t *board, ledboard_t *ledBoard);
void tetris_removeLine(tetrisboard_t *board, uint8_t pos);

#ifdef PC_DEBUG
	void tetris_displayCollisions(tetrisboard_t *board);
#endif

#ifdef __cplusplus
}
#endif

#endif
