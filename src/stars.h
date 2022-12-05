#ifndef STARS_H
#define STARS_H

#include "common.h"

typedef struct {
	Vector2 position;

	float radius;
	float max_radius;

	/// speed for lerping radius * delta time
	float blink_speed;

	/// only update star if active
	bool active;

	/// for blink animation 
	/// tells if start radius is getting bigger or smaller
	bool reverse;
} Star;

void stars_init(void);
void stars_update(void);
void stars_draw(void);

#endif
