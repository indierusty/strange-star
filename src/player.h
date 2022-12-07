#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

typedef struct {
	Vector2 position;
	Vector2 direction;
	Vector2 acceleration;
	Vector2 speed;
	float radius;

	/// bullet to show direction to dash
	Vector2 bullet_position;
	float bullet_radius;

	bool dashing;
	float dash_speed;
	Vector2 dash_dir;

	float time_counter;
	float dash_time;
} Player;


void player_init(void);
void player_update(void);
void player_draw(void);

#endif
