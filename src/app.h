#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "graphics/window.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "Pendulum"

#define DELTA_TIME ((double)(1 / 60.0))
#define METER ((float)(100.0f))

#define SCREEN_OFFSET (Vector2){WIDTH / 2.0f, HEIGHT / 2.0f}

typedef struct {
	Window *window;
	float delta_time;

	List *pendulums;
} App;

void app_run(void);

#endif // GAME_H
