#ifndef STATE_H
#define STATE_H

#include "player.h"
#include "stars.h"
#include "estars.h"

#define MAX_STAR	200
#define MAX_ESTAR	10

typedef struct {
	Player player;
	Star stars[MAX_STAR];
	Estar estars[MAX_ESTAR];
	/// max initial distance between player and estar 
	/// and between estars
	int mndistance;

	int estars_count;
	float delta;
} GameState;

extern GameState g;

#endif

