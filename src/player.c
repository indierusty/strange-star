#include "common.h"
#include "state.h"

/// gap between player and bullet
#define GAP 3

void player_init(void)
{
	g.player.radius = 12;
	g.player.position.x = screen_width*1.0f/2;
	g.player.position.y = screen_height*1.0f/2;
	g.player.direction = Vector2One();

	g.player.dashing = false;
	g.player.dash_speed = 400.0f;
	g.player.dash_dir = Vector2Zero();

	g.player.time_counter = 0.0f;
	g.player.dash_time = 0.10f;
}

static void handle_dashing(void)
{
	g.player.time_counter += g.delta;
	if (g.player.dash_time < g.player.time_counter) {
		g.player.dashing = false;
		g.player.time_counter = 0.0f;
		return;
	}

	g.player.position = Vector2Add(g.player.position, Vector2Scale(g.player.dash_dir, g.player.dash_speed*g.delta));
}

static bool is_in_motion() 
{
	return !(g.player.direction.x == 0 && g.player.direction.y == 0);
}

void player_update(void)
{
#define SPEED 200.0f

	if (IsKeyDown(KEY_A)) g.player.direction = new_vec(-1, 0);
	else if (IsKeyDown(KEY_D)) g.player.direction = new_vec(1, 0);
	else if (IsKeyDown(KEY_W)) g.player.direction = new_vec(0, -1);
	else if (IsKeyDown(KEY_S)) g.player.direction = new_vec(0, 1);
	else g.player.direction = Vector2Zero();

	g.player.speed.x = g.player.direction.x * SPEED * g.delta;
	g.player.speed.y = g.player.direction.y * SPEED * g.delta;

#undef SPEED /// ? is it useful don't known yet

	if (IsKeyPressed(KEY_SPACE) && is_in_motion() && !g.player.dashing) {
		g.player.dashing = true;
		g.player.dash_dir = g.player.direction;
	}

	if (g.player.dashing) 
	{
		/// Dash on Space
		handle_dashing();
	}
	else 
	{
		// for smooth movement 
		g.player.acceleration = Vector2Lerp(g.player.acceleration, g.player.speed, 0.15);
		g.player.position = Vector2Add(g.player.position, g.player.acceleration);
	}

}

void player_draw(void)
{
	/// Draw Player Body
	DrawCircleV(g.player.position, g.player.radius, COLOR_GREEN);
	DrawCircleV(g.player.position, g.player.radius-3, COLOR_BACKGROUND);
	DrawCircleV(g.player.position, g.player.radius-5, COLOR_GREEN);
}


