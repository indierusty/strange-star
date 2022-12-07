#include "common.h"
#include "state.h"

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
    SetTargetFPS(20);

	/// state init
	g.estars_count = 3; /// must be less than MAX_ESTAR
	g.mndistance = 150;

    /// Player
    player_init();

	/// Stars
	stars_init();

	/// Estars
	estars_init();
}

static void update(void)
{
	/// Delta Time
	g.delta	= GetFrameTime();	

    /// Player
    player_update();

	/// Stars
	stars_update();

	/// Estars
	estars_update();
}

static void draw(void) 
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

	/// Stars
	stars_draw();

    /// Player
    player_draw();

	/// Estars
	estars_draw();

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

