#include "screens.h"
#include "common.h"

#define STORY_LEN 12 

static const char story[STORY_LEN][100] = {
 "Bob visits a Strage glaxy ",
 "while space traveling.",
 "Strange stars Unexpectedly",
 "hits bob's space craft.",
 "help him. he's bad fighter.",
 "",
 "Destroy Strage star by",
 "dashing into star at speed.",
 "",
 "use WASD to move and",
 "SPACE to dash into the ",
 "direction."
};

static Vector2 story_pos;
static bool end_screen = 0;
static Rectangle border;

void init_tutorial_screen(void)
{
	end_screen = false;
	story_pos.x = 20;
	story_pos.y = 20;

	border.x = 2;
	border.y = 2;
	border.width = 250;
	border.height= 250;
}

void update_tutorial_screen(void)
{
	if (IsKeyPressed(KEY_ENTER)) end_screen = true;
}

void draw_tutorial_screen(void)
{
#define GAP 2
#define FONT_SIZE 16 
	int y = story_pos.y;
	for (int i = 0; i < STORY_LEN; i++) 
	{
		DrawTextEx(font, story[i],
				(Vector2){story_pos.x, y},
				FONT_SIZE,
				GAP,
				COLOR_WHITE);
		y += 2+FONT_SIZE;
	}
#undef FONT_SIZE 
#undef GAP

	DrawRectangleLinesEx(border, 3, COLOR_WHITE);
}

void unload_tutorial_screen(void)
{
	///
}

int finish_tutorial_screen(void)
{
	if (end_screen) return 1;
	return 0;
}
