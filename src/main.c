#include "common.h"
#include "state.h"
#include "gameplay.h"

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

	game_init();
}

static void update(void)
{
	if (!g.out) game_update();
}

static void draw(void) 
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

	if (!g.out) game_draw();

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

