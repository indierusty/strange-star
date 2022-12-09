#include "common.h"
#include "screens.h"
#include "state.h"

#define NAME_SIZE 25
static const char name[] = "Strange Star";
static Vector2 name_init_pos;
static Vector2 name_final_pos;
static float anim_time = 2.0;
static bool animation_done = false;

static float timer = 0;

static bool end_screen = false;
static int switch_to_screen = 0;

#define COLOR_ACTIVE COLOR_GREEN
#define COLOR_INACTIVE COLOR_WHITE
#define OPTION_FONT_SIZE 20
#define OPTION_GAP 10 /// gap between each option

typedef struct {
	char name[50];
	Vector2 position;
	GameScreen screen;
} Option;

#define MENU_SIZE 3
static Option options[MENU_SIZE];
static Vector2 option_position;
static int active_option = 0; /// index of active option

static void init_options()
{
	active_option = 0;
	option_position = new_vec((float)screen_width/2, 100);

	int y = option_position.y;

	options[0] = (Option) {
		.name = "start game",
		.screen = GAMEPLAY,
		.position = new_vec(
				option_position.x - (float)MeasureText("start game", OPTION_FONT_SIZE)/2,
				y)
	};
	y += OPTION_GAP+OPTION_FONT_SIZE;

	options[1] = (Option) {
		.name = "tutor",
		.screen = TUTORIAL,
		.position = new_vec(
				option_position.x - (float)MeasureText("tutor", OPTION_FONT_SIZE)/2,
				y)
	};

	y += OPTION_GAP+OPTION_FONT_SIZE;
	options[2] = (Option) {
		.name = "exit",
		.screen = EXIT,
		.position = new_vec(
				option_position.x - (float)MeasureText("exit", OPTION_FONT_SIZE)/2,
				y)
	};
}

void init_title_screen(void)
{
	name_init_pos = new_vec(
			(float)screen_width/2-(float)MeasureText(name, NAME_SIZE)/2,
			(float)screen_height/2-(float)NAME_SIZE/2);

	name_final_pos = new_vec(
			name_init_pos.x,
			20);
	
	anim_time = 1.2;
	animation_done = false;

	timer = 0;

	switch_to_screen = GAMEPLAY; 
	end_screen = false;

	init_options();
}

static void do_animation()
{
	if (anim_time < timer) 
	{
		name_init_pos = Vector2Lerp(name_init_pos, name_final_pos, 10.0*GetFrameTime());
	}

	if (name_init_pos.y <= name_final_pos.y+2) 
	{
		animation_done = true;
	}
}

static void update_menu() 
{
	if (IsKeyPressed(KEY_DOWN)) active_option += 1;
	if (IsKeyPressed(KEY_UP)) active_option -= 1;
	if (active_option < 0) active_option = MENU_SIZE-1;
	if (active_option == MENU_SIZE) active_option = 0;
}

void update_title_screen(void) 
{
	if (animation_done && IsKeyPressed(KEY_ENTER)) 
	{
		end_screen = true;
		switch_to_screen = GAMEPLAY;
	}

	timer += GetFrameTime();

	if (!animation_done) 
	{
		do_animation();
	}
	else 
	{
		update_menu();
	};
}

static void draw_menu() 
{
	for (int i = 0; i < MENU_SIZE; i++)
	{
		DrawText(options[i].name,
				options[i].position.x,
				options[i].position.y,
				OPTION_FONT_SIZE,
				active_option == i ? COLOR_ACTIVE : COLOR_INACTIVE);
	}
}

void draw_title_screen(void) 
{
	DrawText(
			name, 
			name_init_pos.x,	
			name_init_pos.y,	
			NAME_SIZE, 
			COLOR_YELLOW);

	if (animation_done) draw_menu();
}

void unload_title_screen(void) 
{
}

int finish_title_screen(void) 
{
	if (end_screen) return options[active_option].screen;
	return 0;
}
