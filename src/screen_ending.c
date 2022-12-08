#include <stdio.h>

#include "common.h"
#include "screens.h"
#include "raylib.h"
#include "state.h"

static float time_counter = 0; /// TODO: float overflow
static int finish_screen = 0;

#define MSG_FONTSIZE 30

static char message[100];

void init_ending_screen(void)
{
	finish_screen = 0;
	time_counter = 0;

	sprintf(message, "Score :: %d", g.score);
}

void update_ending_screen(void)
{
	time_counter += g.delta;
	if (IsKeyPressed(KEY_ENTER)) finish_screen = 1;
}

void draw_ending_screen(void)
{
	DrawText(
			TextSubtext(message, 0, (int)(time_counter*5)), 
			screen_width/2-MeasureText(message, MSG_FONTSIZE)/2,
			screen_height/2-MSG_FONTSIZE/2, 
			MSG_FONTSIZE, 
			COLOR_PLAYER);

	DrawText(
			"PRESS [ENTER] to RESTART!",
			screen_width/2-MeasureText("PRESS [ENTER] to RESTART!", 10)/2,
			screen_height-20*2, 
			10,
			LIGHTGRAY);
}

void unload_ending_screen(void)
{
	///
}

int finish_ending_screen(void)
{
	return finish_screen;
}

