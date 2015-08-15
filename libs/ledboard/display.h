#ifndef __LEDBOARD_DISPLAY_H__
#define __LEDBOARD_DISPLAY_H__

#ifdef PC_DEBUG
	// if enabled: show only visable rows
	#define LED_DISPLAY_HEIGHT LED_BOARD_HEIGHT 
	
	// if enabled: show all rows including head rows
	//#define LED_DISPLAY_HEIGHT LED_BOARD_TOTAL_HEIGHT 

	// if enabled: show collision plus all 3 colors
	#define SHOW_COLORS 
#endif

#include "ledboard.h"

#ifdef __cplusplus
extern "C" {
#endif

void ledboard_display(ledboard_t *board);

#ifdef __cplusplus
}
#endif

#endif
