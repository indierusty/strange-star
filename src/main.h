#ifndef MAIN_H
#define MAIN_H

#include "player.h"
#include "bullet.h"

#define MAX_BULLET 3

typedef struct {
	Player player;
	Bullet bullets[MAX_BULLET];
} GameState;

extern GameState g;

#endif

