#ifndef BULLET_H
#define BULLET_H

#include "common.h"

typedef struct {
	Vector2 position;
	Vector2 direction;
	float speed;
	float radius;
	bool active;
} Bullet;

void bullets_draw(void);
void bullets_update(void);
void make_bullet(void);
void bullets_init(void); 

#endif

