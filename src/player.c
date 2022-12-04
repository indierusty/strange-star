#include "player.h"
#include "main.h"

/// gap between player and bullet
#define GAP 3

void player_init(void)
{
	g.player.radius = 12;
	g.player.position.x = screen_width*1.0f/2;
	g.player.position.y = screen_height*1.0f/2;
	g.player.direction = Vector2One();

	g.player.bullet_position = Vector2Add(g.player.position, Vector2Scale(g.player.direction, g.player.radius+2));
	g.player.bullet_radius = 3;
}

void player_update(void)
{
#define SPEED 200.0f
	/// Player position movement 
	if (IsKeyDown(KEY_A)) g.player.speed.x = -SPEED*g.delta;
	else if (IsKeyDown(KEY_D)) g.player.speed.x = SPEED*g.delta;
	else if (IsKeyDown(KEY_W)) g.player.speed.y = -SPEED*g.delta;
	else if (IsKeyDown(KEY_S)) g.player.speed.y = SPEED*g.delta;
	else g.player.speed = Vector2Zero();

#undef SPEED /// ? is it useful don't known yet

	// for smooth movement 
	g.player.acceleration = Vector2Lerp(g.player.acceleration, g.player.speed, 0.1);
	g.player.position = Vector2Add(g.player.position, g.player.acceleration);

	/// Player direction movement
	g.player.direction = Vector2Normalize(Vector2Subtract(GetMousePosition(), g.player.position));
	g.player.bullet_position = 
		Vector2Add( 
				g.player.position,
				Vector2Scale(g.player.direction, g.player.radius+GAP+g.player.bullet_radius)
		);

	/// Shooting Bullet
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		make_bullet();
	}
}

void player_draw(void)
{
	/// Draw Player Body
	DrawCircleV(g.player.position, g.player.radius, COLOR_PLAYER);
	DrawCircleV(g.player.position, g.player.radius-3, COLOR_BACKGROUND);
	DrawCircleV(g.player.position, g.player.radius-5, COLOR_PLAYER);

	/// Draw Player Bullet
	DrawCircleV(g.player.bullet_position, g.player.bullet_radius, COLOR_PLAYER);
}


