#pragma once

#include "defines.h"

struct Player
{
	Player() : x(0.0f), y(0.0f) {}

	void reset()
	{
		x = WINDOW_WIDTH / 2.0f;
		y = MAX_PLAYER_Y;
	}

	float LegsStartX() const { return x + 24; }
	float LegsEndX()   const { return x + 64; }
	float LegsY()      const { return y + 73; }

	float x, y; // virsutinio kairiojo kampo koordinates
};

struct Plate
{
	Plate() : x(0.0f), y(0.0f) {}

	void reset(int index)
	{
		x = float(rand() % (WINDOW_WIDTH - PLATES_WIDTH));
		y = float(WINDOW_HEIGHT) / PLATES_AMOUNT * index;
	}

	float StartX()  const { return x; }
	float EndX()    const { return x + PLATES_WIDTH; }
	float TopY()    const { return y; }
	float BottomY() const { return y + PLATES_HEIGHT; }

	float x, y; // virsutinio kairiojo kampo koordinates
};
