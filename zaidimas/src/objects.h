#pragma once

#include "defines.h"

class Player
{
public:
	Player();
	Player(float startX, float startY);

	void reset();
	void move(float dx, float dy);

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void  setX(float x) { m_x = x; }
	void  setY(float y) { m_y = y; }

	float LegsStartX() const { return m_x + 24; }
	float LegsEndX()   const { return m_x + 64; }
	float LegsY()      const { return m_y + 73; }

private:
	float m_x;
	float m_y;
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

	float x, y;
};
