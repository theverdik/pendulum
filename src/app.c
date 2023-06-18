#include <raylib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "graphics/renderer.h"
#include "objects/pendulum.h"

static App *init(void);

static void update(App *app);
static void tick(App *app);
static void render(App *app);

static void terminate(App *app);

static App *init(void)
{
	App *app = malloc(sizeof(App));

	app->window = window_init(WIDTH, HEIGHT, TITLE);

	app->pendulums = list_create((destructor)pendulum_destroy, sizeof(Pendulum));

	return app;
}

void app_run(void)
{
	App *app = init();

	const double delta_time = 1.0 / 100.0;

	list_add(app->pendulums, pendulum_create((Vector2){0.0f, 0.0f}, 150.0f, PI / 2, 100.0f, WHITE));

	double currentTime = GetTime();
	double newTime;
	double accumulator = 0.0;

	while (!window_should_close())
	{
		update(app);

		newTime = GetTime();

		accumulator += newTime - currentTime;
		currentTime = newTime;

		while (accumulator >= delta_time)
		{
			tick(app);

			accumulator -= delta_time;
		}

		render(app);
		DrawFPS(0, 0);
	}

	terminate(app);
}

static void update(App *app)
{
	window_update(app->window);

	for (Node *temp = app->pendulums->head; temp != NULL; temp = temp->next)
		pendulum_update(temp->data);
}

static void tick(App *app)
{
	for (Node *temp = app->pendulums->head; temp != NULL; temp = temp->next)
		pendulum_tick(temp->data);
}

static void render(App *app)
{
	BeginDrawing();
	ClearBackground(app->window->background);

	for (Node *temp = app->pendulums->head; temp != NULL; temp = temp->next) {
		pendulum_render(temp->data);
	}

	EndDrawing();
}

static void terminate(App *app)
{
	list_free(app->pendulums);
	window_destroy(app->window);
	free(app);
}
