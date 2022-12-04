#include "player.h"
#include "main.h"

void player_init(void)
{
	g.player.radius = 12;
	g.player.position.x = screen_width*1.0f/2;
	g.player.position.y = screen_height*1.0f/2;
	g.player.direction = Vector2One();
}

void player_update(void)
{
	/// Player position movement 
	if (IsKeyDown(KEY_A)) g.player.speed.x = -2;
	else if (IsKeyDown(KEY_D)) g.player.speed.x = 2;
	else if (IsKeyDown(KEY_W)) g.player.speed.y = -2;
	else if (IsKeyDown(KEY_S)) g.player.speed.y = 2;
	else g.player.speed = Vector2Zero();

	g.player.acceleration = Vector2Lerp(g.player.acceleration, g.player.speed, 0.2);

	g.player.position = Vector2Add(g.player.position, g.player.acceleration);

	/// Player direction movement
}

void player_draw(void)
{
	DrawCircleV(g.player.position, g.player.radius, COLOR_PLAYER);
}


