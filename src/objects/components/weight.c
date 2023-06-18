#include <stdlib.h>

#include "objects/components/weight.h"

Weight *weight_create(float radius, float mass)
{
	Weight *weight = malloc(sizeof(Weight));

	weight->radius = radius;
	weight->mass = mass;

	return weight;
}

void weight_destroy(Weight *weight)
{
	free(weight);
}
