#include "bullet.h"
#include "main.h"

static void bullet_init(Bullet* b) 
{
#define SPEED 200.0f
	b->active	= false;
	b->radius	= 3;
	b->speed	= SPEED;
	b->position = Vector2Zero();
	b->direction= Vector2Zero();
#undef SPEED
}

void bullets_init(void) 
{
	for (int i = 0; i < MAX_BULLET; ++i) bullet_init(&g.bullets[i]);
}

/// activate new bullet at current player bullet position and direction
void make_bullet(void)
{
	for (int i = 0; i < MAX_BULLET; ++i) {
		Bullet* b = &g.bullets[i];
		if (!b->active) {
			b->position = g.player.bullet_position;
			b->direction = g.player.direction;
			b->active = true;
			break;
		}
	}
}

void bullets_update(void)
{
	for (int i = 0; i < MAX_BULLET; ++i) {
		Bullet* b = &g.bullets[i];

        /// update active bullets 
		if (b->active) {
			b->position = Vector2Add(b->position, Vector2Scale(b->direction, b->speed*g.delta));
		}

        /// inactivate bullet when goes out of screen 
		if (b->position.x <= 0 ||
			b->position.x >= screen_width ||
			b->position.y <= 0 ||
			b->position.y >= screen_height
		   ) {
			bullet_init(b);
		}

		/// TODO: destroy bullets when collide with stars 
	}
}

void bullets_draw(void)
{
	for (int i = 0; i < MAX_BULLET; ++i) {
		Bullet* b = &g.bullets[i];
		if (b->active) DrawCircleV(b->position, b->radius, COLOR_PLAYER);
	}
}
