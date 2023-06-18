#ifndef PENDULUM_H
#define PENDULUM_H

#include <stdbool.h>

#include "objects/components/weight.h"

typedef struct {
    Vector2 rod_start;
    float rod_length;
    float angle; // radians
    float angular_vel;
    float angular_acc;
    Weight *weight;

    Color color;

    bool hold;
    bool pause;
} Pendulum;

Pendulum *pendulum_create(Vector2 rod_start, float rod_length, float angle, float weight_mass, Color color);

void pendulum_update(Pendulum *pendulum);
void pendulum_tick(Pendulum *pendulum);
void pendulum_render(Pendulum *pendulum);

void pendulum_destroy(Pendulum *pendulum);

#endif // PENDULUM_H
