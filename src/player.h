#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

typedef struct {
	Vector2 position;
	Vector2 direction;
	Vector2 acceleration;
	Vector2 speed;
	float radius;

	/// bullet
	Vector2 bullet_position;
	float bullet_radius;
} Player;

void player_init(void);
void player_update(void);
void player_draw(void);

#endif
