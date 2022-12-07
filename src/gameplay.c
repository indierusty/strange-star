#include "gameplay.h"
#include "state.h"

#define DASH_SCORE 5

static void init()
{
	/// state init
	g.estars_count = 3; /// must be less than MAX_ESTAR
	g.mndistance = 150;
	g.score = 0;
	g.out = false;
}

void game_init(void)
{
	init();

    /// Player
    player_init();

	/// Stars
	stars_init();

	/// Estars
	estars_init();
}

static bool check_collision(Vector2 apos, float aradius, Vector2 bpos, float bradius)
{
	float sum = aradius+bradius;
	if (Vector2DistanceSqr(apos, bpos) <= (sum)*(sum)) return true;
	return false;
}

static void update(void)
{
	/// player and estar collision
	for (int i = 0; i < g.estars_count; ++i) {
		if (g.estars[i].active) {
			if (check_collision(g.player.position, g.player.radius, g.estars[i].position, g.estars[i].radius)) {
				if (g.player.dashing) {
					g.score += DASH_SCORE;
					estar_init(&g.estars[i]);
				} else {
					g.out = true;
				}
			}
		}
	}
}

void game_update(void)
{
	/// Delta Time
	g.delta	= GetFrameTime();	

    /// Player
    player_update();

	/// Stars
	stars_update();

	/// Estars
	estars_update();

	update();
}

void game_draw(void)
{
	/// Stars
	stars_draw();

    /// Player
    player_draw();

	/// Estars
	estars_draw();
}

