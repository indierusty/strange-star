#include "stars.h"
#include "state.h"

static Vector2 get_pos() 
{
	return (Vector2) { GetRandomValue(0, screen_width), GetRandomValue(0, screen_height)};
}

static void init_star(Star* s) 
{
	s->position = get_pos();

	s->radius = 0.0f;
	s->max_radius = GetRandomValue(2,6);

	/// if radius is big then speed is higher
	if (s->max_radius > 4) s->blink_speed = GetRandomValue(5, 30)*1.0f / 10;
	else s->blink_speed = GetRandomValue(1, 20)*1.0f / 10;

	/// false by default as will be true when stars blinking time come
	s->active = true; 

	s->reverse = false;
}

void stars_init(void)
{
	/// initialize 
	for (int i = 0; i < MAX_STAR; ++i) {
		init_star(&g.stars[i]);
	}
}

static void update_star(Star* s) 
{
	if (s->active) {
		if (s->reverse) {
			s->radius = Lerp(s->radius,  0, s->blink_speed*g.delta);
			if (s->radius <= 0.9) { 
				s->active = false;
				s->reverse = false;
				s->radius = 0;
			}
		} else {
			s->radius = Lerp(s->radius,  s->max_radius, s->blink_speed*g.delta);
			if (s->radius >= s->max_radius-1) s->reverse = true;
		}
	} else {
		init_star(s);
	}
}

void stars_update(void)
{
	for (int i = 0; i < MAX_STAR; ++i) {
		update_star(&g.stars[i]);
	}
}

void stars_draw(void)
{
	for (int i = 0; i < MAX_STAR; ++i) {
		Star* s = &g.stars[i];
		if (s->active) {
			DrawCircleV(s->position, s->radius, COLOR_STAR);
		}
	}
}
