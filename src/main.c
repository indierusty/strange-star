#include "common.h"
#include "main.h"
#include "bullet.h"

GameState g;

static void init(void);
static void update_and_draw(void);
static void end(void);

int main() 
{
    init();

    while (!WindowShouldClose()) 
    {
        update_and_draw();
    }

    end();
}

static void init(void) 
{
    InitWindow(screen_width, screen_height, "raylib");
    SetTargetFPS(60);

    /// Player
    player_init();

    /// Bullets
    bullets_init();

	/// Stars
	stars_init();
}

static void update(void)
{
	/// Delta Time
	g.delta	= GetFrameTime();	

    /// Player
    player_update();

    /// Bullets
    bullets_update();

	/// Stars
	stars_update();
}

static void draw(void) 
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

	/// Stars
	stars_draw();

    /// Player
    player_draw();

    /// Bullets
    bullets_draw();

    EndDrawing();
}

static void update_and_draw(void)
{
    update();
    draw();
}

static void end(void) 
{
    CloseWindow();
}

