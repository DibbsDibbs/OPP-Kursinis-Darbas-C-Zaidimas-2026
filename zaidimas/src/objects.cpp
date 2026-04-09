#include "objects.h"

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
