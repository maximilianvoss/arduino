#include "board.h"

static uint8_t led_matrix_colors[7][3] = LEDBOARD_COLOR_SETS;

void ledboard_createBoard(ledboard_t *ledboard) {
	uint8_t i;
	memset((void *) ledboard->red, 0, sizeof(uint8_t) * LED_BOARD_TOTAL_HEIGHT * LED_BOARD_WIDTH);
	memset((void *) ledboard->green, 0, sizeof(uint8_t) * LED_BOARD_TOTAL_HEIGHT * LED_BOARD_WIDTH);
	memset((void *) ledboard->blue, 0, sizeof(uint8_t) * LED_BOARD_TOTAL_HEIGHT * LED_BOARD_WIDTH);
}

void ledboard_removeLine(ledboard_t *ledboard, uint8_t pos) {
	uint8_t i;

	for ( i = pos; i < LED_BOARD_HEIGHT - 1; i++ ) {
		memcpy((void *) ledboard->red[i], (void *) ledboard->red[i+1], sizeof(uint8_t) * LED_BOARD_WIDTH);
		memcpy((void *) ledboard->green[i], (void *) ledboard->green[i+1], sizeof(uint8_t) * LED_BOARD_WIDTH);
		memcpy((void *) ledboard->blue[i], (void *) ledboard->blue[i+1], sizeof(uint8_t) * LED_BOARD_WIDTH);
	}
	memset((void *) ledboard->red[LED_BOARD_HEIGHT - 1], 0, sizeof(uint8_t) * LED_BOARD_WIDTH);
	memset((void *) ledboard->green[LED_BOARD_HEIGHT - 1], 0, sizeof(uint8_t) * LED_BOARD_WIDTH);
	memset((void *) ledboard->blue[LED_BOARD_HEIGHT - 1], 0, sizeof(uint8_t) * LED_BOARD_WIDTH);
}

void ledboard_setColor(ledboard_t *ledboard, uint8_t x, uint8_t y, enum ledboard_colorset_e color) {
	ledboard->red[y][x-1] = led_matrix_colors[color][0];
	ledboard->green[y][x-1] = led_matrix_colors[color][1];
	ledboard->blue[y][x-1] = led_matrix_colors[color][2];
}