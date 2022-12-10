#include "common.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include "state.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = 0;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };
Sound inter_game = { 0 };
Sound player_destroy = { 0 };
Sound star_destroy = { 0 };
bool exit_game = false;

GameState g;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void change_to_screen(int screen);     // Change to screen, no transition effect

static void transition_to_screen(int screen); // Request transition to next screen
static void update_transition(void);         // Update transition effect
static void draw_transition(void);           // Draw transition effect (full-screen rectangle)

static void update_draw_frame(void);          // Update and draw one frame
											  //
Vector2 new_vec(float x, float y)
{
	return (Vector2){x, y};
}

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screen_width, screen_height, "raylib game template");

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/Roboto-Medium.ttf");
    music = LoadMusicStream("resources/ambient.ogg");
    fxCoin = LoadSound("resources/coin.wav");
    inter_game = LoadSound("resources/coin.wav");
    player_destroy = LoadSound("resources/laserLarge_002.ogg");
    star_destroy = LoadSound("resources/forceField_003.ogg");

    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    // Setup and init first screen
    currentScreen = LOGO;
    init_logo_screen();

#define FPS 160

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(update_draw_frame, FPS, 1);
#else
    SetTargetFPS(FPS);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !exit_game)    // Detect window close button or ESC key
    {
        update_draw_frame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO: unload_logo_screen(); break;
        case TITLE: unload_title_screen(); break;
        case GAMEPLAY: unload_gameplay_screen(); break;
        default: break;
    }

    // Unload global data loaded
    UnloadFont(font);
    UnloadMusicStream(music);
    UnloadSound(fxCoin);
    UnloadSound(inter_game);
    UnloadSound(player_destroy);
    UnloadSound(star_destroy);

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void change_to_screen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: unload_logo_screen(); break;
        case TITLE: unload_title_screen(); break;
        case GAMEPLAY: unload_gameplay_screen(); break;
        case ENDING: unload_ending_screen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: init_logo_screen(); break;
        case TITLE: init_title_screen(); break;
        case GAMEPLAY: init_gameplay_screen(); break;
        case ENDING: init_ending_screen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void transition_to_screen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void update_transition(void)
{
    if (!transFadeOut)
    {
        //transAlpha += 0.05f;
        transAlpha += 0.08f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: unload_logo_screen(); break;
                case TITLE: unload_title_screen(); break;
                case GAMEPLAY: unload_gameplay_screen(); break;
                case TUTORIAL: unload_tutorial_screen(); break;
                case ENDING: unload_ending_screen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: init_logo_screen(); break;
                case TITLE: init_title_screen(); break;
                case GAMEPLAY: init_gameplay_screen(); break;
                case TUTORIAL: init_tutorial_screen(); break;
                case ENDING: init_ending_screen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        //transAlpha -= 0.02f;
        transAlpha -= 0.05f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void draw_transition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void update_draw_frame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                update_logo_screen();
                if (finish_logo_screen()) transition_to_screen(TITLE);

            } break;
            case TITLE:
            {
                update_title_screen();
                if (finish_title_screen() == GAMEPLAY) transition_to_screen(GAMEPLAY);
				if (finish_title_screen() == TUTORIAL)  transition_to_screen(TUTORIAL);
				if (finish_title_screen() == EXIT)  exit_game = true;

            } break;
            case GAMEPLAY:
            {
                update_gameplay_screen();
                if (finish_gameplay_screen() == 1) transition_to_screen(ENDING);
            } break;
            case TUTORIAL:
            {
                update_tutorial_screen();
                if (finish_tutorial_screen() == 1) transition_to_screen(TITLE);
            } break;
            case ENDING:
            {
                update_ending_screen();
                if (finish_ending_screen() == 1) transition_to_screen(TITLE);
            } break;
            default: break;
        }
    }
    else update_transition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(COLOR_BACKGROUND);

        switch(currentScreen)
        {
            case LOGO: draw_logo_screen(); break;
            case TITLE: draw_title_screen(); break;
            case GAMEPLAY: draw_gameplay_screen(); break;
            case TUTORIAL: draw_tutorial_screen(); break;
            case ENDING: draw_ending_screen(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (onTransition) draw_transition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
