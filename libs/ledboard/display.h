#ifndef __LEDBOARD_DISPLAY_H__
#define __LEDBOARD_DISPLAY_H__

#ifdef PC_DEBUG 
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
