#include <math.h>

#include "state.h"
#include "common.h"

static inline float degree_to_radian(double degree)
{
    float pi = 3.14159;
    return (degree * (pi / 180));
}

static Vector2 calculate_direction(int angle) 
{
    float radian_angle = degree_to_radian(angle);
	return new_vec(cosf(radian_angle), sinf(radian_angle));
}

void make_particle(Vector2 at)
{
}

void particles_init(void)
{
}

void particles_update(void)
{
}

void particles_draw(void)
{
}


