#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"

#define DEBUG

#ifdef DEBUG
	#include "stdio.h"
#endif

/// 1<<8 == 256 just for fun
static const int screen_width = 1<<8;
static const int screen_height= 1<<8;

/// Colors
#define COLOR_BACKGROUND	(Color) {40, 40, 40, 255}
#define COLOR_GREEN			(Color) {0, 228, 48, 255}
#define COLOR_WHITE			(Color) {0xeb, 0xdb, 0xb2, 255}
#define COLOR_YELLOW		(Color) {0xfa, 0xbd, 0x2f, 255}

static Vector2 new_vec(float x, float y) 
{
	return (Vector2){x, y};
}

#endif // COMMON_H
