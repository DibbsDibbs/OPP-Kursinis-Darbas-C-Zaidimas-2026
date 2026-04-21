#pragma once

#include "defines.h"

#include <iosfwd>

class Player
{
public:
	Player();
	Player(float startX, float startY);
	Player(const Player& other);

	void reset();
	void move(float dx, float dy);

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void  setX(float x) { m_x = x; }
	void  setY(float y) { m_y = y; }

	float LegsStartX() const { return m_x + 24; }
	float LegsEndX()   const { return m_x + 64; }
	float LegsY()      const { return m_y + 73; }

	// Operatoriaus perkrovimas: leidzia daryti std::cout << player;
	friend std::ostream& operator<<(std::ostream& os, const Player& p);

	// Operatoriaus perkrovimas: palyginimas pagal y (aukscio) pozicija
	bool operator<(const Player& other) const { return m_y < other.m_y; }

private:
	float m_x;
	float m_y;
};

class Plate
{
public:
	Plate();
	Plate(float startX, float startY);

	void reset(int index);
	void scrollBy(float dy);

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void  setPosition(float x, float y) { m_x = x; m_y = y; }

	float StartX()  const { return m_x; }
	float EndX()    const { return m_x + PLATES_WIDTH; }
	float TopY()    const { return m_y; }
	float BottomY() const { return m_y + PLATES_HEIGHT; }

private:
	float m_x;
	float m_y;
};
