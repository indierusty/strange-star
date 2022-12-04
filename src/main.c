#include "common.h"

static void init(void);
static void update_and_draw(void);
static void end(void);

int main() 
{
    InitWindow(screen_width, screen_height, "raylib");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) 
    {
        update_and_draw();
    }

    end();
}

static void init(void) 
{
}

static void update(void)
{
}

static void draw(void) 
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

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
