#ifndef MAIN_H
#define MAIN_H

#include "player.h"
#include "bullet.h"
#include "stars.h"

#define MAX_BULLET	5
#define MAX_STAR	200

typedef struct {
	Player player;
	Bullet bullets[MAX_BULLET];
	Star stars[MAX_STAR];
	float delta;
} GameState;

extern GameState g;

#endif

