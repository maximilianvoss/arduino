#ifndef __TETERMINO_H__
#define __TETERMINO_H__

#include "tetris.h"

#define TETERMINO_CREATION_HISTORY 4
#define TETERMINO_CREATION_THERSHOLD 1

#ifdef __cplusplus
extern "C" {
#endif

void initTeterminoHistory();
void createTeterminoData(tetermino_t *tetermino);
uint8_t calculateNewTetermino();
uint8_t checkTeterminoHistory(uint8_t value);
void createTetermino(tetermino_t* tetermino);

#ifdef __cplusplus
}
#endif

#endif
