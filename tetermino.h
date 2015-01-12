#ifndef __TETERMINO_H__
#define __TETERMINO_H__

#include "tetris.h"

#ifdef __cplusplus
extern "C" {
#endif

void createTeterminoData(tetermino_t *tetermino);
void createTetermino(tetermino_t* tetermino, enum teterminoEnum type);

#ifdef __cplusplus
}
#endif

#endif
