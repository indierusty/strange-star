#ifndef STATE_H
#define STATE_H

#include "raylib.h"

//----------------------------------------------------------------------------------
// Particle 
//----------------------------------------------------------------------------------

typedef struct {
	Vector2 position;
	Vector2 direction;
	Color color;
	float radius;
} MiniStar;

#define MINISTARS_SIZE 5

typedef struct {
	MiniStar stars[MINISTARS_SIZE];
	Vector2 position;
	bool active;
} Particle;

#define PARTICLES_SIZE 10

void make_particle(Vector2 at);
void particles_init(void);
void particles_update(void);
void particles_draw(void);

//----------------------------------------------------------------------------------
// Player
//----------------------------------------------------------------------------------
typedef struct {
	Vector2 position;
	Vector2 direction;
	Vector2 acceleration;
	Vector2 speed;
	float radius;

	bool dashing;
	float dash_speed;
	Vector2 dash_dir;

	float time_counter;
	float dash_time;
} Player;


void player_init(void);
void player_update(void);
void player_draw(void);

//----------------------------------------------------------------------------------
// Stars 
//----------------------------------------------------------------------------------
typedef struct {
	Vector2 position;

	float radius;
	float max_radius;

	/// speed for lerping radius * delta time
	float blink_speed;

	/// only update star if active
	bool active;

	/// for blink animation 
	/// tells if start radius is getting bigger or smaller
	bool reverse;
} Star;

void stars_init(void);
void stars_update(void);
void stars_draw(void);

//----------------------------------------------------------------------------------
// EStars 
//----------------------------------------------------------------------------------
typedef struct {
	bool active;
	Vector2 position;
	float radius;
	float max_radius;
	/// speed of strange gravity 
	float speed;
	/// direction towards player
	Vector2 direction;
	/// time related
	float time_counter;
	float start_time;
	float duration;

	float blink_speed;
} Estar;

void estar_init(Estar* e);
void estars_init(void);
void estars_update(void);
void estars_draw(void);

#define MAX_STAR	200
#define MAX_ESTAR	10

typedef struct {
	Player player;
	Star stars[MAX_STAR];
	Estar estars[MAX_ESTAR];
	Particle particles[PARTICLES_SIZE];
	/// mn initial distance between player and estar and between estars
	int mndistance;
	int estars_count;
	float delta;
	int score;
	bool out;
} GameState;

extern GameState g;

#endif

