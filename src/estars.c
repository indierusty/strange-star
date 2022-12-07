#include "estars.h"
#include "state.h"

static Vector2 get_pos() 
{
	return (Vector2) { GetRandomValue(0, screen_width), GetRandomValue(0, screen_height)};
}

static bool far_enough(Vector2 pos)
{
    if (Vector2Distance(g.player.position, pos) < g.mndistance) return false;
    return true;
}

static Vector2 position()
{
    Vector2 pos = get_pos();
    while (!far_enough(pos)) 
    {
        pos = get_pos();
    }

    return pos;
}

static void init(Estar* e)
{
	e->active = false;

    /// update pos untill is far enough from player
	e->position = position();
	e->radius = 3.0f;
	e->max_radius = 10.0f;

	e->time_counter = 0.0f;
    e->duration = GetRandomValue(5, 15)*1.0f/10;
	e->start_time = GetRandomValue(5,20)*1.0f/10;

	e->blink_speed = GetRandomValue(5, 20)*1.0f/10;

	e->direction = Vector2Normalize(Vector2Subtract(g.player.position, e->position));
	e->speed = 100.0f;
}

void estars_init(void)
{
	for (int i = 0; i < g.estars_count; i++) 
	{
		init(&g.estars[i]);
	}
}

static void update(Estar* e) 
{
    e->time_counter += g.delta;

	if (e->active)
	{
        if ((e->start_time + e->duration) <= e->time_counter) {
            init(e);
        }

		e->radius = Lerp(e->radius, e->max_radius, e->blink_speed*g.delta);
		e->position = Vector2Add(e->position, Vector2Scale(e->direction, e->speed*g.delta));
	}
	else
	{
        if (e->start_time >= e->time_counter) e->active = true;
	}
}

void estars_update(void)
{
	for (int i = 0; i < g.estars_count; i++)
	{
		update(&g.estars[i]);
	}
}

void estars_draw(void) 
{
	for (int i = 0; i < g.estars_count; i++)
	{
		if (g.estars[i].active) 
		{
			DrawCircleV(g.estars[i].position, g.estars[i].radius, COLOR_ESTAR);
		}
	}
}
