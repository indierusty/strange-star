#ifndef ESTAR_H
#define ESTAR_H

#include "common.h"

typedef struct {
	bool active;
	Vector2 position;
	float radius;
	float max_radius;
	/// speed of strange gravity 
	float speed;
	/// direction towards player
	Vector2 direction;
	/// time related
	float time_counter;
	float start_time;
	float duration;

	float blink_speed;
} Estar;

void estar_init(Estar* e);
void estars_init(void);
void estars_update(void);
void estars_draw(void);

#endif
