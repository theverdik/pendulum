#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"
#include "objects/pendulum.h"

#define FONT_SIZE 30
#define RADIUS 15.0f
#define G (9.81f / 65.0f)

static Vector2 pendulum_get_rod_end(Pendulum *pendulum);

Pendulum *pendulum_create(Vector2 rod_start, float rod_length, float angle, float weight_mass, Color color)
{
	Pendulum *pendulum = malloc(sizeof(Pendulum));

	pendulum->rod_start = rod_start;
	pendulum->rod_length = rod_length;

	pendulum->angle = angle;
	pendulum->angular_vel = 0.0f;
	pendulum->angular_acc = 0.0f;

	pendulum->weight = weight_create(RADIUS, weight_mass);

	pendulum->color = color;

	pendulum->hold = false;
	pendulum->pause = false;

	return pendulum;
}

void pendulum_update(Pendulum *pendulum)
{
	if (IsKeyPressed(KEY_SPACE)) {
		pendulum->pause = !pendulum->pause;
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Vector2 mouse_pos = math_vec2_sub(GetMousePosition(), SCREEN_OFFSET);

		if (CheckCollisionPointCircle(mouse_pos, pendulum_get_rod_end(pendulum), pendulum->weight->radius) || pendulum->hold)
			pendulum->hold = true;

		pendulum->angle = -fmod(atan2f(mouse_pos.y, mouse_pos.x) - 2.0f * PI / 4.0f, 2.0f * PI);

		pendulum->angular_vel = 0.0f;
		pendulum->angular_acc = 0.0f;
	}
	else
		pendulum->hold = false;
}

void pendulum_tick(Pendulum *pendulum)
{
	if (pendulum->pause || pendulum->hold)
		return;

	pendulum->angular_acc = -(G / pendulum->rod_length) * sin(pendulum->angle);

	// pendulum->angular_vel *= 0.999f;

	pendulum->angular_vel += pendulum->angular_acc;

	pendulum->angle += pendulum->angular_vel;
}

void pendulum_render(Pendulum *pendulum)
{
	if (pendulum->hold)
		DrawText("HOLDING WEIGHT", 5, HEIGHT - FONT_SIZE, FONT_SIZE, WHITE);
	else if (pendulum->pause)
		DrawText("PAUSE", 5, HEIGHT - FONT_SIZE, FONT_SIZE, WHITE);

	Vector2 pendulum_rod_end = pendulum_get_rod_end(pendulum);

	renderer_render_line(pendulum->rod_start, pendulum_rod_end, 2.0f, pendulum->color);
	renderer_render_circle(pendulum_rod_end, pendulum->weight->radius, pendulum->color);
}

static Vector2 pendulum_get_rod_end(Pendulum *pendulum)
{
	return (Vector2){pendulum->rod_length * sinf(pendulum->angle), pendulum->rod_length * cosf(pendulum->angle)};
}

void pendulum_destroy(Pendulum *pendulum)
{
	weight_destroy(pendulum->weight);
	free(pendulum);
}
