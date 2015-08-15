#include "tetris.h"


const tetris_library_t Tetris = {
    .calculateDisplayBoard = tetris_calculateDisplayBoard,
    .createTetermino = tetris_createTetermino,
    .move = tetris_move,
    .clearLines = tetris_clearLines,
    .calculateMove = tetris_calculateMove,
    .isCollision = tetris_isCollision,
    .initTeterminoHistory = tetris_initTeterminoHistory
};