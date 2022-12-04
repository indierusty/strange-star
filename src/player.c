#include "player.h"
#include "main.h"

void player_init(void)
{
	g.player.radius = 12;
	g.player.position.x = screen_width*1.0f/2;
	g.player.position.y = screen_height*1.0f/2;
}

void player_update(void)
{
	if (IsKeyDown(KEY_A)) g.player.position.x -= 2;
	if (IsKeyDown(KEY_D)) g.player.position.x += 2;
	if (IsKeyDown(KEY_W)) g.player.position.y -= 2;
	if (IsKeyDown(KEY_S)) g.player.position.y += 2;
}

void player_draw(void)
{
	DrawCircleV(g.player.position, g.player.radius, COLOR_PLAYER);
}


