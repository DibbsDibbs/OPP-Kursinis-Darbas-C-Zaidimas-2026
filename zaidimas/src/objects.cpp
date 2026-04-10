#include "objects.h"

Plate::Plate()
	: m_x(0.0f), m_y(0.0f)
{
}

Plate::Plate(float startX, float startY)
	: m_x(startX), m_y(startY)
{
}

void Plate::reset(int index)
{
	m_x = float(rand() % (WINDOW_WIDTH - PLATES_WIDTH));
	m_y = float(WINDOW_HEIGHT) / PLATES_AMOUNT * index;
}

void Plate::scrollBy(float dy)
{
	m_y -= dy;

	if (m_y > WINDOW_HEIGHT)
	{
		m_y = float(rand() % 10);
		m_x = float(rand() % (WINDOW_WIDTH - PLATES_WIDTH));
	}
}

Player::Player()
	: m_x(WINDOW_WIDTH / 2.0f), m_y(MAX_PLAYER_Y)
{
}

Player::Player(float startX, float startY)
	: m_x(startX), m_y(startY)
{
}

void Player::reset()
{
	m_x = WINDOW_WIDTH / 2.0f;
	m_y = MAX_PLAYER_Y;
}

void Player::move(float dx, float dy)
{
	m_x += dx;
	m_y += dy;
}
