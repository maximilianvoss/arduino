#include "ledboard.h"

const ledboard_library_t LEDBoard = {
	.createBoard = ledboard_createBoard,
	.removeLine = ledboard_removeLine,
	.setColor = ledboard_setColor,
	.display = ledboard_display
};